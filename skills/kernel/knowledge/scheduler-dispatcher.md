# Scheduler and Dispatcher Knowledge

## Overview
The Windows scheduler and dispatcher coordinate thread execution across processors, handling ready queues, priority levels, context switches, and wait states. This knowledge document covers dispatcher object design, scheduler policies, and the interaction between kernel scheduling and deferred work.

## Dispatcher Architecture

### Dispatcher Objects
Dispatcher objects share a common `DISPATCHER_HEADER` layout. Common types are:
- `Event`
- `Semaphore`
- `Mutex` (`KMUTANT`)
- `Timer` (`KTIMER`)
- `Queue` (`KQUEUE`)

Each dispatcher object stores a signal state, wait list, and type-specific fields. Thread wait operations and signaling routines manipulate the `DISPATCHER_HEADER`.

### Object Signaling
A thread waits on dispatcher objects using functions such as `KeWaitForSingleObject` and `KeWaitForMultipleObjects`. Signaling an object wakes one or more waiting threads, potentially triggering a scheduler decision.

## Scheduling Basics

### Priority Levels
Windows defines 32 priority levels, split into:
- real-time priorities (16-31)
- variable priorities (0-15)

Thread execution order is determined by priority, with quantum expiration and priority boosts influencing scheduling behavior.

### Processor Control Block (KPRCB)
Each logical processor has a `KPRCB` containing:
- ready queues for each priority
- current thread pointer
- idle thread reference
- DPC queue and statistics

The scheduler consults `KPRCB` to choose the next thread to run.

## Thread State Transitions

### Lifecycle States
Threads transition through states such as:
- `Initialized`
- `Ready`
- `Running`
- `Standby`
- `Waiting`
- `Terminated`

The scheduler moves threads from `Ready` to `Running`, while waits and I/O can move threads to `Waiting`.

### Context Switch
A context switch saves the outgoing thread's kernel state and restores the incoming thread's state. This includes registers, stack pointers, and processor control structures.

## Deferred Execution

### APCs
Asynchronous Procedure Calls execute when threads are in an alertable state. They can be used for I/O completion, user-mode callbacks, or kernel-mode cleanup.

### DPCs
Deferred Procedure Calls run at `DISPATCH_LEVEL` and service interrupt-related work. They are queued to processors and execute before returning control to normal thread scheduling.

## Common Patterns
- priority boost after I/O completion
- thread wait on dispatcher object signal
- DPC queue drain before processing lower-priority work
- thread preemption by higher priority runnable thread

## Analysis Considerations
- `!thread` and `!process` reveal wait reasons and dispatch status.
- `!runaway` and `!dpc` help locate scheduler or DPC saturation issues.
- IRQL elevation changes the permissible work and dispatch behavior.

## References
- Windows Internals: Scheduling chapter
- Microsoft kernel debugger documentation

## Cross-links
- `../patterns/dispatcher-routines.md`
- `../recipes/analyze-scheduler.md`
- `../playbooks/analyze-windows-kernel.md`

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

