---
title: Analyze Kernel Crash Playbook
skill: kernel
category: playbooks
difficulty: intermediate
tags: [pe, windows, driver, gui, kernel, debug]
updated: 2026-07-05
---
# Analyze Kernel Crash Playbook

## Objective
Investigate a Windows kernel crash or bug check to determine the faulty component, trigger conditions, and memory corruption evidence.

## Steps
1. Load the crash dump in WinDbg or analyze the bug check using kernel debugger commands.
2. Verify symbol paths and kernel module versions.
3. Inspect the bug check code and associated parameters.
4. Trace the crashing thread, exception record, and stack.
5. Examine memory manager and pool state for corruption.
6. Review scheduler and dispatcher state for concurrency issues.
7. Document the root cause and recommended kernel fix.

## Common Scenarios
- invalid memory access in kernel or driver
- double free or pool corruption
- deadlock or spin lock timeout
- IRQL violation or unexpected APC/DPC at high IRQL

## Best Practices
- confirm whether the crash is driver-owned or kernel core-owned.
- inspect preceding events and system warnings in event logs.
- compare the faulting address with known kernel or driver ranges.
- preserve an unmodified dump when passing it to other analysts.

## Outcome
- identified root cause for the bug check
- verified whether the crash arises from synchronization, memory corruption, or invalid system call usage
- action items for driver or kernel remediation

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
- [analyze-executive-components](analyze-executive-components.md)
- [analyze-kernel-memory](analyze-kernel-memory.md)
- [analyze-windows-kernel](analyze-windows-kernel.md)

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

