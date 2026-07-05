# Reverse Engineering Best Practices

> Principles and habits of professional reverse engineers. These apply whether you are analyzing malware, performing vulnerability research, or understanding proprietary software.

---

## 1. Always Work From a Snapshot

**Never analyze a potentially malicious binary on a non-snapshotted machine.**

Create a VM snapshot before launching any unknown binary. If analysis goes wrong — accidental execution, exploit triggered, side effects on disk or network — you can restore in seconds.

Snapshot discipline:
- Snapshot before loading a binary into any debugger
- Snapshot after completing major analysis milestones
- Keep at least a "clean" and a "working" snapshot
- Never reuse a compromised sandbox without reverting

---

## 2. Trust Disassembly Over Decompiler Output

The decompiler produces a human-friendly approximation. It makes assumptions:
- Type assignments based on usage patterns
- Control flow structuring that may not match the original
- Expression simplification that loses precision

**Rule:** When the decompiler and disassembly disagree about semantics, disassembly is correct.

Common decompiler mistakes to watch for:

| Decompiler output          | Actual ASM semantics                            |
|----------------------------|-------------------------------------------------|
| `a = b * 2 + c`            | `lea rax, [rbx + rcx*2]` (not two operations)  |
| `if (a < 0)`               | `js` (signed), but value is treated unsigned elsewhere |
| `v1 = v2;`                 | May be a byte/word copy but shown as 64-bit     |
| `*(int *)(obj + 0x28)`     | Member access of unknown struct; type is guessed|

---

## 3. Use Evidence-Based Renaming

Never rename a function or variable unless you have concrete evidence.

**Acceptable evidence:**
- RTTI class name (`.?AVClassName@@` → the class is `ClassName`)
- PDB symbol name (most reliable)
- Export name from DLL (reliable)
- Error message string referenced by function (`"Failed to open database"` → function relates to DB opening)
- Import called exclusively from this function (`CreateMutex` called nowhere else → mutex-related)
- Two or more independent signals that agree

**Not acceptable:**
- "It looks like a hash function" — call it `possible_hash_func` until confirmed
- "It probably initializes something" — use `sub_140001234` until you know more
- Speculation from decompiler variable naming

Bad naming propagates errors. A wrong class name will mislead every analysis that follows.

---

## 4. Never Assume the Decompiler Has Correct Types

Always verify pointer types against memory layout evidence:

```cpp
// Decompiler shows:
DWORD *v1 = some_function();
v1[4] = 0;

// This doesn't mean it's a DWORD array.
// It means: *(some_function() + 0x10) = 0
// The type is unknown. Find where the pointer came from.
// Look at what created the object (constructor, factory function).
// Look at what other fields are accessed and what values they hold.
```

Build structs incrementally:
1. Find the constructor — it initializes all fields
2. Map each `[this + offset] = value` in the constructor to a field
3. Find all member accesses throughout the codebase
4. Assign types based on how values are used (passed to known APIs, compared to constants, etc.)

---

## 5. Cross-Reference Everything

Every important address should be examined from multiple angles:

| What to look at | How |
|----------------|-----|
| Who calls this function? | Press X on function name in IDA |
| What reads this global? | Press X on global variable |
| What writes this struct field? | Data XREFs on the field offset |
| Where is this vtable used? | XREFs on the vtable address |
| Where is this string referenced? | XREFs on the string |

Orphaned code (no XREFs) means either:
- Function is called indirectly (through vtable or function pointer) — search for its address in .rdata
- Function is exported — check export table
- Function is dead code — verify by searching for the function's address as a literal constant
- IDA missed recognizing it as code — manually create a function at the address

---

## 6. Track Reversals Systematically

Maintain a log of everything you discover:

```markdown
## Analysis Log

### 2026-07-04

Function sub_14001F800:
  - Called from sub_14002A100 (3x) and sub_14002B000 (1x)
  - First arg (rcx) is a pointer that vtable[-1] identifies as .?AVChatClient@@
  - Second arg (rdx) is an int32 that is compared to 0x11, 0x12, 0x13 (message type IDs)
  - Contains switch that dispatches based on second arg
  - Conclusion: ChatClient::HandleIncomingMessage(int messageType)
  - Renamed: ChatClient__HandleIncomingMessage
  - Confidence: HIGH

Global at .data:0x14020A000:
  - Written at startup with a VirtualAlloc result
  - Read in ChatClient__HandleIncomingMessage
  - 8-byte pointer -> heap object
  - Conclusion: likely g_chatManager or similar singleton
  - Confidence: MEDIUM
```

This log is invaluable when returning to a binary after days away.

---

## 7. Handle Anti-Debug Properly

Always handle anti-debug before doing meaningful dynamic analysis. If you don't, the binary modifies its own behavior and you analyze the wrong thing.

**ScyllaHide is not enough by itself.** Always verify:

1. **PEB.BeingDebugged** (offset 0x002): patch to 0 in debugger memory
2. **PEB.NtGlobalFlag** (offset 0x0BC on x64): patch to 0
3. **Heap flags** (HeapBase+0x70 and HeapBase+0x74 on x64): mask out debug bits
4. **TLS callbacks**: set breakpoints in x64dbg's TLS callback pause setting
5. **Timing checks**: run at full speed, don't single-step through timed sections
6. **NtQueryInformationProcess hooks**: ScyllaHide covers most, verify with API Monitor

After bypassing anti-debug, revert to a snapshot and re-run to confirm the binary behaves normally.

---

## 8. Build and Use Pattern Signatures

For functions you need to locate across binary versions, create pattern signatures rather than hardcoding offsets.

**Good signature:**
- Minimum 12–16 bytes
- Wildcards `??` on all relative operand bytes (calls, jumps, LEA operands)
- Unique within the binary (test with a scanner)
- Points to the first byte of the function

**Signature placement:**
- If the first 5 bytes are a `call` (which differs per version), start at byte 5
- Skip preamble bytes that may vary (branch hints, NOP padding)
- Use the most characteristic opcode sequence (the part that reflects the algorithm, not the calling convention setup)

**Verify signatures against at least 3 versions** of the binary. A signature that breaks on version N+1 is worse than no signature — it silently returns wrong addresses.

---

## 9. Understand Section Semantics Before Patching

Before writing any patch:

| Section  | Characteristics                       | How to write               |
|----------|---------------------------------------|----------------------------|
| `.text`  | RX (read, execute)                    | VirtualProtect PAGE_EXECUTE_READWRITE |
| `.rdata` | R (read only)                         | VirtualProtect PAGE_READWRITE (loses write protection) |
| `.data`  | RW (read, write)                      | Direct write, already writable |

Patching `.rdata` (vtables) is detectable: the memory type changes from IMAGE (shared) to PRIVATE (COW copy). Integrity-checking anti-cheat tools scan for this.

---

## 10. Validate Pointer Chains Before Using Them

Multi-level pointer dereferences can crash if any intermediate is null or unmapped.

**Safe dereference pattern:**
```cpp
// BAD: crashes if any pointer is invalid
float health = *(float*)(**(void***)(moduleBase + 0x1A2B4C8) + 0x78 + 0x10);

// GOOD: validate each level
uintptr_t base = moduleBase + 0x1A2B4C8;
if (!IsValidPtr(base)) return false;
uintptr_t lvl1 = *(uintptr_t*)base;
if (!IsValidPtr(lvl1)) return false;
uintptr_t lvl2 = *(uintptr_t*)(lvl1 + 0x10);
if (!IsValidPtr(lvl2)) return false;
float health = *(float*)(lvl2 + 0x78);
```

**IsValidPtr implementation:**
```cpp
bool IsValidPtr(uintptr_t addr) {
    if (addr < 0x1000) return false;        // null-like
    if (addr > 0x7FFFFFFFFFFF) return false; // kernel space / non-canonical
    MEMORY_BASIC_INFORMATION mbi;
    if (!VirtualQuery((void*)addr, &mbi, sizeof(mbi))) return false;
    return mbi.State == MEM_COMMIT &&
           (mbi.Protect & (PAGE_READABLE_MASK)) != 0 &&
           (mbi.Protect & PAGE_GUARD) == 0;
}
```

---

## 11. Pattern Scan at the Right Time

Pattern scanning works on mapped memory, not file offsets. Scan after the module is loaded:

- For in-process: scan at any point after `LoadLibrary` / the module is visible in PEB
- For out-of-process: use `ReadProcessMemory` to scan pages, checking `VirtualQueryEx` first
- Restrict scan to `MEM_COMMIT | MEM_IMAGE` pages with execute permissions
- Never scan the entire address space — it's slow and crashes on guard pages

If a pattern fails to find a match:
1. Verify the pattern bytes are correct (check in debugger at the function)
2. Check if the binary version changed and opcodes shifted
3. Check if the function was inlined (no standalone copy exists)
4. Check if COMDAT folding merged it with another function

---

## 12. Annotate Crypto Immediately

When you find encryption or hashing code:

1. **Identify the algorithm** from constants: AES round constants, SHA round constants, RC4 state size, MD5/SHA1 magic numbers
2. **Note the key source**: hardcoded in .rdata, derived from password, from network, from registry
3. **Note the mode**: ECB, CBC, CTR — look for IV parameter, XOR with previous block
4. **Document the interface**: what are the inputs and outputs, what struct is used for state

Do this immediately while the code is in context. Crypto functions look similar to each other and become confusing after you move on.

**Common crypto constants to recognize:**

| Constant         | Algorithm    | Value              |
|------------------|--------------|--------------------|
| 0x9E3779B9       | MD5 init / general hash | Little-endian Fibonacci |
| 0x67452301       | MD5 A        | First 32-bit word  |
| 0x6A09E667       | SHA-256 H0   |                    |
| 0x428A2F98       | SHA-256 K[0] |                    |
| 0x5A827999       | SHA-1 K[0]   |                    |
| 0x61707865       | ChaCha20     | "expa"             |
| 0x63766172       | ChaCha20     | "arve"             |
| AES S-Box        | AES          | 256-byte lookup starting 0x63, 0x7C, 0x77... |

---

## 13. Maintain a Private Vocabulary

Develop consistent naming conventions before starting a large binary:

```
// Suggested naming scheme:

// Classes (from RTTI or inferred)
ClassName__MethodName                 // member functions
vtable_ClassName                      // vtable address
TypeDescriptor_ClassName              // RTTI TypeDescriptor

// Free functions
module_purpose_verb                   // e.g., net_socket_connect
sub_XXXXXXXX                          // unknown, keep IDA default

// Globals
g_singleton_type                      // singleton pointer
g_array_type                          // global array
s_local_static_name                   // function-level static

// Confidence markers
// Append _CONFIRM for high-confidence names
// Keep sub_ prefix until confirmed
```

---

## 14. Version the IDA Database

IDA .i64 / .idb files are version-specific. If you're tracking a target across updates:

- Name the IDB with the binary hash: `target_sha256_first8.i64`
- Export notes periodically: File -> Produce File -> Create MAP File
- Use IDC/IDAPython to export all names: `idc.get_name(ea)` iteration
- Store names/comments in a version-controlled file alongside each IDB
- When a new version drops: diff the exports list, transfer names where offsets match

---

## 15. Use Hardware Breakpoints for Sensitive Targets

Software breakpoints (INT3 = 0xCC) modify memory. Anti-cheat and anti-debug systems read their own code looking for 0xCC bytes.

Hardware breakpoints use CPU debug registers DR0–DR3. They never modify memory.

```
Capacity: 4 hardware BPs per thread
Types: Execute, Write, Read/Write (access)
Width: 1, 2, 4, or 8 bytes

x64dbg: right-click address -> Breakpoint -> Hardware, Execute
WinDbg: ba e1 address         # break on execute, 1-byte
        ba r4 address         # break on read/write, 4-byte
```

Limitations:
- Only 4 per thread
- Can be cleared by the target if it writes to DR0–DR3 via SetThreadContext
- Detectable by calling GetThreadContext and checking DR registers
- For detecting DR manipulation: monitor NtSetContextThread calls

---

## 16. Performance Considerations for RE Tools

| Operation                          | Typical cost                        |
|------------------------------------|-------------------------------------|
| IDA auto-analysis, medium DLL      | 5–30 seconds                        |
| Hex-Rays decompile, complex func   | 100ms – 5s                          |
| Pattern scan, 100MB binary         | ~10ms in memory, ~500ms from disk   |
| RTTI enumeration IDAPython script  | 1–10 seconds                        |
| IDA full database save (.i64)      | 1–10 seconds                        |
| Cross-reference computation        | Fast for < 100K functions, slow for 1M+ |

Tips for large binaries (50MB+):
- Disable "Coagulate subs" in analysis options (creates very large functions)
- Disable "Find and create function tails" to speed initial analysis
- Run IDAPython enumeration scripts with batch mode (`idc.auto_wait()`)
- Use Ghidra for large game binaries — its analysis is more parallelized

## Related Material

### Knowledge
- [common-instructions](knowledge/assembly/common-instructions.md)
- [compiler-patterns](knowledge/assembly/compiler-patterns.md)
- [exceptions](knowledge/cpp/exceptions.md)

### Prompts
- [analyze_binary](prompts/analyze_binary.md)
- [analyze_crash](prompts/analyze_crash.md)
- [analyze_memory](prompts/analyze_memory.md)

