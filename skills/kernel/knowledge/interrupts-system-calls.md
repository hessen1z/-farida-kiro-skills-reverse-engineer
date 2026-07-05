# Interrupts and System Calls Knowledge

## Overview
Interrupts and system calls are the primary transitions between hardware, user mode, and kernel mode. This knowledge document explains how Windows handles hardware interrupts, software traps, system call dispatch, and the security implications of SSDT and syscall paths.

## Interrupt Handling

### Interrupt Flow
A hardware interrupt rises the processor IRQL to a device-specific level, dispatches the ISR, and optionally queues a DPC for deferred work. Interrupt handling is latency-sensitive and must minimize time spent at high IRQL.

### ISR and DPC
ISRs perform minimal work and queue DPCs for non-critical processing. DPCs run at `DISPATCH_LEVEL`, allowing the kernel to continue handling interrupts while completing I/O or signaling threads.

### Interrupt Objects
Interrupts are represented by `KINTERRUPT` objects and managed by the interrupt controller. Modern Windows uses APIC and message-signaled interrupts for scalable delivery.

## System Call Dispatch

### User-Kernel Transition
System calls cross from user mode to kernel mode using `syscall` on x64 or `sysenter` on x86. Gate descriptors and model-specific registers control the transition.

### SSDT and Service Descriptor
The SSDT maps service numbers to kernel entry points. A system call wrapper populates registers with the service index, and the dispatcher uses the table to transfer control.

### System Call Security
System call dispatch validates pointers, parameters, and thread context. Kernel code must avoid privilege escalation by enforcing user-mode address verification and object access control.

## Performance and Hazards

### Interrupt Latency
High interrupt frequency can starve normal threads and cause DPC queue backlog. Modern designs offload work to threads or use adaptive interrupt moderation.

### System Call Overhead
Frequent system calls have overhead from mode switching and validation. Efficient APIs minimize the number of cross-boundary transitions.

## Common Patterns
- `KeInsertQueueDpc` in ISR for deferred processing
- `syscall` service index loaded from `RCX`/`R11` registers
- `KiSystemServiceExit` return path after kernel service completion
- `NTSTATUS` result returned in `RAX`

## Analysis Considerations
- trace interrupt handlers with `!irp` and `!dpc`
- verify system call dispatch with `!ssdt` and `!kd`
- inspect CR3 and page table state if system calls access user-mode memory

## References
- Windows Internals: System Calls and Interrupts chapters
- Intel/AMD architecture manuals

## Cross-links
- `../patterns/interrupt-handler.md`
- `../patterns/ssdt-usage.md`
- `../recipes/analyze-ssdt.md`

## Related Material

### Knowledge
- [handle-tables](handle-tables.md)
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

