---
title: Analyze Scheduler Recipe
skill: kernel
category: recipes
difficulty: intermediate
tags: [pe, windows, gui, kernel, debug]
updated: 2026-07-05
---
# Analyze Scheduler Recipe

## Purpose
Analyze Windows thread scheduling and dispatcher behavior to diagnose priority inversion, CPU starvation, and context-switch patterns.

## Prerequisites
- Kernel debugger with symbols.
- Familiarity with `KPRCB`, `KTHREAD`, and dispatcher object state.
- Access to processor ready queues and thread wait state.

## Inputs
- `KPRCB` ready queues and current thread state.
- thread priority, affinity, and wait reason.
- DPC and timer activity.

## Steps
1. Inspect the processor control block (`KPRCB`) and ready queues.
2. Analyze the current thread and its priority relative to other runnable threads.
3. Examine wait chains and dispatcher objects for blocked threads.
4. Review DPC activity and deferred processing latency.
5. Identify scheduling anomalies such as priority inversion or runaway threads.

## Verification
- Confirm that ready queues are balanced and that no threads are stuck in the wrong state.
- Verify that high-priority threads are not preempted incorrectly.
- Ensure all blocked threads are waiting on valid dispatcher objects.

## Notes
- Real-time threads (priority 16-31) have stricter scheduling expectations.
- DPC queue saturation can mask scheduler issues and cause system hangs.

## References
- `../knowledge/kernel-architecture.md`
- `../patterns/dispatcher-routines.md`
- `../examples/kernel-debugging.md`

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
- [analyze-kernel-component](analyze-kernel-component.md)
- [analyze-kernel-object](analyze-kernel-object.md)
- [analyze-memory-manager](analyze-memory-manager.md)

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

### Rules
- [kernel-guidelines](../rules/kernel-guidelines.md)

### Prompts
- [kernel-analysis](../prompts/kernel-analysis.md)
- [kernel-debugging-prompt](../prompts/kernel-debugging-prompt.md)
- [kernel-memory-analysis](../prompts/kernel-memory-analysis.md)

### Checklists
- [checklist](../checklists/checklist.md)

