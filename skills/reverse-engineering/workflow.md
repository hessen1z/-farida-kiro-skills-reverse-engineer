# Reverse Engineering Workflow

> A systematic methodology for analyzing unknown Windows binaries. Follow these phases in order. Skip nothing on first pass — evidence from any phase informs all others.

---

## Phase 0 — Environment Setup

Before touching the binary, prepare a controlled environment.

### Sandbox / VM Setup

Use an isolated VM. Snapshots are mandatory. Recommendations:

- **Windows 10/11 x64** (match target OS)
- **VMware Workstation or VirtualBox** with snapshots
- **Disable internet** or route through a monitored interface (INetSim, FakeNet-NG)
- **Shared folders disabled** to prevent exfiltration
- **Tools installed:** IDA Pro / Ghidra, x64dbg + ScyllaHide, Process Monitor, API Monitor, PE-bear

### Tool Configuration

**IDA Pro:**
```
Options -> General -> Auto Analysis: ON
Options -> Decompiler -> Output: always show casts ON
Options -> Colors: highlight calls differently from jumps
File -> Plugins -> FLIRT: load all signature files for target platform
```

**x64dbg:**
```
Options -> Preferences -> Events -> System Breakpoint: ON
Options -> Preferences -> Events -> TLS Callbacks: ON
Options -> Preferences -> Events -> Entry Breakpoint: ON
Plugins: ScyllaHide (bypass anti-debug)
Plugins: xAnalyzer (auto-analyze calling conventions)
```

**Symbol Server:**
```
_NT_SYMBOL_PATH=srv*C:\Symbols*https://msdl.microsoft.com/download/symbols
```

---

## Phase 1 — Initial Triage (Static, 15–30 minutes)

Goal: Understand *what kind* of binary this is before investing hours.

### Step 1.1 — File Identification

```
# Check magic bytes
PE header present? -> Windows executable
CLR header? -> .NET managed code (use dnSpy, not IDA)
Signature overlay? -> Packed or self-extracting

Tools: file.exe, TrID, PE-bear
```

Check for packing indicators:
- Section count < 3 with high entropy (> 7.0 bits/byte)
- Import table with only LoadLibrary + GetProcAddress
- Unusual section names: .upx, .nsp, MPRESS1

If packed: proceed to Phase 2 first to unpack, then restart Phase 1.

### Step 1.2 — PE Structure Walk

Open in PE-bear or CFF Explorer. Record:

| Field                   | What to note                                      |
|-------------------------|---------------------------------------------------|
| Machine                 | x86 (0x14C) or x64 (0x8664)                       |
| Subsystem               | Console (3), GUI (2), Native (1), Driver          |
| DLL Characteristics     | ASLR? DEP? CFG? High-entropy VA?                  |
| Entry Point RVA         | Note the section it falls in                      |
| Compile timestamp       | Approximate build date (may be fake)              |
| Debug directory         | PDB path? CodeView? Symbol age                    |

### Step 1.3 — Import Analysis

The import table reveals what APIs the binary uses, which tells you what it does.

**Key import families:**

| Import DLL / Function Group       | Likely Purpose                             |
|------------------------------------|--------------------------------------------|
| CreateFile, ReadFile, WriteFile    | File I/O                                   |
| VirtualAlloc, PAGE_EXECUTE_*       | Code injection or JIT                      |
| CreateProcess, ShellExecute        | Process launch                             |
| RegOpenKey, RegSetValue            | Persistence or configuration               |
| WSAConnect, send, recv             | Network communication                      |
| CryptEncrypt, BCryptEncrypt        | Encryption                                 |
| LoadLibrary, GetProcAddress        | Dynamic resolution (often packed/malware)  |
| NtQuerySystemInformation           | Anti-VM / sandbox detection                |
| IsDebuggerPresent                  | Anti-debug                                 |

Red flags: no meaningful imports + LoadLibrary/GetProcAddress = manual IAT resolution.

### Step 1.4 — String Analysis

```
# In IDA: View -> Open Subviews -> Strings
# Strings window: filter for interesting patterns
```

Look for:
- URLs, IP addresses, domain names
- Registry paths (`HKLM\SOFTWARE\...`)
- File paths and filenames
- Error messages that identify the product
- Format strings that reveal function purpose
- Encryption keys (base64 strings, hex strings)
- RTTI names (`.?AV...@@`) — confirm C++ and class names

### Step 1.5 — Export Analysis (DLLs)

For DLLs, exports tell you the public API surface:

```
# dumpbin /exports target.dll
# or: IDA View -> Exports
```

Note: some DLLs export by ordinal only. Some exports forward to other DLLs.

---

## Phase 2 — Unpacking (If Required)

Skip if binary is not packed.

### Step 2.1 — Confirm Packing

- High entropy in code section
- Import table with only LoadLibrary/GetProcAddress
- Entry point in unusual section

### Step 2.2 — Dynamic Unpacking

1. Load in x64dbg
2. Run with ScyllaHide loaded (bypass anti-debug in stub)
3. Use "Find OEP by Section Hop": Options -> right-click in CPU -> find OEP
4. Run until the unpacking stub jumps to OEP
5. When execution reaches a new section that wasn't there in PE header, you're at OEP

### Step 2.3 — Dump and Fix Imports

1. At OEP: Plugins -> Scylla -> Dump
2. Scylla: IAT Autosearch -> Get Imports
3. Fix any unresolved imports manually (look at `jmp [addr]` thunks)
4. Scylla: Fix Dump -> write patched dump to disk
5. Load dump in IDA for proper analysis

---

## Phase 3 — Deep Static Analysis

Goal: Recover program structure, class hierarchy, key algorithms.

### Step 3.1 — Initial Auto-Analysis Pass

Load in IDA. Let auto-analysis complete. This typically takes 1–15 minutes depending on binary size.

While analysis runs:
- Set type library for Windows SDK: View -> Type Libraries -> select `mssdk` and `vc6win`
- FLIRT signatures: File -> Load File -> FLIRT Signature File -> select all CRT/MSVC sigs

### Step 3.2 — Identify Entry Point and Main

MSVC executables call `__tmainCRTStartup` or `mainCRTStartup` at entry. The real `main`/`WinMain` is called from there. Find it:

```
Entry point
  -> __tmainCRTStartup (in CRT, often recognized by FLIRT)
     -> calls several init functions (atexit, heap init, etc.)
     -> calls the real main (usually last significant call before ExitProcess)
```

### Step 3.3 — Identify C++ Classes via RTTI

In IDA, find all vtables by locating COL structures:

1. Search for `.?AV` strings: Search -> Text -> ".?AV"
2. Each hit is a TypeDescriptor name field
3. TypeDescriptor is at string_addr - 16
4. COL is somewhere in .rdata with pTypeDescriptor = RVA to TypeDescriptor
5. Vtable is at COL + 8 (first slot after the COL pointer slot)

IDAPython shortcut to auto-name vtables:
```python
# After loading from knowledge/rtti.md: dump_all_classes()
```

Rename functions using the class structure:
- `vtable_MyClass` → prefix all slots with `MyClass::`
- slot 0 → check if it matches signature of a known virtual method pattern

### Step 3.4 — Code Cross-Reference Analysis

For each interesting function:

1. **Find all callers:** press X in IDA on function name
2. **Find all data references:** press X on global variables
3. **Follow call chains upward** until you reach a known entry point
4. **Follow call chains downward** to understand what the function does

Mark each function as you understand it. Use repeatable comments (`:`shortcut in IDA) so they appear in callers.

### Step 3.5 — Type Propagation

When you understand a function's purpose:
1. Set its prototype: press Y in IDA
2. Set argument types in all callers
3. Set struct types for memory accesses: Create struct in IDA, apply with T

This propagates through Hex-Rays and dramatically improves decompiler output.

### Step 3.6 — Pattern Recognition Checklist

Work through the binary looking for these patterns:

- [ ] Encryption / decryption loops (XOR key, rotate, AES round keys in .rdata)
- [ ] Network protocol handlers (recv -> parse -> dispatch)
- [ ] Command dispatch tables (array of function pointers indexed by command ID)
- [ ] Factory functions (switch on type ID, return pointer to different vtable)
- [ ] Configuration parsing (read from registry/file, populate struct)
- [ ] Thread entry points (functions matching LPTHREAD_START_ROUTINE signature)
- [ ] Exception handlers (__except blocks, SetUnhandledExceptionFilter)

---

## Phase 4 — Dynamic Analysis

Goal: Validate static findings. Observe live state. Resolve indirect calls.

### Step 4.1 — Attach or Launch in Debugger

Preferred: launch from debugger with a system breakpoint.

```
x64dbg: File -> Open -> target.exe
  System breakpoint fires before TLS callbacks
  Use ScyllaHide to bypass anti-debug
```

For already-running processes:
```
x64dbg: File -> Attach -> select PID
  Breaks at ntdll!DbgBreakPoint
  Risk: some binaries detect attach via PEB.NtGlobalFlag
```

### Step 4.2 — Symbol Configuration

In x64dbg, the Symbol tab shows loaded modules. For each interesting DLL:
- Right-click -> Reload Symbols
- Configure symbol server path in x64dbg settings

### Step 4.3 — Break at Key Points

Set breakpoints on functions identified in static analysis:

```
# Software breakpoint: F2 on address
# Hardware Execute BP: right-click address -> Breakpoint -> Hardware, Execute
# Hardware Access BP: right-click memory in dump -> Hardware Access
# Memory BP: right-click region -> Memory Breakpoint -> Access
```

Prefer **hardware breakpoints** for anti-debug-aware binaries. They are set via CPU debug registers (DR0–DR3), not by writing 0xCC to memory.

### Step 4.4 — Observe Call Arguments

When execution stops at a breakpoint:
- Register panel shows current state
- Stack panel shows return addresses and arguments
- Dump panel: follow RCX (usually the object pointer) to see the vtable

For C++ objects: Follow `[RCX]` (the vtable pointer) to see the vtable, then `[[RCX]-8]` to see the COL and confirm class identity.

### Step 4.5 — Logging Unknown Functions

Set a conditional breakpoint that logs without stopping:

```
# In x64dbg, right-click BP -> Edit -> Condition: 0 (never stop)
# Log text: "called MyFunc, RCX={rcx}, RDX={rdx}"
# Runs forever, logs all calls to the function
```

Frida (dynamic instrumentation) is more powerful for logging:
```js
// Attach to function and log args
Interceptor.attach(ptr("0x12345678"), {
  onEnter: function(args) {
    console.log("arg0=" + args[0] + " arg1=" + args[1]);
  }
});
```

### Step 4.6 — Memory Analysis at Runtime

When execution is paused:

```
# Enumerate memory regions
# In x64dbg: Memory Map tab (Alt+M)
# Look for MEM_PRIVATE regions that are EXECUTE: injected code or JIT

# Read struct members
# Dump panel: Ctrl+G -> enter address -> view raw bytes
# Right-click -> Data type -> various formats
```

---

## Phase 5 — Documentation and Annotation

Goal: Record findings so they are reusable.

### Step 5.1 — IDA Database Organization

- Rename all identified functions: `ClassName__MethodName` or `Module_Purpose`
- Create structs for all identified C++ objects
- Apply struct types to pointer variables
- Add function comments explaining purpose, params, return
- Add inline comments for non-obvious instructions
- Color code by module (red = anti-debug, green = core logic, blue = networking)

### Step 5.2 — Class Hierarchy Documentation

For each identified class, document:

```markdown
## ClassName

vtable @ 0x14XXXXXX
COL name: .?AVClassName@@
Base classes: BaseA, BaseB

Fields (deduced from constructor + member access):
  +0x00  vptr
  +0x08  m_field1  (int)
  +0x10  m_field2  (pointer to OtherClass)
  +0x18  m_field3  (bool + padding)

Methods (vtable slots):
  slot 0: virtual void Init()       @ 0x14XXXXXXXX
  slot 1: virtual int Process()     @ 0x14XXXXXXXX
  slot 2: virtual void Cleanup()    @ 0x14XXXXXXXX
```

### Step 5.3 — Algorithm Documentation

For cryptographic or custom protocol code, document:
- Input format
- Output format
- Key/parameter sources
- Step-by-step description matching decompiler pseudocode

### Step 5.4 — Signature Generation

For each key function identified, create a pattern signature for future scanning:

```
# Grab bytes at function start (avoid first 5 that encode CALL instruction)
# Replace operand bytes with ?? wildcards
# Test pattern against binary to ensure uniqueness

# Example:
48 89 5C 24 08    # mov [rsp+8], rbx
48 89 74 24 10    # mov [rsp+10], rsi
57                # push rdi
48 83 EC 20       # sub rsp, 20
?? ?? ?? ?? ??    # call (relative, varies with base)
48 8B F9          # mov rdi, rcx
```

---

## Phase 6 — Validation

Before finalizing conclusions, validate every significant finding.

### Step 6.1 — Cross-Validate Static with Dynamic

For every function you identified statically:
- Set a breakpoint and confirm it fires when expected
- Confirm argument types match your analysis
- Confirm return values match your analysis

### Step 6.2 — Edge Case Testing

- What happens with NULL inputs?
- What happens at boundary sizes?
- Are there length checks that could be bypassed?
- Are there integer overflows in size calculations?

### Step 6.3 — Version Robustness

If patterns/offsets will be used against multiple versions:
- Test patterns against adjacent versions of the binary
- Verify that RTTI names are consistent
- Note which offsets are stable vs version-dependent

---

## Common Pitfalls to Avoid During Workflow

| Pitfall | Mitigation |
|---------|-----------|
| Starting dynamic before static | Always do static triage first |
| Trusting decompiler types blindly | Verify every type against disassembly |
| Not accounting for ASLR | Always use RVAs, never hardcode VAs |
| Confusing debug and release builds | Check compiler flags in binary/section names |
| Stopping at first anti-debug bypass | Check for multiple layers (TLS, SEH, timing) |
| Assuming inlined functions don't exist | Recognize FLIRT-pattern functions even when inlined |
| Renaming without evidence | Only rename when at least 2 independent signals agree |
| Missing tail calls | A `jmp` at function end can be a call to a different function |

---

## Time Budget Guide

| Binary Type            | Static Triage | Deep Analysis | Total Estimate |
|------------------------|---------------|---------------|----------------|
| Small utility (< 100KB) | 30 min        | 2–4 hrs       | 4–6 hrs        |
| Medium app (1–5MB)      | 1–2 hrs       | 8–20 hrs      | 10–24 hrs      |
| Large app (> 10MB)      | 2–4 hrs       | Days–weeks    | Depends on goal|
| Packed malware          | + 1–4 hrs unpack | Same as above | + unpack time |
| Virtualized code        | N/A           | 2–5x overhead | Varies greatly |

## Related Material

### Knowledge
- [common-instructions](knowledge/assembly/common-instructions.md)
- [compiler-patterns](knowledge/assembly/compiler-patterns.md)
- [exceptions](knowledge/cpp/exceptions.md)

### Prompts
- [analyze_binary](prompts/analyze_binary.md)
- [analyze_crash](prompts/analyze_crash.md)
- [analyze_memory](prompts/analyze_memory.md)

