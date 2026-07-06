---
title: Reverse Engineering Code Examples
skill: reverse-engineering
category: 
difficulty: intermediate
tags: [pe, windows, x64, pdb, kernel, dll]
updated: 2026-07-05
---
# Reverse Engineering Code Examples

> Production-quality C++ code demonstrating the core techniques. All examples target Windows x64. Build with MSVC 2019+ or Clang-cl.

---

## Pattern Scanner

**File:** `examples/pattern-scan.cpp`

A high-performance in-process pattern scanner with wildcard support. Scans committed executable memory regions only.

### Key design decisions

- Scans only `MEM_COMMIT` + `PAGE_EXECUTE_*` regions — avoids scanning stack, heap, and data pages needlessly
- `??` wildcard is represented as `0xFF` mask byte (`0x00`) — a two-array mask approach is faster than string parsing at scan time
- Returns the first match; caller can request all matches by iterating from result + 1
- Thread-safe: read-only scan, no shared state

### Usage

```cpp
// Find the function by its prologue bytes
// Use ?? for bytes that encode addresses (will change with ASLR)
uintptr_t addr = PatternScan(
    "48 89 5C 24 08 "   // mov [rsp+8], rbx
    "48 89 74 24 10 "   // mov [rsp+10], rsi
    "57 "               // push rdi
    "48 83 EC 20 "      // sub rsp, 20
    "48 8B F9 "         // mov rdi, rcx
    "?? ?? ?? ?? ?? "   // call [rel32] — wildcarded, changes per version
    "48 8B D8"          // mov rbx, rax
);

if (addr) {
    auto fn = reinterpret_cast<void(*)(void*)>(addr);
    fn(someObject);
}
```

**Full implementation:** [../examples/cpp/pattern-scan.cpp](../examples/cpp/pattern-scan.cpp)

---

## PE Parser

**File:** `../examples/cpp/pe-parser.cpp`

Walks a PE file (mapped in memory or on disk) and enumerates:
- Section headers with permissions
- Import table (all DLLs and their functions)
- Export table (named and ordinal exports)
- Data directories

### Key design decisions

- Works on both in-memory (loaded) and on-disk (file-mapped) PE images
- Handles both PE32 (x86) and PE32+ (x64) via `Magic` field detection
- Validates all RVAs before dereferencing — no crashes on truncated or malformed PE files
- Resolves import thunk names including ordinal-only imports

### Usage

```cpp
// Parse the current process's own executable
PEParser parser(GetModuleHandle(nullptr), true /*in-memory*/);

// Enumerate imports
for (const auto& dll : parser.GetImports()) {
    printf("DLL: %s\n", dll.name.c_str());
    for (const auto& fn : dll.functions) {
        printf("  [%3u] %s @ 0x%llX\n", fn.ordinal, fn.name.c_str(), fn.iat_va);
    }
}

// Find an export by name
uintptr_t va = parser.GetExportByName("MyExportedFunction");
```

**Full implementation:** [../examples/cpp/pe-parser.cpp](../examples/cpp/pe-parser.cpp)

---

## VMT Hook

**File:** `../examples/cpp/vmt-hook.cpp`

A safe per-object virtual function table hook. Replaces one vtable slot on a specific object instance without modifying the shared vtable in `.rdata`.

### Key design decisions

- Per-object hook: allocates a private vtable copy for the target object only — other instances are unaffected
- Non-destructive: preserves original vtable slots, only replaces the targeted one
- Hook function receives the original vtable slot as a trampoline — can call original
- RAII cleanup: `VmtHook` destructor restores the original vptr
- Thread-safe for read operations; caller must synchronize around hook install/remove

### Why per-object is preferred

Patching the global vtable in `.rdata` is detectable:
1. The page transitions from `MEM_IMAGE` to `MEM_PRIVATE` (COW copy)
2. Integrity scanning tools hash vtable contents
3. Other processes sharing the same DLL are unaffected but the local process has a unique page — detectable via memory scan

Per-object swapping only writes the object's vptr field, which is in writable heap/stack memory — no page permission changes.

### Usage

```cpp
class IEnemy {
public:
    virtual int  GetHealth() = 0;
    virtual void TakeDamage(int amount) = 0;
    virtual void Update() = 0;
};

// Hook slot 0 (GetHealth)
VmtHook hook(enemyPtr, 0);

// Install hook — saves original, writes new vptr
hook.Install([](void* thisPtr) -> int {
    // Call original
    int original = hook.CallOriginal<int>(thisPtr);
    printf("GetHealth called, original=%d\n", original);
    return 9999; // override return
});

// ... use enemy ...

// hook.Remove() restores original vptr (also called by destructor)
```

**Full implementation:** [../examples/cpp/vmt-hook.cpp](../examples/cpp/vmt-hook.cpp)

---

## Pointer Chain

**File:** `../examples/cpp/pointer-chain.cpp`

Safe multi-level pointer chain resolver. Validates each pointer in the chain before dereferencing. Returns `std::optional<T>` — no exceptions, no crashes on invalid chains.

### Key design decisions

- Each level validates: not null, not kernel address, page is `MEM_COMMIT`, not `PAGE_GUARD`, has read access
- Variadic template: `ReadChain<float>(base, 0x10, 0x20, 0x78)` reads any depth chain
- Returns `std::optional<T>`: caller checks with `.has_value()` before using result
- Write variant `WriteChain<float>` validates the final page has write access

### Usage

```cpp
// Read health: module_base + 0x1A2B4C8 -> +0x10 -> +0x78 -> float
auto health = ReadChain<float>(
    moduleBase + 0x1A2B4C8,  // static offset from module base
    0x10,                     // offset into player_manager
    0x78                      // offset into player object -> health
);

if (health.has_value()) {
    printf("Health: %.1f\n", health.value());
}

// Write health
bool ok = WriteChain<float>(
    moduleBase + 0x1A2B4C8,
    0x10,
    0x78,
    100.0f  // value to write
);
```

**Full implementation:** [../examples/cpp/pointer-chain.cpp](../examples/cpp/pointer-chain.cpp)

---

## Additional Patterns and Snippets

### Get Module Base by Name

```cpp
uintptr_t GetModuleBase(const wchar_t* moduleName) {
    return reinterpret_cast<uintptr_t>(GetModuleHandleW(moduleName));
}

// Get current executable base:
uintptr_t base = reinterpret_cast<uintptr_t>(GetModuleHandleW(nullptr));
```

### Walk Module List via PEB

```cpp
// Enumerate all loaded modules via PEB.Ldr (no Win32 API needed)
#include <winternl.h>

void EnumModules() {
    auto* peb  = NtCurrentTeb()->ProcessEnvironmentBlock;
    auto* ldr  = peb->Ldr;
    auto* head = &ldr->InMemoryOrderModuleList;

    for (auto* e = head->Flink; e != head; e = e->Flink) {
        auto* entry = CONTAINING_RECORD(e, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);
        if (entry->DllBase) {
            wprintf(L"Module: %wZ @ 0x%p (size 0x%X)\n",
                &entry->FullDllName,
                entry->DllBase,
                entry->SizeOfImage);
        }
    }
}
```

### Resolve Export by Name Without LoadLibrary

```cpp
uintptr_t GetExportAddress(uintptr_t moduleBase, const char* exportName) {
    auto* dos  = reinterpret_cast<IMAGE_DOS_HEADER*>(moduleBase);
    auto* nt   = reinterpret_cast<IMAGE_NT_HEADERS64*>(moduleBase + dos->e_lfanew);
    auto& dir  = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
    if (!dir.VirtualAddress) return 0;

    auto* exp  = reinterpret_cast<IMAGE_EXPORT_DIRECTORY*>(moduleBase + dir.VirtualAddress);
    auto* names    = reinterpret_cast<DWORD*>(moduleBase + exp->AddressOfNames);
    auto* ordinals = reinterpret_cast<WORD*>(moduleBase + exp->AddressOfNameOrdinals);
    auto* funcs    = reinterpret_cast<DWORD*>(moduleBase + exp->AddressOfFunctions);

    for (DWORD i = 0; i < exp->NumberOfNames; i++) {
        const char* name = reinterpret_cast<const char*>(moduleBase + names[i]);
        if (strcmp(name, exportName) == 0) {
            DWORD funcRva = funcs[ordinals[i]];
            // Check for forwarded export
            if (funcRva >= dir.VirtualAddress && funcRva < dir.VirtualAddress + dir.Size) {
                // Forwarded: moduleBase+funcRva is a string like "NTDLL.RtlAllocateHeap"
                return 0; // Handle forwarding separately if needed
            }
            return moduleBase + funcRva;
        }
    }
    return 0;
}
```

### Get Class Name From Object (RTTI)

```cpp
const char* GetMSVCClassName(void* obj) {
    if (!obj) return nullptr;

    uintptr_t moduleBase = reinterpret_cast<uintptr_t>(GetModuleHandleW(nullptr));

    // vptr is at object[0]
    uintptr_t* vptr = *reinterpret_cast<uintptr_t**>(obj);

    // COL is at vptr[-1]
    uintptr_t col = vptr[-1];

    // On x64, pTypeDescriptor is an RVA at COL+12
    DWORD tdRva = *reinterpret_cast<DWORD*>(col + 12);
    uintptr_t td = moduleBase + tdRva;

    // TypeDescriptor name starts at offset +16
    return reinterpret_cast<const char*>(td + 16);
    // Returns ".?AVMyClass@@" or similar
}
```

### Enumerate Vtable Slots

```cpp
void PrintVtable(void* obj, int maxSlots = 32) {
    uintptr_t* vptr = *reinterpret_cast<uintptr_t**>(obj);
    const char* name = GetMSVCClassName(obj);
    printf("vtable for %s:\n", name ? name : "unknown");

    for (int i = 0; i < maxSlots; i++) {
        uintptr_t slot = vptr[i];
        if (!slot) break;

        // Validate it's in executable memory
        MEMORY_BASIC_INFORMATION mbi{};
        if (!VirtualQuery(reinterpret_cast<void*>(slot), &mbi, sizeof(mbi))) break;
        if (!(mbi.Protect & (PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE))) break;

        // Get symbol name if PDB loaded (requires dbghelp)
        char symBuf[512]{};
        SYMBOL_INFO* sym = reinterpret_cast<SYMBOL_INFO*>(symBuf);
        sym->SizeOfStruct = sizeof(SYMBOL_INFO);
        sym->MaxNameLen = 256;

        DWORD64 disp = 0;
        if (SymFromAddr(GetCurrentProcess(), slot, &disp, sym)) {
            printf("  [%2d] 0x%llX  %s+0x%llX\n", i, slot, sym->Name, disp);
        } else {
            printf("  [%2d] 0x%llX\n", i, slot);
        }
    }
}
```

### Hook Import Address Table Entry

```cpp
bool HookIAT(const char* targetDll, const char* targetFunc, void* hookFn, void** outOriginal) {
    uintptr_t base = reinterpret_cast<uintptr_t>(GetModuleHandleW(nullptr));
    auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
    auto* nt  = reinterpret_cast<IMAGE_NT_HEADERS64*>(base + dos->e_lfanew);
    auto& dir = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    if (!dir.VirtualAddress) return false;

    auto* imp = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(base + dir.VirtualAddress);
    for (; imp->Name; imp++) {
        const char* dllName = reinterpret_cast<const char*>(base + imp->Name);
        if (_stricmp(dllName, targetDll) != 0) continue;

        auto* thunk    = reinterpret_cast<IMAGE_THUNK_DATA64*>(base + imp->FirstThunk);
        auto* origThunk= reinterpret_cast<IMAGE_THUNK_DATA64*>(base + imp->OriginalFirstThunk);

        for (; thunk->u1.Function; thunk++, origThunk++) {
            if (origThunk->u1.Ordinal & IMAGE_ORDINAL_FLAG64) continue; // skip ordinal imports

            auto* ibn = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(base + origThunk->u1.AddressOfData);
            if (strcmp(ibn->Name, targetFunc) != 0) continue;

            // Found the IAT slot. Patch it.
            *outOriginal = reinterpret_cast<void*>(thunk->u1.Function);

            DWORD old;
            VirtualProtect(&thunk->u1.Function, sizeof(uintptr_t), PAGE_READWRITE, &old);
            thunk->u1.Function = reinterpret_cast<uintptr_t>(hookFn);
            VirtualProtect(&thunk->u1.Function, sizeof(uintptr_t), old, &old);
            return true;
        }
    }
    return false;
}
```

## Related Material

### Knowledge
- [common-instructions](knowledge/assembly/common-instructions.md)
- [compiler-patterns](knowledge/assembly/compiler-patterns.md)
- [exceptions](knowledge/cpp/exceptions.md)

### Prompts
- [analyze_binary](prompts/analyze_binary.md)
- [analyze_crash](prompts/analyze_crash.md)
- [analyze_memory](prompts/analyze_memory.md)

