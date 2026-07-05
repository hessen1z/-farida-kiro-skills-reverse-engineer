# Kernel Debugging Example

## Scenario
Investigate a kernel-mode driver crash using WinDbg and kernel memory inspection.

## Steps
1. Load the crash dump and verify symbols:
```text
.symfix
.reload /f
!analyze -v
```
2. Inspect the crashing thread:
```text
~* k
!thread <ThreadAddress>
```
3. Identify the bug check and faulting instruction:
```text
!analyze -v
kL
u <FaultingAddress>
```
4. Examine related kernel objects and memory:
```text
!process 0 0
!object 
!pool 0
!pte <Address>
```
5. Correlate the crash with driver code and IRQL state.

## Outcome
- Reconstructed the crash path from process state to kernel entry.
- Identified the driver or kernel module responsible for the fault.
- Documented the expected fix or mitigation.

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
- [kernel-apc-dpc-example](kernel-apc-dpc-example.md)
- [kernel-handle-table-example](kernel-handle-table-example.md)
- [kernel-memory-inspection](kernel-memory-inspection.md)

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

