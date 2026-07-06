---
title: References
skill: reverse-engineering
category: 
difficulty: advanced
tags: [pe, windows, x64, driver, malware, unity, pdb, cryptography, gui, kernel, debug, dll]
updated: 2026-07-05
---
# References

> Official documentation, specifications, and authoritative resources. All links verified as of 2026.

---

## Microsoft — PE Format & Windows Internals

### PE Format Specification
**PE Format Reference (Microsoft Docs)**
https://learn.microsoft.com/en-us/windows/win32/debug/pe-format

The canonical reference for the Portable Executable format. Covers all headers, data directories, section flags, import/export tables, base relocations, TLS, exception tables, and debug directories. Read this before anything else.

**IMAGE_NT_HEADERS64 Structure**
https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-image_nt_headers64

**IMAGE_OPTIONAL_HEADER64 Structure**
https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-image_optional_header64

**IMAGE_SECTION_HEADER Structure**
https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-image_section_header

**IMAGE_IMPORT_DESCRIPTOR Structure**
https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-image_import_descriptor

### Debugging and Symbol APIs

**DbgHelp Functions (Symbol Handler)**
https://learn.microsoft.com/en-us/windows/win32/debug/dbghelp-functions

Covers SymInitialize, SymFromAddr, SymEnumSymbols, StackWalk64, UnDecorateSymbolName, MiniDumpWriteDump.

**SymFromAddr Function**
https://learn.microsoft.com/en-us/windows/win32/api/dbghelp/nf-dbghelp-symfromaddr

**UnDecorateSymbolName Function**
https://learn.microsoft.com/en-us/windows/win32/api/dbghelp/nf-dbghelp-undecoratesymbolname

**Symbol Server and Symbol Path Configuration**
https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/symbol-path

**Microsoft Public Symbol Server**
https://msdl.microsoft.com/download/symbols

_NT_SYMBOL_PATH=srv*C:\Symbols*https://msdl.microsoft.com/download/symbols

### Memory Management

**VirtualAlloc Function**
https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtualalloc

**VirtualProtect Function**
https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtualprotect

**VirtualQuery Function**
https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtualquery

**MEMORY_BASIC_INFORMATION Structure**
https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-memory_basic_information

**ReadProcessMemory / WriteProcessMemory**
https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-readprocessmemory

**Memory Protection Constants**
https://learn.microsoft.com/en-us/windows/win32/memory/memory-protection-constants

### Process and Thread Internals

**PEB Structure (winternl.h)**
https://learn.microsoft.com/en-us/windows/win32/api/winternl/ns-winternl-peb

**PEB_LDR_DATA Structure**
https://learn.microsoft.com/en-us/windows/win32/api/winternl/ns-winternl-peb_ldr_data

**NtQueryInformationProcess**
https://learn.microsoft.com/en-us/windows/win32/api/winternl/nf-winternl-ntqueryinformationprocess

Covers ProcessDebugPort, ProcessDebugObjectHandle, ProcessDebugFlags — commonly abused by anti-debug.

**TEB Structure**
https://learn.microsoft.com/en-us/windows/win32/api/winternl/ns-winternl-teb

**Thread Local Storage (TLS)**
https://learn.microsoft.com/en-us/windows/win32/procthread/thread-local-storage

**IMAGE_TLS_DIRECTORY64 Structure**
https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-image_tls_directory64

### Exception Handling

**Structured Exception Handling (x64)**
https://learn.microsoft.com/en-us/cpp/build/exception-handling-x64

Covers RUNTIME_FUNCTION, UNWIND_INFO, unwind codes, chained unwind, exception handlers — required reading for understanding .pdata and .xdata.

**x64 Prolog and Epilog Requirements**
https://learn.microsoft.com/en-us/cpp/build/prolog-and-epilog

Defines exactly what constitutes a valid function prologue/epilogue. Explains why RSP alignment and unwind records must be consistent.

**IMAGE_RUNTIME_FUNCTION_ENTRY Structure**
https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-runtime_function

**__try / __except / __finally (MSVC)**
https://learn.microsoft.com/en-us/cpp/cpp/try-except-statement

**SetUnhandledExceptionFilter**
https://learn.microsoft.com/en-us/windows/win32/api/errhandlingapi/nf-errhandlingapi-setunhandledexceptionfilter

### Security Mitigations

**Control Flow Guard Overview**
https://learn.microsoft.com/en-us/windows/win32/secbp/control-flow-guard

**SetProcessValidCallTargets (CFG API)**
https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-setprocessvalidcalltargets

**Hardware-enforced Stack Protection**
https://learn.microsoft.com/en-us/windows/security/hardware-security/hardware-based-kernel-protections

**IsDebuggerPresent**
https://learn.microsoft.com/en-us/windows/win32/api/debugapi/nf-debugapi-isdebuggerpresent

**CheckRemoteDebuggerPresent**
https://learn.microsoft.com/en-us/windows/win32/api/debugapi/nf-debugapi-checkremotedebuggerpresent

### Calling Conventions and ABI

**x64 Calling Convention (Microsoft Docs)**
https://learn.microsoft.com/en-us/cpp/build/x64-calling-convention

Definitive reference for argument passing, return values, volatile/non-volatile registers, shadow space.

**x64 Software Conventions**
https://learn.microsoft.com/en-us/cpp/build/x64-software-conventions

Stack layout, frame pointer usage, RSP alignment requirements, register usage by the ABI.

**x86 Calling Conventions (MSVC)**
https://learn.microsoft.com/en-us/cpp/cpp/argument-passing-and-naming-conventions

Covers __cdecl, __stdcall, __fastcall, __thiscall for 32-bit targets.

---

## Intel — CPU Architecture

### Intel Software Developer's Manuals (SDM)

**Intel 64 and IA-32 Architectures Software Developer's Manual (Combined Volumes)**
https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html

The authoritative reference for x86/x64 instruction set, encoding, privilege levels, debug registers, performance monitoring, segmentation, paging, TLB behavior, SIMD.

Direct download (all volumes combined):
https://cdrdv2.intel.com/v1/dl/getContent/671200

**Volume 1: Basic Architecture**
Covers registers, memory addressing, data types, floating-point, SIMD overview, protection model.

**Volume 2: Instruction Set Reference (A-Z)**
Every instruction: encoding, description, operation, exceptions, timing. Use this to understand what a specific opcode does.

**Volume 3: System Programming Guide**
Privilege levels, segmentation, paging, interrupt/exception handling, debug registers (DR0-DR7), MSRs, VMX, SMM. Required for understanding hardware breakpoints.

### Debug Registers

From SDM Volume 3, Chapter 17 — Debug, Branch Profile, TSC:

```
DR0-DR3: Linear address of breakpoint (read/write)
DR6:     Debug Status Register (breakpoint conditions hit)
DR7:     Debug Control Register (enable/condition/length per DR0-DR3)

DR7 encoding per breakpoint Ni (i=0,1,2,3):
  Bits [2i+1 : 2i]  = G/L enable (global/local)
  Bits [17+4i+1 : 17+4i] = Condition (00=exec, 01=write, 10=I/O, 11=RW)
  Bits [19+4i+1 : 19+4i] = Length (00=1B, 01=2B, 10=8B, 11=4B)
```

**RDTSC Instruction (timing)**
Reads the processor timestamp counter. Used for timing-based anti-debug detection. See SDM Volume 2B, Chapter 4.

### SIMD Reference

**Intel Intrinsics Guide**
https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html

Interactive reference for all SSE, AVX, AVX-512 intrinsics. Essential for understanding vectorized code produced by auto-vectorizing compilers.

---

## AMD — CPU Architecture

### AMD64 ABI and Architecture

**AMD64 Architecture Programmer's Manual**
https://www.amd.com/system/files/TechDocs/40332.pdf

Covers AMD64 instruction set, register set, memory model. Very similar to Intel SDM but with AMD-specific extensions and clarifications.

Direct download: https://www.amd.com/system/files/TechDocs/40332.pdf

**AMD64 ABI (System V, for Linux/GCC reference)**
https://gitlab.com/x86-psABIs/x86-64-ABI

The System V AMD64 ABI used by GCC/Clang on Linux and by MinGW. Different from MSVC ABI. Useful when analyzing GCC-compiled code or cross-platform RE.

Key differences from MSVC ABI:
- 6 integer registers (RDI, RSI, RDX, RCX, R8, R9) instead of 4
- No shadow space
- Stack arguments aligned differently
- Callee-saved: RBX, RBP, R12-R15

**CPUID Instruction Reference**
https://www.amd.com/system/files/TechDocs/25481.pdf

Used by anti-VM code to detect hypervisors (hypervisor bit in leaf 1 ECX), enumerate CPU features, and fingerprint the processor.

---

## RTTI and C++ ABI

### Itanium C++ ABI (GCC/Clang)

**Itanium C++ ABI Specification**
https://itanium-cxx-abi.github.io/cxx-abi/abi.html

Covers the name mangling scheme, vtable layout, RTTI structures, exception handling for GCC/Clang. Directly applicable when RE-ing Linux binaries or Windows binaries compiled with Clang/MinGW.

Key sections:
- 2.5: Virtual Table Layout
- 2.9.1: RTTI Layout
- 5: Name Mangling

**LLVM libcxxabi RTTI Implementation**
https://github.com/llvm/llvm-project/blob/main/libcxxabi/src/cxa_demangle.cpp

Reference implementation of Itanium name demangling. Reading this code teaches you the full mangling grammar.

### MSVC ABI (Reverse-Engineered Documentation)

**Agner Fog — Calling Conventions for Different C++ Compilers**
https://www.agner.org/optimize/calling_conventions.pdf

Comprehensive comparison of calling conventions across MSVC, GCC, Clang, Borland, and others. Covers stack layouts, register usage, name mangling, struct passing, exception handling.

**MSVC Name Mangling Reference (SymbolSort)**
https://mearie.org/documents/mscmangle/

Reverse-engineered documentation of MSVC's name mangling scheme. Explains the grammar for encoding namespaces, templates, qualifiers, and calling conventions.

---

## Tools Documentation

### IDA Pro

**IDA Pro Documentation**
https://hex-rays.com/documentation/

**IDA Pro SDK Reference (for plugin development)**
https://hex-rays.com/products/ida/support/sdkdoc/

**IDAPython API Reference**
https://hex-rays.com/documentation/idapython_docs/75/

**IDC (IDA Scripting) Reference**
https://hex-rays.com/documentation/idc/

**Hex-Rays Decompiler Manual**
https://hex-rays.com/products/decompiler/manual/

### Ghidra

**Ghidra GitHub (NSA) — includes full documentation**
https://github.com/NationalSecurityAgency/ghidra

**Ghidra API Javadoc**
https://ghidra.re/ghidra_docs/api/

**Ghidra Script Development Guide**
https://ghidra.re/ghidra_docs/analyzeHeadlessREADME.html

### x64dbg

**x64dbg Documentation**
https://help.x64dbg.com/en/latest/

**x64dbg GitHub**
https://github.com/x64dbg/x64dbg

**ScyllaHide (Anti-Anti-Debug plugin)**
https://github.com/x64dbg/ScyllaHide

### WinDbg

**WinDbg Documentation (Microsoft)**
https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/

**Debugging Tools for Windows (download)**
https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/debugger-download-tools

**WinDbg Command Reference**
https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/commands

---

## Cryptography Reference

### AES (Advanced Encryption Standard)

**NIST FIPS 197 — AES Specification**
https://csrc.nist.gov/publications/detail/fips/197/final

The official AES specification. Contains full S-Box, MixColumns coefficients, key expansion algorithm. Necessary for recognizing AES code in binaries.

### SHA (Secure Hash Algorithm)

**NIST FIPS 180-4 — SHA Specification**
https://csrc.nist.gov/publications/detail/fips/180-4/final

Covers SHA-1, SHA-224, SHA-256, SHA-384, SHA-512. Contains all round constants and initial hash values — memorizing a few helps identify SHA code instantly.

### General Cryptographic Reference

**Applied Cryptography by Bruce Schneier (companion site)**
https://www.schneier.com/books/applied-cryptography/

**CrypTool — interactive crypto learning**
https://www.cryptool.org/

---

## RE Community Resources

### Books

- *Practical Malware Analysis* — Sikorski & Honig (No Starch Press)
  The standard text for malware RE. Covers static/dynamic analysis, unpacking, anti-debug, shellcode.

- *The Art of Software Security Assessment* — Dowd, McDonald, Schuh (Addison-Wesley)
  Deep coverage of vulnerability research methodology.

- *Windows Internals, Part 1 & 2* — Yosifovich, Ionescu, Solomon (Microsoft Press)
  The definitive Windows internals reference. Covers process/thread architecture, memory management, I/O, security.

- *Hacker Disassembling Uncovered* — Kaspersky (A-LIST Publishing)
  Detailed analysis of compiler-generated code patterns.

### Online Resources

**Godbolt Compiler Explorer**
https://godbolt.org/

Compile C/C++ code and see the exact assembly output for MSVC/GCC/Clang at any optimization level. Invaluable for understanding how source maps to binary.

**Matt Pietrek — Articles on Windows Internals (archived)**
https://bytepointer.com/resources/pietrek_the_real_story.htm

Classic deep-dives into PE format, DLL loading, and Windows internals from the 1990s. Still accurate for core mechanisms.

**OpenRCE Community Wiki**
http://www.openrce.org/

Community wiki with RE articles, tool reviews, tutorials.

**Hexblog (Ilfak Guilfanov — IDA Pro author)**
https://hex-rays.com/blog/

Blog posts on IDA internals, Hex-Rays decompiler design, and advanced RE techniques from the primary IDA developer.

**Diary of a Reverse Engineer**
https://web.archive.org/web/2021*/https://doar-e.github.io/

Deep technical posts on Windows RE, exploit development, vulnerability research.

**Connor McGarr's Blog**
https://connormcgarr.github.io/

Kernel exploitation, Windows internals, CFG bypass, memory corruption RE.

---

## Standards and Specifications

**System V AMD64 ABI (v1.0)**
https://gitlab.com/x86-psABIs/x86-64-ABI/-/jobs/artifacts/master/raw/x86-64-ABI/abi.pdf?job=build

**DWARF Debugging Standard**
https://dwarfstd.org/

Used by GCC/Clang for debug information (vs MSVC's PDB). Relevant when RE-ing Linux/cross-compiled binaries.

**ECMA-335 — CLI/MSIL Standard (.NET)**
https://ecma-international.org/publications-and-standards/standards/ecma-335/

The specification for .NET Common Language Infrastructure. Required when RE-ing managed code.

## Related Material

### Knowledge
- [common-instructions](knowledge/assembly/common-instructions.md)
- [compiler-patterns](knowledge/assembly/compiler-patterns.md)
- [exceptions](knowledge/cpp/exceptions.md)

### Prompts
- [analyze_binary](prompts/analyze_binary.md)
- [analyze_crash](prompts/analyze_crash.md)
- [analyze_memory](prompts/analyze_memory.md)

