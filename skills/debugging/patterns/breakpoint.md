---
title: Breakpoint Pattern
skill: debugging
category: patterns
difficulty: intermediate
tags: [pe, asm, kernel, debug]
updated: 2026-07-05
---
# Breakpoint Pattern

## Pattern Name
Breakpoint instruction pattern

## Problem
Detect code that intentionally triggers a debugger trap or software breakpoint.

## Context
Software breakpoints are used in debugging, instrumentation, and anti-analysis.

## Recognition
- `INT3` (`0xCC`) in code sections
- `INT 3` assembly mnemonic
- inline patching of instruction bytes with `0xCC`

## Evidence
- code execution stops when a debugger is attached
- debugger reports `INT3` or breakpoint exception

## Resolution / Action
- inspect the affected instruction and surrounding code
- determine whether it is a debug trap or intentional protection
- restore original bytes if needed for analysis

## Examples
```asm
int3
```

## Notes
- Hardware breakpoints do not modify code bytes.
- Software breakpoints may be inserted by debuggers or stub code.

## References
- Intel x86 manuals
- WinDbg breakpoint documentation

## Related Material

### Knowledge
- [anti-debugging](../knowledge/anti-debugging.md)
- [debugging](../knowledge/debugging.md)
- [kernel-debugging](../knowledge/kernel-debugging.md)

### Patterns
- [exception-handler](exception-handler.md)
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

