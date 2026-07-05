# Handle Tables Knowledge

## Overview
Handle tables are per-process structures that provide opaque access to kernel objects. They mediate security checks, reference counting, and object lifetime.

## Handle Table Structure
A handle table includes:
- `TableCode`: encoded pointer to allocation and deletion state
- `HandleCount`: number of active handles
- entries for each open handle

### HANDLE_TABLE_ENTRY
Each entry stores:
- object pointer
- granted access mask
- attributes such as inheritance and protection
- reference count for lifetime management

## Handle Translation
Handles are translated to kernel objects by `ObReferenceObjectByHandle`, which validates access rights against the object’s security descriptor.

## Security and Access
Handle operations invoke the Object Manager to enforce ACLs. `NtOpenProcess`, `NtOpenThread`, and file handle opens pass through handle table validation.

## Practical Workflows
- inspect a handle table with debugger extension commands.
- correlate handle values with object addresses.
- verify that duplicate handles share the same object reference.

## Common Mistakes
- assuming handle values are global across processes.
- using stale handles after object deletion.
- neglecting to consider handle inheritance across process creation.

## References
- Windows Internals: Object Manager and Handle Tables

## Cross-links
- `../knowledge/process-thread-manager.md`
- `../patterns/kernel-objects.md`
- `../recipes/analyze-kernel-object.md`

## Related Material

### Knowledge
- [interrupts-system-calls](interrupts-system-calls.md)
- [irql-apc-dpc](irql-apc-dpc.md)
- [kernel-architecture](kernel-architecture.md)

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

### Rules
- [kernel-guidelines](../rules/kernel-guidelines.md)

### Prompts
- [kernel-analysis](../prompts/kernel-analysis.md)
- [kernel-debugging-prompt](../prompts/kernel-debugging-prompt.md)
- [kernel-memory-analysis](../prompts/kernel-memory-analysis.md)

### Checklists
- [checklist](../checklists/checklist.md)

