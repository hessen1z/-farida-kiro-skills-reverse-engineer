---
title: Kernel Rules
skill: kernel
category: rules
difficulty: intermediate
tags: [pe, gui, kernel, debug]
updated: 2026-07-05
---
# Kernel Rules

## Rule: Preserve IRQL Semantics
- Always verify that code paths and analysis points respect the current IRQL.
- Do not assume pageable functions are safe at `DISPATCH_LEVEL`.

## Rule: Use Symbol-Aware Analysis
- Kernel analysis should always use correct symbols for the target build.
- Avoid inferring structure layouts without version-specific symbols.

## Rule: Trace Object Ownership
- Kernel objects are reference-counted and may persist after handles close.
- Identify every owner and reference chain before concluding an object leak.

## Rule: Distinguish Cause and Effect
- Memory corruption may appear after a crash; identify whether it is causal.
- Use stack traces and scheduler state to correlate failure points.

## Rule: Prefer Non-Invasive Inspection
- Live kernel debugging should minimize state changes.
- Use dump analysis when memory corruption or stability is involved.

## Related Material

### Knowledge
- [handle-tables](../knowledge/handle-tables.md)
- [interrupts-system-calls](../knowledge/interrupts-system-calls.md)
- [irql-apc-dpc](../knowledge/irql-apc-dpc.md)

### Patterns
- [dispatcher-routines](../patterns/dispatcher-routines.md)
- [kernel-objects](../patterns/kernel-objects.md)
- [pool-allocations](../patterns/pool-allocations.md)

### Recipes
- [analyze-kernel-component](../recipes/analyze-kernel-component.md)
- [analyze-kernel-object](../recipes/analyze-kernel-object.md)
- [analyze-memory-manager](../recipes/analyze-memory-manager.md)

### Playbooks
- [analyze-executive-components](../playbooks/analyze-executive-components.md)
- [analyze-kernel-crash](../playbooks/analyze-kernel-crash.md)
- [analyze-kernel-memory](../playbooks/analyze-kernel-memory.md)

### Examples
- [kernel-apc-dpc-example](../examples/kernel-apc-dpc-example.md)
- [kernel-debugging](../examples/kernel-debugging.md)
- [kernel-handle-table-example](../examples/kernel-handle-table-example.md)

### References
- [references](../references/references.md)

### Prompts
- [kernel-analysis](../prompts/kernel-analysis.md)
- [kernel-debugging-prompt](../prompts/kernel-debugging-prompt.md)
- [kernel-memory-analysis](../prompts/kernel-memory-analysis.md)

### Checklists
- [checklist](../checklists/checklist.md)

