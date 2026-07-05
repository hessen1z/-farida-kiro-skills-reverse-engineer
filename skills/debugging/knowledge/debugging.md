# Debugging Knowledge

## Overview

Debugging is the process of examining runtime state, control flow, and memory to diagnose faults, hangs, or unexpected behavior in native software. In Windows, debugging covers user-mode applications, games, kernel drivers, crash dumps, and protected or anti-debug-aware binaries.

## Background

Windows debugging relies on several coordinated subsystems:
- the OS exception dispatch and Structured Exception Handling (SEH)
- symbol resolution via PDB and debug directories
- processor debug facilities for breakpoints and watchpoints
- stack unwinding metadata for reliable call stack recovery
- kernel-mode and user-mode target attachment models

A robust debugging skill distinguishes between evidence collection, hypothesis verification, and non-invasive runtime observation.

## Core Concepts

### Debugger architecture

A debugger interacts with a target process or dump through:
- live attachment or process launch
- breakpoint and single-step control
- memory read/write and register inspection
- event notification for exceptions, thread creation, and module loads

### Symbol resolution

Symbols map addresses to function names, source lines, and types. Key elements include:
- PDB GUID and age matching the binary image
- symbol search paths and cache layout
- debug directories inside PE images
- deferred symbol loading for performance

### Exception handling

Windows exceptions are represented by `EXCEPTION_RECORD` and `CONTEXT` structures. Common exception types:
- access violation (`0xC0000005`)
- integer divide by zero (`0xC0000094`)
- breakpoint (`0x80000003`)
- C++ exception (`0xE06D7363`)

Exception handlers can be:
- SEH chain handlers on the stack
- vectored exception handlers
- C++ catch blocks built on top of SEH

### Stack unwinding

Reliable stack traces depend on unwind metadata:
- x64 uses `RUNTIME_FUNCTION` and unwind codes
- x86 may use frame pointers or compiler-generated stack frames
- missing or corrupted unwind data requires heuristic recovery

### Breakpoints and watchpoints

Breakpoints pause execution at known instructions. Types include:
- software breakpoints: `INT3` inserted in code
- hardware breakpoints: debug registers `DR0`–`DR3`
- memory breakpoints: page guard or access condition traps

Hardware breakpoints are less intrusive and avoid code modification, but are limited in number.

## Internal design

### User-mode vs kernel-mode

User-mode debugging attaches to a process and observes application threads, modules, and heap state. Kernel-mode debugging connects to the OS kernel and inspects system threads, drivers, and global state. Kernel debugging requires remote or local target configuration.

### Crash dump analysis

Crash dumps capture process or kernel state at fault time. Common dump analysis steps:
1. load the dump in WinDbg or another debugger
2. verify module list and symbol status
3. inspect the exception record and stack traces
4. recover the call stack and identify the faulting module

### Anti-debug and protection

Protected binaries may use anti-debug techniques such as:
- debugger presence checks (`IsDebuggerPresent`, `NtQueryInformationProcess`)
- timing checks around `GetTickCount` or `QueryPerformanceCounter`
- self-modifying code and memory checks
- exception-based control flow

These protections can affect breakpoint placement, memory reads, and process behavior.

## Data structures and components

### Exception metadata

- `EXCEPTION_RECORD` contains exception code, flags, and faulting address
- `CONTEXT` stores the register state
- `EXCEPTION_POINTERS` bundles record and context pointers

### Unwind metadata

- `UNWIND_INFO` describes how to restore registers and stack frame state
- `RUNTIME_FUNCTION` table entries map code ranges to unwind data
- x86 frame pointers use `EBP`/`RBP` chains when available

### Debug metadata

- PE debug directory entries reference `IMAGE_DEBUG_DIRECTORY`
- PDB files contain symbol tables, type info, and source line mappings
- CodeView records embed debug information in a runnable image

## Examples

### WinDbg command workflow

```text
.symfix
.reload /f
!analyze -v
k
lm vm
```

### Exception handling example

```asm
mov eax, dword ptr [esp]
cmp eax, 0xE06D7363 ; MSVC C++ exception code
je exception_handler
```

### Symbol initialization in C++

```cpp
#include <windows.h>
#include <dbghelp.h>

void InitSymbols(HANDLE process) {
    SymSetOptions(SYMOPT_DEFERRED_LOADS | SYMOPT_UNDNAME | SYMOPT_LOAD_LINES);
    SymInitialize(process, nullptr, FALSE);
    SymSetSearchPath(process, "srv*C:\\symbols*https://msdl.microsoft.com/download/symbols");
}
```

## Notes and caveats

- Always verify symbol matches before trusting function names.
- Avoid invasive commands that change state in a live target.
- Treat unhandled exceptions and access violations as evidence, not root cause by themselves.
- For hang analysis, compare thread activity across multiple snapshots.

## References

- Microsoft Debugging Tools for Windows
- WinDbg documentation
- Visual Studio debugging guide
- Windows Internals by Mark Russinovich
- AMD and Intel architecture manuals

## See Also

- `../patterns/breakpoint.md`
- `../patterns/exception-handler.md`
- `../recipes/analyze-crash.md`
- `../recipes/recover-call-stack.md`
- `../playbooks/Crash.md`

## Related Material

### Knowledge
- [anti-debugging](anti-debugging.md)
- [kernel-debugging](kernel-debugging.md)

### Patterns
- [breakpoint](../patterns/breakpoint.md)
- [exception-handler](../patterns/exception-handler.md)
- [stack-unwind-failure](../patterns/stack-unwind-failure.md)

### Recipes
- [analyze-crash](../recipes/analyze-crash.md)
- [analyze-exception](../recipes/analyze-exception.md)
- [analyze-hang](../recipes/analyze-hang.md)

### Playbooks
- [Crash](../playbooks/Crash.md)
- [Hang](../playbooks/Hang.md)
- [Performance](../playbooks/Performance.md)

### Examples
- [kernel-debugging](../examples/kernel-debugging.md)
- [stack-unwind](../examples/stack-unwind.md)
- [winDbg-crash-analysis](../examples/winDbg-crash-analysis.md)

### References
- [references](../references/references.md)

### Rules
- [debugging-principles](../rules/debugging-principles.md)

### Prompts
- [debug-process](../prompts/debug-process.md)
- [exception-analysis](../prompts/exception-analysis.md)
- [hang-analysis](../prompts/hang-analysis.md)

### Checklists
- [checklist](../checklists/checklist.md)

