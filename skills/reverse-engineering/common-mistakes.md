---
title: Common Reverse Engineering Mistakes
skill: reverse-engineering
category: 
difficulty: intermediate
tags: [pe, windows, loader, asm, x64, kernel, debug, dll]
updated: 2026-07-05
---
# Common Reverse Engineering Mistakes

> Every mistake listed here has derailed real analysis sessions. Learn them and avoid them.

---

## Mistake 1 — Trusting the Decompiler Without Verification

**What happens:** You read the Hex-Rays or Ghidra output, accept its type assignments, and base your analysis on pseudocode that contains errors.

**Why it fails:** Decompilers make incorrect type decisions constantly. They assume a 64-bit value is a pointer when it is an integer. They miss that two separate variables alias the same memory. They misidentify tail calls as local branches.

**Example:**
```c
// Decompiler output (WRONG):
DWORD *v3 = (DWORD *)*(obj + 0x20);
v3[2] = 1;

// Actual ASM:
mov rax, [rcx+20h]   ; load pointer from offset 0x20
mov dword ptr [rax+8], 1  ; write int at offset 0x08 of pointed object
// The decompiler confused byte offset (8) with array index (2).
// v3[2] = index 2 of DWORD array = byte offset 8. Coincidentally correct here,
// but if the type is not DWORD, the meaning changes completely.
```

**Fix:** Always read the disassembly alongside the decompiler. Verify every memory access is correctly typed. When in doubt, look at the `mov` instructions directly.

---

## Mistake 2 — Confusing File Offsets With RVAs and Virtual Addresses

**What happens:** You note an address from a static analysis tool, then search for it in a debugger (or vice versa), and find nothing.

**Why it fails:** Three address spaces exist for any PE:
- File offset: byte position in the file on disk (sections padded to 0x200)
- RVA: offset from ImageBase in memory (sections aligned to 0x1000)
- VA: ImageBase + RVA (changes with ASLR)

**Example:**
```
A function at file offset 0x1200 is in the .text section.
.text: VirtualAddress = 0x1000, PointerToRawData = 0x400
RVA = 0x1200 - 0x400 + 0x1000 = 0x1800
VA (base 0x140000000) = 0x140001800
```

**Fix:** Use the formula: `RVA = FileOffset - PointerToRawData + VirtualAddress` for the section containing the offset. Use PE-bear or IDA's address translator. Never hardcode VAs — always work with RVAs.

---

## Mistake 3 — Not Accounting for ASLR

**What happens:** You find a value in a debugger (e.g., `0x7FF6A1234500`) and hardcode it. On next run, it's at a different address and your code crashes.

**Why it fails:** ASLR randomizes module base addresses on every load. The VA you observed in one session is different the next.

**Fix:**
- Always find the module base at runtime: `GetModuleHandle(nullptr)` for the main executable, or `GetModuleHandle(L"target.dll")` for a DLL
- Store offsets, not absolute addresses: `offset = observed_VA - module_base`
- Verify the offset is stable across multiple runs before using it

---

## Mistake 4 — Missing Inlined Functions

**What happens:** You search for all calls to `sub_XYZ` but find only 2 callers, when the function logic appears in 20 places.

**Why it fails:** The compiler inlined the function at 18 of those call sites. No CALL instruction exists; the body is duplicated in place. IDA cross-references only show explicit CALL instructions.

**Example:**
```asm
; Function "compare_strings" inlined into caller:
; (No call instruction — code is directly embedded)
mov rdi, rcx
mov rcx, rdx
mov rdx, rdi
repe cmpsb
sete al
movzx eax, al
; ... continues with caller code
```

**Fix:**
- Use FLIRT signatures to detect known library functions even when inlined
- Search for the characteristic byte sequence of the function with a pattern scanner
- When analyzing security-critical functions (input validation, bounds checks), always scan for inline copies

---

## Mistake 5 — Assuming Tail Calls Are Local Jumps

**What happens:** At the end of a function you see `jmp sub_XYZ` and think it's a loop or early exit within the function. You miss that it's a call to a completely different function.

**Why it fails:** Tail call optimization replaces `call sub_XYZ / ret` with `jmp sub_XYZ`. The stack frame is deallocated before the jump. The target function returns directly to the original caller.

**Example:**
```asm
ProcessCommand:
  sub rsp, 28h
  ; ... do work ...
  add rsp, 28h     ; stack restored
  jmp sub_140001800  ; THIS IS A CALL TO sub_140001800, not a loop!
```

**Fix:** At the end of a function (after the epilogue `add rsp, N`), any `jmp` to a subroutine is a tail call. Follow the jump target as if it were a call. In IDA, these are displayed with a different icon.

---

## Mistake 6 — Not Handling Anti-Debug Before Dynamic Analysis

**What happens:** You attach a debugger and the binary crashes, hangs, produces garbage output, or enters a different code path than normal execution.

**Why it fails:** Anti-debug checks fire and the binary detects the debugger. It then:
- Exits immediately
- Spawns the real logic in a separate process
- Decrypts code incorrectly
- Corrupts its own data structures deliberately

**Fix:**
1. Load ScyllaHide before attaching
2. Patch PEB.BeingDebugged = 0 immediately after system breakpoint
3. Patch PEB.NtGlobalFlag = 0
4. Patch heap debug flags
5. Use hardware breakpoints instead of software
6. Use "System Breakpoint" pause setting so you stop before TLS callbacks

Do not proceed with dynamic analysis until you have confirmed behavior matches non-debugger execution.

---

## Mistake 7 — Ignoring TLS Callbacks

**What happens:** You set a breakpoint at the entry point. The binary already has anti-debug checks in place that you never see fire.

**Why it fails:** TLS callbacks execute before the entry point. They are listed in the PE's TLS directory and invoked by the loader.

**Fix:**
- In x64dbg: Options → Preferences → Events → check "TLS Callbacks"
- The debugger will now pause at each TLS callback before reaching the entry point
- Set breakpoints inside TLS callbacks to observe their logic

---

## Mistake 8 — Pattern Scanning With Insufficient Wildcards

**What happens:** Your pattern works on one binary version but fails on the next.

**Why it fails:** Relative operand bytes (call targets, LEA offsets, MOV immediate addresses) change when the binary is recompiled or rebased. If you included these bytes in your pattern without wildcarding them, the pattern becomes version-specific.

**Example:**
```
BAD pattern:  48 83 EC 28 E8 A3 1F 00 00  (includes call relative offset)
GOOD pattern: 48 83 EC 28 E8 ?? ?? ?? ??  (wildcards the relative 4-byte offset)
```

**Rule:** Any 4-byte or 8-byte sequence that encodes an address (relative or absolute) must be wildcarded. This includes:
- `E8 xx xx xx xx` (call rel32)
- `E9 xx xx xx xx` (jmp rel32)
- `48 8D 05 xx xx xx xx` (LEA rax, [rip + disp32])
- `FF 15 xx xx xx xx` (call [rip + disp32]) — indirect call through IAT
- `48 B8 xx xx xx xx xx xx xx xx` (MOV rax, imm64) — absolute address

---

## Mistake 9 — Confusing Multiple Inheritance vtable Layout

**What happens:** You read a vtable expecting class A's methods but the slots are all wrong. You find the function at `vtable[0]` adjusts a pointer and jumps elsewhere.

**Why it fails:** With multiple inheritance, an object has multiple vtable pointers. The second (and subsequent) base class vtables contain **thunks** — small stubs that adjust `this` before calling the actual implementation.

**Example:**
```cpp
struct B { virtual void fb(); };
struct C : A, B { void fb() override; };

// When accessing C as B*, the vptr points to C's B-subobject vtable:
// vtable_C_for_B:
//   slot 0:  thunk { sub rcx, 0x10; jmp C::fb }
//
// NOT slot 0:  C::fb directly
```

**Fix:** When you find a vtable slot pointing to a tiny stub that adjusts `rcx` and jumps, that's a thunk for multiple inheritance. The real implementation is the jump target. Always check for thunks when working with vtables.

---

## Mistake 10 — Reading Packed Binary As If It's Normal Code

**What happens:** You open a packed binary in IDA, analyze functions at the entry point, find nonsensical code, and spend hours trying to understand it.

**Why it fails:** The code you're analyzing is the unpacking stub, not the actual program logic. The real code is encrypted or compressed and only exists in memory after the stub runs.

**Detection checklist:**
- Section entropy > 7.0 bits/byte → strong packing indicator
- Import table: only `LoadLibrary` + `GetProcAddress` → manual IAT resolution after unpack
- Entry point in non-default section (not .text)
- `VirtualAlloc` + `VirtualProtect` + large `memcpy` near entry → unpacking in progress

**Fix:** Always check for packing before static analysis. Unpack first (see workflow.md Phase 2), then analyze the unpacked dump.

---

## Mistake 11 — Hardcoding Struct Offsets Without Documentation

**What happens:** Your code uses `*(int*)(obj + 0x58)` everywhere. A new binary version shifts all offsets by 8 bytes and everything breaks silently — you read the wrong field.

**Fix:** Define struct types in IDA. Name every field. Apply the struct type to all object pointers. When offsets change in a new version, updating the struct propagates everywhere.

```c
// BAD:
int hp = *(int*)(player + 0x78);
int mp = *(int*)(player + 0x7C);

// GOOD:
struct PlayerStats {
    /* 0x00 */ void* vptr;
    /* 0x08 */ float x, y, z;
    /* 0x14 */ int _pad;
    /* 0x18 */ char name[64];
    /* 0x58 */ int level;
    /* 0x5C */ int _pad2;
    /* 0x60 */ float maxHp;
    /* 0x64 */ float currentHp;  // the field you meant
    /* 0x78 */ int currency;      // not hp!
};
int hp = player->currentHp;
```

---

## Mistake 12 — Confusing Import-by-Ordinal With Import-by-Name

**What happens:** You see an import thunk in IDA with no name. You skip over it thinking it's an unresolved symbol. The function turns out to be critical.

**Why it fails:** Some DLLs export functions by ordinal only (no name string). IDA shows `ntdll_73` or `Ordinal_73`.

**Fix:**
- Check the exporting DLL: use `dumpbin /exports ntdll.dll` or PE-bear
- Map ordinal numbers to function names
- Update the import in IDA with the correct name and prototype
- Note: undocumented ordinal exports in ntdll, kernel32 often wrap interesting functionality

---

## Mistake 13 — Not Verifying Pointer Chain Stability

**What happens:** You find a pointer chain that works during your testing session. Hours later, the chain returns null or garbage.

**Why it fails:** Pointer chains through dynamically allocated objects are only stable as long as those objects exist at those addresses. If the game/application reallocates them (e.g., on level load, map change, restart), all chains rooted in those objects break.

**Fix:**
- Verify the chain from multiple restarts, not just one session
- Check whether intermediate pointers change on key application events
- Prefer pointer chains rooted in static data (.data/.rdata), not in heap objects
- For each intermediate node, check if it's stable across the events that matter

---

## Mistake 14 — Over-Relying on String References

**What happens:** You find a string like `"Authentication failed"`, follow the XREFs, find a function, and conclude it's the authentication function. You spend hours analyzing the wrong function.

**Why it fails:** Error strings are often centralized in logging functions. The XREF to `"Authentication failed"` may point to a logging helper that is called from dozens of unrelated places, not directly from the authentication logic.

**Fix:**
- Follow XREFs multiple levels up until you find a function with meaningful context
- Check whether the function containing the string is a generic logger (takes a string arg + varargs) vs specific logic
- Use strings as hints, not as definitive identification
- Corroborate with import usage and calling context

---

## Mistake 15 — Forgetting About Exception Handler Metadata

**What happens:** You see an indirect call target that doesn't appear in any vtable or function pointer. You can't figure out where it's called from.

**Why it fails:** MSVC exception handling uses `.pdata` and `.xdata` sections to register exception handler functions. These are invoked by the OS exception dispatcher, not by direct CALL instructions. There are no code-level XREFs.

These include:
- `__except` filter expressions and bodies
- `__finally` blocks
- Destructor functions called during stack unwind
- C++ catch blocks

**Fix:**
- In IDA: View → Open Subviews → Exception Handlers (IDA can parse .pdata)
- Look for function entries in `.pdata` (array of `RUNTIME_FUNCTION` structures)
- Destructor calls during unwind appear as `UNW_OP_PUSH_MACHFRAME` + `UWOP_SET_FPREG` entries — check .xdata for unwind codes

---

## Mistake 16 — Analyzing the Wrong Architecture

**What happens:** You load a DLL in IDA Pro x64. The analysis looks wrong. Some functions make no sense.

**Why it fails:** The binary is a fat binary or contains mixed-architecture code. Some DLLs have:
- ARM64 + x64 sections (Windows on ARM)
- A 32-bit PE stub that loads a 64-bit DLL
- Mixed x86/x64 code via WOW64 transitions

**Fix:**
- Check `IMAGE_FILE_HEADER.Machine` value in PE-bear before loading
- For ARM64EC binaries: IDA requires the correct processor module (ARM64)
- For WOW64: the 32-bit code runs in a 32-bit context, not 64-bit

---

## Mistake 17 — Missing COMDAT Folding / ICF

**What happens:** You rename function A. Then you find that function B (with identical code) also has the same address and gets renamed. Even worse: callers you expected to call A are actually calling B's address.

**Why it fails:** Identical Code Folding (ICF / COMDAT folding) merges functions with identical machine code. Multiple source-level functions map to one address.

**Fix:**
- Be aware that one address may represent multiple logical functions
- When XREFs seem too broad for a function's apparent purpose, check for ICF
- In IDA, multiple names pointing to the same address is a sign of ICF
- Document all known identities of an address in a comment

---

## Mistake 18 — Running Hot Code Under Single-Step

**What happens:** You single-step through a function. It takes 30 seconds to step through what should be a tight loop. Or worse: you trigger a timing-based anti-debug check and the binary takes a different path.

**Why it fails:** Single-stepping has massive overhead: every step fires a debug exception, context switches occur, the target effectively runs 1000x slower. Timing checks compare RDTSC or GetTickCount before and after suspect regions — single-stepping makes every region look "too slow."

**Fix:**
- Use run-to-cursor (`F4` in x64dbg) instead of single-step for code you don't need to inspect
- Set a breakpoint at the exit of the hot region, then run at full speed
- Reserve single-step for the specific lines you need to understand
- In timed regions: only use hardware execute breakpoints (no INT3 overhead)

## Related Material

### Knowledge
- [common-instructions](knowledge/assembly/common-instructions.md)
- [compiler-patterns](knowledge/assembly/compiler-patterns.md)
- [exceptions](knowledge/cpp/exceptions.md)

### Prompts
- [analyze_binary](prompts/analyze_binary.md)
- [analyze_crash](prompts/analyze_crash.md)
- [analyze_memory](prompts/analyze_memory.md)

