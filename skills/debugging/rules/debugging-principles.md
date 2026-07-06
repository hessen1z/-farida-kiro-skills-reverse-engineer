---
title: Debugging Rules
skill: debugging
category: rules
difficulty: intermediate
tags: [pe, driver, gui, kernel, debug]
updated: 2026-07-05
---
# Debugging Rules

## Rule 1: Verify Symbols
Always verify that symbol files match the binary version and GUID/age. Stale or mismatched symbols can mislead call stack recovery and function names.

## Rule 2: Preserve Evidence
Do not modify memory or execution state before capturing evidence from dumps or stable snapshots. Preserve original artifacts for later review.

## Rule 3: Use the Right Debugger
Choose user-mode, kernel-mode, or game-specific tools based on the target. Do not use user-mode-only debuggers for kernel or driver analysis.

## Rule 4: Respect Runtime State
When analyzing live processes, avoid invasive commands that may alter memory, thread state, or synchronization objects.

## Rule 5: Validate Hypotheses
Confirm root cause hypotheses with stack traces, exception records, and memory context before drawing conclusions.

## Related Material

### Knowledge
- [anti-debugging](../knowledge/anti-debugging.md)
- [debugging](../knowledge/debugging.md)
- [kernel-debugging](../knowledge/kernel-debugging.md)

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

### Prompts
- [debug-process](../prompts/debug-process.md)
- [exception-analysis](../prompts/exception-analysis.md)
- [hang-analysis](../prompts/hang-analysis.md)

### Checklists
- [checklist](../checklists/checklist.md)

