# Windows Reverse Engineering - Core Concepts

> Written for senior software engineers. Assumes familiarity with x86/x64 assembly, C++, and Windows internals.

---

## 1. Disassembly vs Decompilation

### Disassembly

Disassembly converts raw machine bytes back into human-readable assembly mnemonics. It is a lossless representation of the instruction stream.

**Linear Sweep**: Starts at a known offset and decodes every byte sequentially. Fast, but can misinterpret data interleaved with code (jump tables in .text).

**Recursive Descent**: Follows actual control flow. More accurate but incomplete: indirect calls (`call rax`) require dynamic analysis to resolve.

IDA Pro uses a hybrid approach with FLIRT and code analysis heuristics to distinguish code from data.

**What gets preserved in disassembly:**
- All original instruction bytes and semantics
- Relative offsets in jumps and calls (after relocation)
- Register usage and memory access patterns

**What gets lost:**
- Original variable and function names (unless symbols present)
- Type information (a DWORD and a float look identical at byte level)
- High-level constructs: loops, conditions, structs are inferred not recovered
- Comments, intent, and algorithmic logic

### Decompilation

Decompilation reconstructs pseudo-C or pseudo-C++ from disassembly. IDA Hex-Rays, Ghidra, and Binary Ninja all do this.

The process:
1. **Lifting** to an IR (IDA: microcode; Ghidra: P-code; BN: MLIL to HLIL)
2. **Analysis passes**: dead code elimination, expression simplification, type propagation
3. **Structuring**: converting CFG back to if/else, loops
4. **Type recovery**: using calling conventions, RTTI, import signatures

**What gets lost in decompilation:**
- Exact instruction selection (LEA used for arithmetic shows as `a + b*2`)
- Optimization artifacts (CMOV becomes ternary, loses branch-avoidance intent)
- Calling convention nuances hidden by the decompiler abstraction
- Inline assembly shown as intrinsics or raw hex

**Critical**: The decompiler output is a guess. Always verify against disassembly. Wrong type assignments propagate bad results everywhere.

---

## 2. Static vs Dynamic Analysis

### Static Analysis

Analyzing the binary without executing it. Tools: IDA Pro, Ghidra, Binary Ninja, PE-bear, CFF Explorer, strings.exe, dumpbin.

**Strengths:**
- Safe (no code runs)
- Entire binary visible at once
- Cross-references, call graphs, data flow all available
- Reproducible: same binary, same results

**Weaknesses:**
- Packed/obfuscated code requires unpacking first
- Indirect calls need dynamic validation
- Encrypted strings or runtime-generated code invisible
- Cannot observe runtime values, heap layouts, or race conditions

**Use for:** First pass. PE structure, imports, exports, embedded strings, codebase size. Malware analysis where execution is dangerous.

### Dynamic Analysis

Running the binary and observing behavior. Tools: x64dbg, WinDbg, Frida, Process Monitor, Wireshark, API Monitor.

**Strengths:**
- Resolves all indirect calls at runtime
- Unpacks/decrypts code automatically
- Real memory layouts, live vtable pointers, actual heap state
- Enables runtime patching and experimentation

**Weaknesses:**
- Anti-debug measures may alter behavior
- Requires a safe environment (VM, sandbox)
- Time-consuming for large codebases
- Behavior may vary across runs (ASLR, timing, network state)

**Use for:** After static triage. Resolving indirect dispatch. Unpacking. Measuring timing-sensitive behavior.

### Combined Workflow

```
Static triage
  -> identify interesting functions
  -> Dynamic: run to target, observe live state
  -> Back to static: apply dynamic findings
  -> Iterate
```

---

## 3. Symbols: Exports, RTTI, PDB, Stripped Binaries

### Export Table

Lists functions by name and/or ordinal that a DLL exposes. Most reliable symbols without a PDB.

In IDA: View -> Open Subviews -> Exports
In x64dbg: Symbols tab

The export directory contains function names, ordinals, and RVAs. Forward exports (pointing to another DLL) are also possible.

### RTTI (Run-Time Type Information)

MSVC generates RTTI for any class with at least one virtual function. Structures live in .rdata:

```
Complete Object Locator (COL)
  +-- Signature (0 = x86, 1 = x64)
  +-- Offset (object base to vtable pointer)
  +-- pTypeDescriptor -> TypeDescriptor
  |     +-- pVFTable (RTTI type info vtable)
  |     +-- name[] -> mangled class name (".?AVFoo@@")
  +-- pClassDescriptor -> ClassHierarchyDescriptor
        +-- numBaseClasses
        +-- pBaseClassArray[] -> BaseClassDescriptor[]
```

In x64 binaries, pointers inside RTTI are stored as RVAs (relative to module base). You must add the module base to resolve them.

Vtable layout:
```
[object + 0]  ->  vtable*
vtable[-1]    ->  Complete Object Locator*
vtable[0]     ->  virtual function slot 0
vtable[1]     ->  virtual function slot 1
vtable[N]     ->  virtual function slot N
```

### PDB Files

Program Database files contain: function names, types, source file/line maps, local variable names, struct layouts, enum values.

Setting up a symbol server:
```
_NT_SYMBOL_PATH=srv*C:\Symbols*https://msdl.microsoft.com/download/symbols
```

Public Microsoft symbol server covers all system DLLs. Load in IDA: File -> Load File -> PDB File.

### Stripped Binaries: Recovery Strategies

1. **FLIRT signatures**: IDA matches library functions (CRT, STL) against known patterns
2. **RTTI**: Class names recoverable unless compiled with /GR-
3. **Import inference**: A function calling CreateFile then ReadFile in a loop is a file reader
4. **String cross-references**: Error messages and log strings identify functionality
5. **PDB path**: The PE debug directory embeds the original PDB path. Sometimes findable on public symbol servers

---

## 4. Calling Conventions

### x64 Windows ABI (Microsoft)

**Integer and Pointer Arguments (first 4):**

| Argument | Register |
|----------|----------|
| 1st      | RCX      |
| 2nd      | RDX      |
| 3rd      | R8       |
| 4th      | R9       |
| 5+       | Stack, right to left, above shadow space |

**Floating-Point Arguments:**

| Argument | Register |
|----------|----------|
| 1st      | XMM0     |
| 2nd      | XMM1     |
| 3rd      | XMM2     |
| 4th      | XMM3     |

Slot position determines register: if 2nd arg is float, it uses XMM1 regardless of what the 1st arg type was.

**Return Values:**
- Integer/pointer <= 64 bits: RAX
- Float/double: XMM0
- Structs <= 16 bytes: RAX:RDX
- Structs > 16 bytes: caller allocates storage, passes pointer in RCX (other args shift right)

**Shadow Space (Home Space):**
Caller allocates 32 bytes on the stack before every call. Reserved for the callee to spill RCX/RDX/R8/R9. Always present even if unused.

```
Stack layout immediately after CALL (low to high):
  RSP+0x00  ->  return address
  RSP+0x08  ->  shadow[0]  (RCX home)
  RSP+0x10  ->  shadow[1]  (RDX home)
  RSP+0x18  ->  shadow[2]  (R8 home)
  RSP+0x20  ->  shadow[3]  (R9 home)
  RSP+0x28  ->  arg5 (if present)
  RSP+0x30  ->  arg6 (if present)
```

**Volatile vs Non-Volatile Registers:**

| Type         | Registers                                     |
|--------------|-----------------------------------------------|
| Volatile     | RAX, RCX, RDX, R8, R9, R10, R11, XMM0-XMM5   |
| Non-Volatile | RBX, RBP, RDI, RSI, RSP, R12-R15, XMM6-XMM15 |

**This pointer in MSVC C++ methods:**
Passed in RCX (1st argument slot). Other args shift: RDX, R8, R9, then stack.

### x86 Calling Conventions

**cdecl:**
- Args pushed right-to-left
- Caller cleans stack (add esp, N after call)
- Return: EAX (or EDX:EAX for 64-bit)

**stdcall (Win32 API standard):**
- Args pushed right-to-left
- Callee cleans stack (ret N)
- Decorated name: _FunctionName@bytes (e.g., _CreateFileA@28)

**fastcall (MSVC __fastcall):**
- First two integer args in ECX, EDX
- Remaining pushed right-to-left
- Callee cleans stack

**thiscall (MSVC C++ members):**
- this pointer in ECX
- Args pushed right-to-left
- Callee cleans stack
- GCC uses cdecl with this as first stack arg

---

## 5. Stack Frames

### Typical x64 Prologue Patterns

```asm
; Pattern 1: With frame pointer (less common in MSVC Release)
push rbp
mov  rbp, rsp
sub  rsp, 0x50

; Pattern 2: No frame pointer (typical MSVC /O2)
sub rsp, 0x68      ; shadow(32) + locals + alignment

; Pattern 3: No locals, no calls (leaf function)
; No prologue at all
```

### x64 Stack Layout During Execution

```
  [higher addresses]
  |  arg6           |  <- [rsp + callee_frame + 0x30]
  |  arg5           |  <- [rsp + callee_frame + 0x28]
  |  shadow[3]      |  <- [rsp + callee_frame + 0x20]
  |  shadow[2]      |  <- [rsp + callee_frame + 0x18]
  |  shadow[1]      |  <- [rsp + callee_frame + 0x10]
  |  shadow[0]      |  <- [rsp + callee_frame + 0x08]
  |  return addr    |  <- [rsp + callee_frame + 0x00]
  |  local var N    |  <- [rsp + N]
  |  ...            |
  |  local var 0    |  <- [rsp + 0x08]
  |  saved XMM regs |  <- (if non-volatile XMM used)
  [lower addresses]  <- RSP after prologue
```

### Epilogue

```asm
add rsp, 0x68      ; mirror the prologue sub
ret                ; or pop rbp / ret if frame pointer used
```

### Stack Alignment Rules

RSP must be 16-byte aligned at every CALL instruction. CALL pushes 8 bytes (return address), so inside the callee before prologue, RSP is 8-byte misaligned. The prologue sub must bring total alignment back to 16. Common values: sub rsp, 0x28 (5*8), 0x38, 0x48, 0x58, 0x68.

---

## 6. Mitigations

### ASLR (Address Space Layout Randomization)

Randomizes module base addresses. DLLs are randomized system-wide per boot (not per-process).

PE flags:
- IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE (0x0040): ASLR enabled
- IMAGE_DLLCHARACTERISTICS_HIGH_ENTROPY_VA (0x0020): 64-bit ASLR

**RE implications:**
- Never hardcode virtual addresses. Use RVAs.
- Module base discovery: GetModuleHandle(), PEB.Ldr walk, EnumProcessModules()
- ASLR can be defeated by info leaks exposing pointer values

### DEP/NX (Data Execution Prevention)

Stack and heap pages marked non-executable. Executing from these pages triggers an access violation.

**RE implications:**
- Code injection must target executable regions or allocate with PAGE_EXECUTE_*
- VirtualAlloc(PAGE_EXECUTE_READWRITE) for JIT-generated hooks

### CFG (Control Flow Guard)

Compiler-inserted check before indirect calls validates target is in the CFG bitmap of legitimate targets.

PE flag: IMAGE_DLLCHARACTERISTICS_GUARD_CF (0x4000)

**RE implications:**
- Vtable overwrite hooks may trigger CFG
- IAT hooks may be validated by CFG
- The CFG bitmap is in _IMAGE_LOAD_CONFIG_DIRECTORY
- Bypass requires registering the hook target as a valid CFG target or disabling CFG

### SafeSEH (x86 Only)

PE table of valid exception handlers. OS verifies handler is in this table before calling it. x64 uses table-based unwind info in .pdata instead.

---

## 7. Obfuscation Techniques

### Packing

Compresses or encrypts original code. A stub decompresses at runtime and jumps to the Original Entry Point (OEP).

**Detection indicators:**
- Section entropy > 7.0 bits/byte
- Imports limited to LoadLibrary and GetProcAddress
- Unusual section names: .UPX0, .nsp0, MPRESS1
- Tiny import table relative to file size

**Analysis approach:**
1. Run under x64dbg with ScyllaHide
2. Let unpacking stub execute
3. Break at OEP (use "find OEP by Section Hop" in x64dbg)
4. Dump with Scylla: get imports, fix dump

### Virtualization-Based Obfuscation

Translates native instructions to a proprietary bytecode executed by an embedded VM interpreter. Tools: VMProtect, Themida, Code Virtualizer.

**Characteristics:** Large dispatcher loop, custom opcode table, no recognizable x64 instructions in protected regions.

**Analysis approach:**
1. Identify the VM entry stub (usually a call before the obfuscated region)
2. Find the VM dispatcher (large switch or computed jump)
3. Map VM opcodes to semantics by tracing execution
4. VMAttack IDA plugin can automate some analysis

### Control Flow Flattening (CFF)

All basic blocks become switch cases. A state variable controls execution order.

```
Original: if (x) A(); B();
Flattened:
  state = INIT
  while(1):
    switch(state):
      INIT: state = x ? A_STATE : B_STATE
      A_STATE: A(); state = B_STATE
      B_STATE: B(); return
```

**Analysis approach:**
- Identify the dispatcher variable
- Trace all state transitions
- Reconstruct original CFG
- Tools: D810 (IDA plugin), miasm, angr symbolic execution

### Opaque Predicates

Always-true or always-false conditions that appear non-trivial to static analysis. Used to insert dead code that confuses disassemblers and decompilers.

---

## 8. Compiler Optimizations Affecting RE

### Function Inlining

Callee body is inserted directly at the call site. No CALL instruction, no cross-references to the inlined function.

**RE impact:** Functions appear larger and more complex. Requires pattern matching to identify inlined helper functions.

### Tail Call Optimization (TCO)

The last call in a function becomes a JMP instead of CALL+RET.

```asm
; Source: return OtherFunc(args);
; Without TCO:  call OtherFunc / ret
; With TCO:     jmp  OtherFunc
```

**RE impact:** The JMP looks like a local branch. Easy to think a function ends before the tail call target. The callee's ret serves as the epilogue for both.

### COMDAT Folding / ICF

Linker merges functions with identical machine code to a single address.

**RE impact:** Multiple distinct source functions map to one address. XREFs mislead about which callers are logically distinct.

### Devirtualization

Compiler proves static type, replaces virtual dispatch with direct call.

**RE impact:** Virtual functions may have fewer vtable-mediated callers than expected. Some callers bypass the vtable entirely.

### Vectorization and Loop Unrolling

Loops converted to SIMD (SSE/AVX). Manual loop unrolling removes the loop counter. What was a simple loop becomes a long sequence of operations.

**RE impact:** Identifying the original algorithm requires understanding SIMD semantics and mentally re-rolling unrolled loops.

---

## 9. Name Mangling

### MSVC Mangling Scheme

```
?FunctionName@ClassName@@QEAAXHPEAUFoo@@@Z

Decoding:
  ?              = mangled name start
  FunctionName   = function identifier
  @ClassName@@   = enclosing class scope
  Q              = public member
  E              = __ptr64 (x64 modifier)
  AA             = __cdecl
  X              = void return type
  H              = int parameter
  PEAU           = pointer to public struct
  Foo@@          = struct Foo
  @Z             = end of parameter list / function
```

**Demangle tools:**
- undname.exe (ships with Visual Studio)
- UnDecorateSymbolName() Win32 API in dbghelp.dll
- IDA: right-click -> Demangle name, or Edit -> Demangle Name
- CppNameUndecoratorPlugin for x64dbg

### GCC/Clang Itanium ABI (reference)

```
_ZN9ClassName12FunctionNameEi

  _Z  = mangled name prefix
  N   = nested name start
  9   = 9-character class name length
  12  = 12-character function name length
  E   = nested name end
  i   = int parameter
```

Used on Linux and by MinGW/Clang on Windows. MSVC always uses its own scheme.

---

## 10. Thread Local Storage (TLS)

### PE TLS Directory Structure

```c
typedef struct _IMAGE_TLS_DIRECTORY64 {
    ULONGLONG StartAddressOfRawData;   // TLS template start VA
    ULONGLONG EndAddressOfRawData;     // TLS template end VA
    ULONGLONG AddressOfIndex;          // pointer to TLS index variable
    ULONGLONG AddressOfCallBacks;      // pointer to null-terminated callback array
    DWORD     SizeOfZeroFill;
    DWORD     Characteristics;
} IMAGE_TLS_DIRECTORY64;
```

### TLS Callbacks

The AddressOfCallBacks field points to a null-terminated array of PIMAGE_TLS_CALLBACK function pointers. Each is called by the loader with:
```c
void NTAPI TlsCallback(PVOID DllHandle, DWORD Reason, PVOID Reserved);
// Reason: DLL_PROCESS_ATTACH, DLL_PROCESS_DETACH, DLL_THREAD_ATTACH, DLL_THREAD_DETACH
```

**Critical RE relevance:**
- TLS callbacks execute BEFORE the executable entry point
- Anti-debug checks here fire before entry point breakpoints
- SetUnhandledExceptionFilter calls here affect exception handling before any user code

**How to handle in debugging:**
- x64dbg: Options -> Preferences -> Events -> "TLS Callbacks" checkbox
- WinDbg: sxe ld (break on module load) to catch early execution
- ScyllaHide: automatically patches anti-debug in TLS callbacks
- Manual: in IDA, check the TLS directory, note callback addresses, set BPs manually

---

## 11. Anti-Debug Techniques

### IsDebuggerPresent

Reads PEB.BeingDebugged byte (PEB offset 0x002).

```c
BOOL WINAPI IsDebuggerPresent(void);
// Equivalent to: return (BOOL)NtCurrentPeb()->BeingDebugged;
```

**Bypass:** `mov byte ptr [peb+2], 0` in debugger memory view, or ScyllaHide.

### CheckRemoteDebuggerPresent

```c
BOOL WINAPI CheckRemoteDebuggerPresent(HANDLE hProcess, PBOOL pbDebuggerPresent);
// Internally calls NtQueryInformationProcess(ProcessDebugPort)
```

**Bypass:** Hook NtQueryInformationProcess at ntdll level, return STATUS_SUCCESS with 0 in the output buffer for ProcessDebugPort queries.

### NtQueryInformationProcess

| ProcessInformationClass | Value | Debugger indicated by |
|-------------------------|-------|----------------------|
| ProcessDebugPort        | 7     | non-zero return      |
| ProcessDebugObjectHandle| 30    | non-null handle      |
| ProcessDebugFlags       | 31    | zero return          |

All three are commonly checked by anti-debug code.

### Heap Flag Checks

Windows debug heap sets NtGlobalFlag in the PEB:
- PEB.NtGlobalFlag at offset 0x068 (x86) or 0x0BC (x64)
- Debug value: 0x70 (FLG_HEAP_ENABLE_TAIL_CHECK | FLG_HEAP_ENABLE_FREE_CHECK | FLG_HEAP_VALIDATE_PARAMETERS)

Also check:
- Heap.ForceFlags at HeapBase+0x18 (x86) or HeapBase+0x74 (x64)
- Heap.Flags at HeapBase+0x14 (x86) or HeapBase+0x70 (x64)

**Bypass:** Patch all three locations. ScyllaHide automates this.

### Timing-Based Detection

```asm
; RDTSC-based timing check
rdtsc                    ; reads TSC into EDX:EAX
mov [saved_low], eax
; ... protected code ...
rdtsc
sub eax, [saved_low]     ; compute delta
cmp eax, 0x100000        ; ~1M cycles threshold
ja  debugger_detected
```

Also: GetTickCount, QueryPerformanceCounter, timeGetTime.

**Bypass:**
- Patch the comparison (change JA to JMP forward)
- Don't single-step through timed regions; use run-to-cursor
- Hardware breakpoints introduce less overhead than software BPs, but timing checks still detect debugger presence via NtGlobalFlag

### OutputDebugString Anti-Debug

Under no debugger: OutputDebugString triggers DBG_PRINTEXCEPTION_C (0x40010006), which the CRT handles. Under a debugger, the exception is silently consumed.

**Bypass:** Tell the debugger to pass-through that exception: in x64dbg, right-click exception list.

### Exception-Based Detection

```c
// If SetUnhandledExceptionFilter is called and returns a previous filter,
// under a debugger the exception goes to the debugger not the filter.
// Detecting this: install a filter, trigger an exception, see if filter fires.
```

### Heap Allocation Size Check

`HeapAlloc` in debug mode adds extra bytes for tail checking. Comparing the requested vs actual allocation size can reveal the debug heap.

---

## 12. Common Interview Questions

**Q: What is the difference between RVA and VA?**
RVA (Relative Virtual Address) is an offset from the module's ImageBase. VA (Virtual Address) is the absolute address in the process's virtual address space: VA = ImageBase + RVA. A file offset is a third concept: the byte position within the PE file on disk. File offsets differ from RVAs because sections are aligned differently in memory (SectionAlignment, typically 0x1000) versus on disk (FileAlignment, typically 0x200).

**Q: Which registers are preserved across calls in x64 Windows ABI?**
Non-volatile (callee-saved): RBX, RBP, RDI, RSI, RSP, R12, R13, R14, R15, XMM6-XMM15.
Volatile (caller-saved, may be trashed): RAX, RCX, RDX, R8, R9, R10, R11, XMM0-XMM5.

**Q: Where is the vtable pointer located in a MSVC C++ object?**
At offset 0 in the object (the very first 8 bytes on x64). For multiple inheritance, each base class with virtual functions gets its own vtable pointer at different offsets within the derived object. The vtable itself resides in .rdata and is prefixed at vtable[-1] by a pointer to the Complete Object Locator.

**Q: How does RTTI work in MSVC and how do you find a class by name?**
Every polymorphic object's vtable has a Complete Object Locator at vtable[-1]. The COL points to a TypeDescriptor containing the mangled class name (e.g., ".?AVMyClass@@"). dynamic_cast calls __RTDynamicCast which walks this chain. To find a class by name at runtime: scan .rdata for the mangled name string, find the TypeDescriptor pointing to it, find the vtable pointing to that COL.

**Q: What is shadow space and why does it always exist?**
Shadow space (home space) is 32 bytes allocated by every x64 caller before the CALL instruction. It is reserved for the callee to spill RCX, RDX, R8, R9 to known stack locations. This enables debuggers, profilers, and exception handlers to reliably read argument values without inspecting registers. It always exists even if the callee never spills anything.

**Q: What is a TLS callback and why does it matter for RE?**
TLS callbacks are functions listed in the PE's TLS directory that the Windows loader invokes before the executable's entry point, with DLL_PROCESS_ATTACH. Anti-debug and anti-tamper code placed in TLS callbacks executes before entry point breakpoints fire, making them invisible to analysts who only break at the entry point.

**Q: How does CFG affect vtable hooking and what is the bypass?**
CFG validates every indirect call target against a bitmap. Overwriting a vtable slot with a pointer to hook code will trigger a CFG violation unless the hook address is registered as a valid indirect call target. The bypass is to either allocate the hook in a region registered with SetProcessValidCallTargets(), disable CFG for the target module (requires SetProcessMitigationPolicy), or use a different hooking mechanism that does not involve overwriting vtable pointers.

## Related Material

### Knowledge
- [common-instructions](knowledge/assembly/common-instructions.md)
- [compiler-patterns](knowledge/assembly/compiler-patterns.md)
- [exceptions](knowledge/cpp/exceptions.md)

### Prompts
- [analyze_binary](prompts/analyze_binary.md)
- [analyze_crash](prompts/analyze_crash.md)
- [analyze_memory](prompts/analyze_memory.md)

