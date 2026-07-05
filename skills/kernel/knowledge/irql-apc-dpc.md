# IRQL, APC, and DPC Knowledge

## Overview
IRQL, APC, and DPC are foundational Windows kernel mechanisms for interrupt management, asynchronous execution, and deferred work. Together they define which operations are permitted at a given execution level and how kernel-mode work is scheduled.

## Interrupt Request Levels (IRQL)
IRQL is a prioritized interrupt masking level used by the kernel to serialize access to shared resources and protect critical sections.

### Common IRQL Levels
- `PASSIVE_LEVEL`: normal thread execution, pageable operations allowed.
- `APC_LEVEL`: kernel APC delivery, asynchronous callbacks before waiting.
- `DISPATCH_LEVEL`: DPC execution and dispatcher lock held.
- `DIRQL`: device interrupt levels, higher than dispatcher.
- `HIGH_LEVEL`: highest priority for urgent hardware events.

### IRQL Rules
- code executing at `DISPATCH_LEVEL` cannot perform pageable calls or wait on pageable objects.
- acquiring a spin lock raises IRQL to `DISPATCH_LEVEL`.
- lowering IRQL may deliver pending APCs.

## APC (Asynchronous Procedure Call)
APCs are queued to threads for deferred execution in a thread context.

### APC Types
- **Kernel APCs**: run in kernel mode when a thread enters an alertable wait.
- **Special Kernel APCs**: used for critical operations such as user-mode thread termination.
- **User APCs**: run in user-mode when the thread enters an alertable wait.

### APC Data Structures
- `KAPC`: describes an APC object.
- `ETHREAD` includes APC state and pending APC queues.

## DPC (Deferred Procedure Call)
DPCs execute at `DISPATCH_LEVEL` to handle deferred interrupt processing and time-critical work.

### DPC Flow
1. ISR queues a DPC.
2. The DPC is placed on the processor’s DPC queue.
3. The dispatcher executes the DPC after the interrupt.

### DPC Data Structures
- `KDPC`: deferred procedure descriptor.
- `KDPC_QUEUE`: per-processor queue of pending DPCs.

## Memory Layout
The kernel allocates APC and DPC data structures from nonpaged pool. DPCs and APCs must remain resident because they may execute at elevated IRQL.

## Practical Workflows
- inspect APC queue state with WinDbg and `!thread`.
- analyze DPC latency with `!dpcs` or performance counters.
- verify that DPC routines do not call pageable code.

## Common Mistakes
- queuing DPCs from a thread without checking whether the DPC is already pending.
- executing pageable functions at `DISPATCH_LEVEL`.
- confusing kernel APCs with user APCs when tracing thread wakeups.

## References
- Windows Internals: Interrupts and Synchronization chapter

## Cross-links
- `../patterns/synchronization-primitives.md`
- `../examples/kernel-apc-dpc-example.md`
- `../recipes/analyze-scheduler.md`

## Related Material

### Knowledge
- [handle-tables](handle-tables.md)
- [interrupts-system-calls](interrupts-system-calls.md)
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

