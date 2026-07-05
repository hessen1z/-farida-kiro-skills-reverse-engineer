# Analyze Windows Kernel Playbook

## Objective
Analyze a Windows kernel subsystem to identify execution flow, synchronization, memory management, and driver interactions.

## Steps
1. Define the kernel component or crash target under investigation.
2. Identify relevant symbols, object types, and dispatch routines.
3. Map the memory layout of process and kernel objects.
4. Inspect IRQL, scheduler, and interrupt state.
5. Review I/O flows, SSDT usage, and pool allocations.
6. Document findings and verify against expected kernel behavior.

## Common Scenarios
- kernel panic or bug check analysis
- driver dispatch and IRP failure
- pool corruption and memory leaks
- object and handle lifecycle issues

## Best Practices
- preserve system state before inspecting a live kernel.
- use symbol-aware commands such as `!process`, `!thread`, `!object`, and `!pool`.
- correlate thread wait reasons with dispatcher and scheduler state.
- validate all assumptions against kernel symbol data and version-specific structure layouts.

## Outcome
- a complete map of related kernel objects and subsystem interactions
- identified failure modes and root causes in kernel execution
- prioritized remediation or further analysis steps

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
- [analyze-kernel-crash](analyze-kernel-crash.md)
- [analyze-kernel-memory](analyze-kernel-memory.md)

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

