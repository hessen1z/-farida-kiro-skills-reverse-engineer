---
title: Exception Handler Pattern
skill: debugging
category: patterns
difficulty: intermediate
tags: [pe, windows, asm, x64, kernel, debug]
updated: 2026-07-05
---
# Exception Handler Pattern

## Pattern Name
Exception handler structure

## Problem
Identify exception handling and structured exception handling artifacts in binaries.

## Context
Exception handlers appear in user-mode, kernel-mode, and obfuscated binaries.

## Recognition
- x64 runtime function table entries (`RUNTIME_FUNCTION`)
- x86 SEH registration records on the stack
- vectored exception handler registrations (`AddVectoredExceptionHandler`)

## Evidence
- exception dispatch paths in crash dumps
- presence of `EXCEPTION_RECORD` and `CONTEXT` structures

## Resolution / Action
- map handlers to functions and unwind info
- inspect exception filters and handlers for crash recovery logic

## Examples
```asm
mov rax, fs:[0] ; x86 TEB chain head
```

## Notes
- C++ exception handling is layered on top of SEH.
- Exception-based control flow is common in protectors.

## References
- Windows Structured Exception Handling docs
- Microsoft x64 exception handling

## Related Material

### Knowledge
- [anti-debugging](../knowledge/anti-debugging.md)
- [debugging](../knowledge/debugging.md)
- [kernel-debugging](../knowledge/kernel-debugging.md)

### Patterns
- [breakpoint](breakpoint.md)
- [stack-unwind-failure](stack-unwind-failure.md)

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

