# Synchronization Primitives Pattern

## Pattern Name
Synchronization Primitives

## Problem
Detect kernel synchronization patterns and understand their IRQL and ownership semantics.

## Context
Windows kernel synchronization includes spin locks, push locks, mutexes, semaphores, events, and queued spin locks. Each primitive has usage constraints and performance trade-offs.

## Recognition
- `KeAcquireSpinLock`, `KeReleaseSpinLock`
- `ExEnterCriticalRegionAndAcquireResourceExclusive` / `ExReleaseResourceForThread`
- `KeWaitForSingleObject` on `KMUTANT`, `KSEMAPHORE`, or `KEVENT`
- `ExAllocatePoolWithTag` for `KMUTANT` or `ERESOURCE` structures

## Evidence
- IRQL requirements shown in code and stack traces
- contention indicators such as elevated spin lock acquisition latency
- appearence of `KSPIN_LOCK`, `EX_PUSH_LOCK`, or `KMUTANT` structures in memory dumps

## Resolution / Action
- match the primitive to the operation: exclusive access, shared access, event signaling, or deferred work
- verify that synchronization is held at the correct IRQL and released on all code paths
- identify deadlocks by analyzing lock order and wait chains

## Notes
- Spin locks are safe only at `DISPATCH_LEVEL` or above and must be released before lowering IRQL.
- Push locks and mutexes may block and may require APC-level or passive-level execution.

## References
- Windows Internals: Synchronization chapter

## See Also
- `../knowledge/kernel-architecture.md`
- `../patterns/interrupt-handler.md`
- `../recipes/analyze-kernel-component.md`

## Related Material

### Knowledge
- [handle-tables](../knowledge/handle-tables.md)
- [interrupts-system-calls](../knowledge/interrupts-system-calls.md)
- [irql-apc-dpc](../knowledge/irql-apc-dpc.md)

### Patterns
- [dispatcher-routines](dispatcher-routines.md)
- [kernel-objects](kernel-objects.md)
- [pool-allocations](pool-allocations.md)

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

