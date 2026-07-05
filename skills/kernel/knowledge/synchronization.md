# Synchronization Knowledge

## Overview
Kernel synchronization primitives coordinate access to shared resources and ensure correct execution ordering across threads, interrupts, and deferred routines.

## Synchronization Primitives
- `KSPIN_LOCK` for high-IRQL mutual exclusion
- `KMUTANT` and `KEVENT` for blocking synchronization
- `EX_PUSH_LOCK` for shared/exclusive access
- `KERB` / `FAST_MUTEX` for low-contention mutual exclusion
- DPC and APC objects for deferred execution

## Dispatcher Objects
All kernel dispatcher objects share a `DISPATCHER_HEADER`.
Key types include:
- events
- semaphores
- timers
- queues

## Kernel Timers and Work Items
- `KTIMER` schedules future execution.
- `KDPC` may be associated with a timer to perform deferred work.
- `WORK_QUEUE_ITEM` executes on worker threads at `PASSIVE_LEVEL`.

## IRQL and Synchronization
Different primitives require different IRQL levels.
- spin locks at `DISPATCH_LEVEL`
- mutexes and events at `PASSIVE_LEVEL`
- DPCs at `DISPATCH_LEVEL`

## Practical Workflows
- verify the correct primitive for the operation and IRQL.
- check wait chains for deadlocks caused by inverse lock ordering.
- analyze DPC activity and timer callback execution.

## Common Mistakes
- using nonpaged pool data in a spin lock-protected context incorrectly.
- blocking at `DISPATCH_LEVEL`.
- assuming `ExAcquireFastMutex` behaves like a spin lock.

## References
- Windows Internals: Synchronization chapter

## Cross-links
- `../patterns/synchronization-primitives.md`
- `../examples/kernel-debugging.md`

## Related Material

### Knowledge
- [handle-tables](handle-tables.md)
- [interrupts-system-calls](interrupts-system-calls.md)
- [irql-apc-dpc](irql-apc-dpc.md)

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

