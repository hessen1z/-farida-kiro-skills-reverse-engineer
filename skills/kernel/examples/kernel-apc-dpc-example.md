# Kernel APC and DPC Example

## Scenario
Inspect APC and DPC behavior in a kernel component that defers work after interrupt handling.

## Steps
1. Identify the ISR that queues a DPC.
2. Trace the DPC object and callback routine.
3. Verify DPC execution at `DISPATCH_LEVEL`.
4. Inspect any APCs queued to the thread after DPC completion.

## Example
A minimal DPC routine:
```cpp
#include <ntddk.h>

KDPC gDpc;

void DpcRoutine(KDPC* Dpc, PVOID DeferredContext, PVOID SystemArgument1, PVOID SystemArgument2) {
    UNREFERENCED_PARAMETER(Dpc);
    UNREFERENCED_PARAMETER(DeferredContext);
    UNREFERENCED_PARAMETER(SystemArgument1);
    UNREFERENCED_PARAMETER(SystemArgument2);
    // Deferred work at DISPATCH_LEVEL
}

void QueueDpc() {
    KeInitializeDpc(&gDpc, DpcRoutine, nullptr);
    KeInsertQueueDpc(&gDpc, nullptr, nullptr);
}
```

## Outcome
- confirmed the DPC is queued and executed at `DISPATCH_LEVEL`
- validated the separation between interrupt handling and deferred processing
- identified any pageable code or blocking operations that would violate DPC constraints

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
- [kernel-debugging](kernel-debugging.md)
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

