# Analyze Kernel Memory Playbook

## Objective
Inspect kernel memory layout and pool allocations to diagnose leaks, corruption, and virtual memory faults.

## Steps
1. Review the kernel's virtual memory map and driver allocations.
2. Enumerate nonpaged and paged pool usage by tag.
3. Inspect `PFN` and page table structures for invalid mappings.
4. Trace memory ownership for suspicious buffers or objects.
5. Validate whether memory corruption precedes the crash or is a secondary effect.

## Common Scenarios
- pool header corruption and invalid free
- data structure corruption in `EPROCESS` or `KTHREAD`
- bad PTEs or swapped-out kernel pages
- incorrectly sized allocations at `DISPATCH_LEVEL`

## Best Practices
- use `!pool`, `!pte`, and `!vm` to inspect memory regions.
- identify the allocation tag before altering memory state.
- correlate corrupted pointers with module ownership and stack traces.
- prefer analysis on a dump rather than a live kernel for memory corruption.

## Outcome
- documented kernel memory layout and allocation ownership
- identified corruption source and impacted subsystems
- recommended memory management or driver allocation corrections

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

