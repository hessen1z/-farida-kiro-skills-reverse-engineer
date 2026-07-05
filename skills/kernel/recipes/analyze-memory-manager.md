# Analyze Memory Manager Recipe

## Purpose
Analyze the Windows memory manager to understand page faults, virtual memory layout, pool behavior, and page table state.

## Prerequisites
- Kernel debugging tools and symbols.
- Knowledge of virtual memory concepts and page tables.
- Access to a dump or live kernel session.

## Inputs
- process address space and VAD information.
- page table and physical frame metadata.
- pool allocation tracking data.

## Steps
1. Inspect the process's VAD tree and committed address ranges.
2. Examine page tables for `PTE` state, protection bits, and physical mapping.
3. Verify working set entries and resident page counts.
4. Analyze pool allocations by tag and IRQL context.
5. Identify page faults, guard pages, and copy-on-write behavior.

## Verification
- Confirm the virtual address layout matches expected process regions.
- Validate that page table entries reflect correct access and cache settings.
- Detect pool leaks or corrupted page table entries.

## Notes
- Page fault analysis may require interpreting both user and kernel PTEs.
- Nonpaged pool data can be accessed at high IRQL; paged pool cannot.

## References
- `../knowledge/kernel-architecture.md`
- `../patterns/pool-allocations.md`
- `../examples/kernel-memory-inspection.md`

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
- [analyze-scheduler](analyze-scheduler.md)

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

