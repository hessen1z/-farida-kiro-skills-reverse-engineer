---
title: Prompt: Analyze Memory
skill: reverse-engineering
category: prompts
difficulty: intermediate
tags: [pe, x64, dll]
updated: 2026-07-05
---
# Prompt: Analyze Memory

## Objective
Map the runtime memory layout of a target process. Identify all loaded modules, heap allocations, key objects, pointer chains, and executable regions. Produce a memory map suitable for offset hunting and runtime patching.

## Methodology

### Step 1 — Enumerate All Memory Regions
Use VirtualQuery to walk the entire address space:
```cpp
MEMORY_BASIC_INFORMATION mbi{};
uintptr_t addr = 0;
while (VirtualQuery((void*)addr, &mbi, sizeof(mbi))) {
    printf("%016llX  %-12s  %-20s  %s\n",
        (uint64_t)mbi.BaseAddress,
        StateStr(mbi.State),
        ProtectStr(mbi.Protect),
        TypeStr(mbi.Type));
    addr = (uintptr_t)mbi.BaseAddress + mbi.RegionSize;
}
```
Categories: MEM_IMAGE (PE sections), MEM_PRIVATE (heap/stack/injected), MEM_MAPPED (file/shared).

### Step 2 — Identify Module Boundaries
Walk PEB.Ldr.InMemoryOrderModuleList:
```cpp
auto* peb = NtCurrentTeb()->ProcessEnvironmentBlock;
auto* ldr = peb->Ldr;
for (auto* e = ldr->InMemoryOrderModuleList.Flink; ...) {
    auto* entry = CONTAINING_RECORD(e, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);
    wprintf(L"%p [%08X] %wZ\n", entry->DllBase, entry->SizeOfImage, &entry->FullDllName);
}
```
Record: DllBase (VA), SizeOfImage, module name, full path.

### Step 3 — Find the Heap
HeapBase is in PEB.ProcessHeap. All heap allocations will be in MEM_PRIVATE regions starting near HeapBase. Use `!heap -a` in WinDbg to dump heap segments.

### Step 4 — Locate Key Objects in Memory
For each target C++ class:
1. Break at constructor entry. RCX = freshly allocated object.
2. Note address. Note surrounding memory region (which heap segment).
3. Dump object: `dq rcx L10` in WinDbg or right-click → Follow in Dump in x64dbg.
4. Verify vptr at [obj+0]: must match known vtable address.
5. Read COL from vtable[-1] → confirm class identity.

### Step 5 — Build Pointer Chains to Key Objects
Start from the object address, work backward:
1. Search all readable memory for the object's address as a pointer value.
2. Find which global/static holds a pointer to it (or to a container that holds it).
3. Verify the root is a static address in .data: `module_base + constant_rva`.
4. Test chain across 3+ restarts.

### Step 6 — Identify Executable Regions (Code Caves / Injected)
All MEM_PRIVATE + PAGE_EXECUTE_* regions are suspicious:
- Legitimate: JIT-compiled code, some runtime-generated stubs
- Suspicious: shellcode, injected DLL code not registered in PEB

Enumerate and log all such regions. If size > 4KB and not in PEB module list → potential injection.

### Step 7 — Stack Analysis
Per thread, the stack is a MEM_PRIVATE region with specific characteristics:
- `RSP` points somewhere inside it
- Grows downward
- Top of stack = thread stack limit (lowest committed address)
- In WinDbg: `!teb` shows StackBase and StackLimit

## Checklist
- [ ] All memory regions enumerated and categorized
- [ ] All loaded modules listed with base/size
- [ ] Heap segments identified
- [ ] Key C++ objects located by breaking at constructors
- [ ] Vtable identity verified at each located object
- [ ] Pointer chains built and tested across 3 restarts
- [ ] Suspicious executable MEM_PRIVATE regions flagged
- [ ] Per-thread stack ranges noted

## Expected Output
```
=== Memory Map Summary ===
MEM_IMAGE  regions:  42 (total 180MB  — PE-mapped modules)
MEM_PRIVATE regions: 318 (total 85MB  — heap, stack, JIT)
MEM_MAPPED  regions:  12 (total 4MB   — file-backed)

=== Modules ===
game.exe    base=0x140000000  size=0x01800000
ntdll.dll   base=0x7FF8A000   size=0x001F4000
...

=== Key Objects ===
CPlayerManager @ 0x1C4A2B000  (chain: game.exe+0x1A2B4C8 → +0x10)
CEntityList    @ 0x1C4A3C000  (chain: game.exe+0x1A2B500 → +0x00)

=== Suspicious Regions ===
0x7F0000000  MEM_PRIVATE  PAGE_EXECUTE_READWRITE  size=0x10000  [UNKNOWN — investigate]
```

## Validation
1. Resolve each documented object address at runtime. Verify vptr matches expected vtable.
2. Walk each pointer chain from the static root. Verify it reaches the documented address.
3. Any suspicious executable region: disassemble first 16 bytes. Determine if benign or injected.

## Common Mistakes
- Not verifying object identity via vtable/RTTI — any address can look like a valid pointer.
- Assuming heap objects are at stable addresses — they change on every allocation cycle.
- Missing modules loaded after startup (late LoadLibrary calls) — re-enumerate after game fully loads.
- Not checking for PAGE_GUARD regions before reading — they fault on access.

## Related Material

### Knowledge
- [common-instructions](../knowledge/assembly/common-instructions.md)
- [compiler-patterns](../knowledge/assembly/compiler-patterns.md)
- [exceptions](../knowledge/cpp/exceptions.md)

### Prompts
- [analyze_binary](analyze_binary.md)
- [analyze_crash](analyze_crash.md)
- [build_reclass](build_reclass.md)

