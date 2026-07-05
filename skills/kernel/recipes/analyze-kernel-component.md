# Analyze Kernel Component Recipe

## Purpose
Analyze a Windows kernel component to understand its role in the executive, object management, scheduling, and I/O subsystems.

## Prerequisites
- Kernel symbols for the OS build.
- A kernel memory dump or live kernel debugging session.
- Familiarity with `EPROCESS`, `KTHREAD`, `DEVICE_OBJECT`, and `IRP` structures.

## Inputs
- target component name or driver.
- relevant crash dump or live debugger context.
- kernel module list and object references.

## Steps
1. Identify the component's kernel module and exported entry points.
2. Locate relevant global structures such as `ObTypeIndexTable`, `IoDriverObjectType`, and `KeServiceDescriptorTable`.
3. Catalog the component's object creation, dispatch routines, and memory allocations.
4. Analyze the component's IRQL boundaries and deferred execution patterns.
5. Verify lifecycle transitions, cleanup routines, and reference counting.

## Verification
- Confirm the component's primary functions and object interactions.
- Validate that IRQL transitions are correct for driver or executive code.
- Ensure no dangling references or leaked pool allocations remain.

## Notes
- A kernel component may span user-mode interaction through system calls and kernel-mode callbacks.
- Always preserve the host system state when debugging live kernel components.

## References
- `../knowledge/kernel-architecture.md`
- `../patterns/kernel-objects.md`
- `../playbooks/analyze-windows-kernel.md`

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
- [analyze-kernel-object](analyze-kernel-object.md)
- [analyze-memory-manager](analyze-memory-manager.md)
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

