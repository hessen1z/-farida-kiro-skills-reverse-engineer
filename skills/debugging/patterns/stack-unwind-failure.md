---
title: Stack Unwind Failure Pattern
skill: debugging
category: patterns
difficulty: intermediate
tags: [pe, windows, x64, gui, kernel, debug]
updated: 2026-07-05
---
# Stack Unwind Failure Pattern

## Pattern Name
Incomplete or corrupted stack unwind

## Problem
The debugger cannot recover a full call stack due to missing unwind metadata, corrupted stack frames, or invalid return addresses.

## Context
This occurs in stripped binaries, manually crafted code, or when stack memory is damaged.

## Recognition
- `k` shows truncated or missing frames
- `!analyze -v` reports `bad stack frame` or `unable to unwind
- Frame pointers do not form a valid chain

## Evidence
- return addresses outside executable sections
- mismatched stack memory values
- missing `RUNTIME_FUNCTION` entries for x64

## Resolution / Action
- verify module boundaries and image bases
- use frame pointer chains when available
- reconstruct frames manually using register and stack memory

## Examples
```text
0x00007ff6`12345678 ???
0x00007ff6`12345000 ???
```

## Notes
- x64 relies on unwind metadata; corrupted tables make stack recovery harder.
- Document confidence levels for manually reconstructed stacks.

## References
- WinDbg stack walking documentation
- Windows x64 unwind metadata guides

## Related Material

### Knowledge
- [anti-debugging](../knowledge/anti-debugging.md)
- [debugging](../knowledge/debugging.md)
- [kernel-debugging](../knowledge/kernel-debugging.md)

### Patterns
- [breakpoint](breakpoint.md)
- [exception-handler](exception-handler.md)

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

