# Dispatcher Routines Pattern

## Pattern Name
Dispatcher Routines

## Problem
Recognize kernel dispatcher routines that manage thread scheduling, wait queues, and object signaling.

## Context
Dispatcher routines are the kernel-side implementations that respond to object state changes, thread wakeups, and DPC/APC transitions. They are central to context switching and synchronization.

## Recognition
- `KiSwapThread`, `KiSchedule`, `KeSetEvent`, `KeWaitForSingleObject`
- `DISPATCHER_HEADER` fields in kernel memory
- function prologues using `KiInsertQueueApc`, `KiQueueReadyThread`, `KiUnlockDispatcherDatabase`
- ready queue manipulations in `KPRCB`

## Evidence
- thread state changes in `!thread` output
- active and wait queues visible through `!queue` and `!kdqueue`
- IRQL elevation and dispatch level transitions during object signaling

## Resolution / Action
- map a dispatcher routine to the object type and wait condition being serviced
- verify whether a wait object is signaled by a timer, mutex, or I/O completion
- trace the thread lifetime from wait to ready to running

## Notes
- Dispatcher routines may execute at `DISPATCH_LEVEL`, so they cannot perform pageable operations or block indefinitely.
- Many kernel objects share `DISPATCHER_HEADER`, making diagnosis of queues and events consistent across object types.

## References
- Windows Internals: Scheduling and Dispatcher chapter

## See Also
- `../patterns/synchronization-primitives.md`
- `../recipes/analyze-scheduler.md`
- `../playbooks/analyze-kernel-crash.md`

## Related Material

### Knowledge
- [handle-tables](../knowledge/handle-tables.md)
- [interrupts-system-calls](../knowledge/interrupts-system-calls.md)
- [irql-apc-dpc](../knowledge/irql-apc-dpc.md)

### Patterns
- [kernel-objects](kernel-objects.md)
- [pool-allocations](pool-allocations.md)
- [ssdt-usage](ssdt-usage.md)

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

