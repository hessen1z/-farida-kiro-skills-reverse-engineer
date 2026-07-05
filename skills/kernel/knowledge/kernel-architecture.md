# Windows Kernel Architecture

## Overview
The Windows kernel is a layered executive architecture built around the NT kernel, executive subsystems, and kernel-mode services. It provides scheduling, dispatching, memory management, object management, I/O processing, and synchronization while enforcing privilege separation, IRQL boundaries, and secure resource ownership.

This document explains the core kernel subsystems, their memory layouts, internal data structures, and practical analysis workflows for kernel-mode behavior.

## Windows Kernel Architecture

### Kernel and Executive Layers
The Windows kernel has two primary layers:
- The **kernel** core (ntoskrnl.exe) manages low-level CPU abstractions, interrupt handling, and context switching.
- The **executive** implements higher-level services such as object management, memory management, process and thread management, I/O control, and security.

Important executive components include:
- Object Manager (`Ob`, `Io`)
- Memory Manager (`Mm`)
- Process Manager (`Ps`, `Psp`)
- I/O Manager (`Io`)
- Security Reference Monitor (`Sep`)
- Plug and Play Manager (`Pnp`)

### Execution Model
Windows execution is driven by thread scheduling and interrupt dispatching. Each logical processor runs a **Dispatcher Database** (`KPRCB`) that maintains ready queues, current thread state, and context switch statistics. The scheduler selects threads across priorities and processor affinity while respecting IRQL and dispatcher locks.

### Key Kernel Data Structures
- `EPROCESS` and `ETHREAD`: process and thread control blocks
- `KPROCESS` and `KTHREAD`: kernel scheduling representations
- `KAPC`, `KDPC`, `KTIMER`: asynchronous execution and delayed routine management
- `KSPIN_LOCK`, `ERESOURCE`, `KMUTANT`: synchronization primitives
- `OBJECT_HEADER`, `OBJECT_TYPE`: object management metadata
- `SSDT` and `shadow SSDT`: system call dispatch tables
- `PTE`, `PFN`, `MMVAD`: memory manager page and virtual address descriptors

## Executive

### Object Manager
The Object Manager centralizes resource lifetime and access control. It represents kernel and user objects as handles backed by object header metadata. Important concepts include:
- Object names and directory trees
- Object types and type-specific dispatch routines
- Handle tables and reference counting
- Namespace separation between kernel and user objects

### Security and Access
Object access is mediated by Access Control Lists (ACLs), security descriptors, and subject context. The Object Manager verifies rights before granting handles, and uses the security reference monitor to enforce privileges and audit events.

### Object Manager Memory Layout
Objects live in a mix of pool allocations and section-backed storage. Each object has an `OBJECT_HEADER`, optional `OBJECT_HEADER_NAME_INFO`, `OBJECT_HEADER_CREATOR_INFO`, and the object body. Handle tables are per-process structures allocated from nonpaged pool with `HANDLE_TABLE_ENTRY` records.

## Scheduler

### Dispatch and Priorities
Windows uses a priority-driven scheduler with 32 priority levels. Threads are either **real-time** or **variable**. The dispatcher implements ready queues per priority, quantums, and affinity. The scheduler also handles priority boosts for I/O completion and wait state transitions.

### Scheduling Data Structures
- `KPRCB`: processor control block containing ready queues, current thread, and scheduling data
- `KQUEUE`: dispatcher objects used for wait and queue management
- `DISPATCHER_HEADER`: shared header for events, semaphores, timers, and queues

### Context Switch and Thread States
A thread transitions between `Ready`, `Running`, `Standby`, `Waiting`, and `Terminated`. The scheduler and dispatcher collaborate through `KiSwapThread`, `KiEndDeferredProcessing`, and `KeWaitForSingleObject`.

## IRQL

### Interrupt Request Levels
IRQL defines the priority of execution contexts. Common IRQL values include:
- `PASSIVE_LEVEL` (0)
- `APC_LEVEL` (1)
- `DISPATCH_LEVEL` (2)
- `DIRQL` (device-specific interrupt levels)
- `HIGH_LEVEL`

At higher IRQL, normal kernel routines and thread context switches are blocked. Synchronization primitives have strict IRQL requirements.

### IRQL Transitions
The kernel raises IRQL during interrupt servicing, DPC execution, and critical sections. `KeRaiseIrql`, `KeLowerIrql`, and `KeAcquireSpinLock` are the primary instructions for moving between levels. IRQL mismatches cause deadlocks, lost interrupts, or corrupt state.

## APC and DPC

### APC (Asynchronous Procedure Call)
APCs are queued to threads and execute when the thread enters an alertable wait state. There are three APC types:
- Kernel APC
- Special kernel APC
- User APC

APCs can be used for I/O completion, delayed procedure execution, and thread cleanup.

### DPC (Deferred Procedure Call)
DPCs run at `DISPATCH_LEVEL` and service interrupt-related deferred work. They are queued to a processor's DPC queue and execute after the interrupt handler returns. Common DPC uses include timer callbacks, I/O completion, and synchronization operations.

## Interrupt Handling

### Hardware Interrupts
The kernel uses the interrupt dispatcher to manage IRQs and interrupt service routines (ISRs). For modern Windows versions, interrupt handling is represented by `KINTERRUPT` objects, and IRQ routing uses the APIC or I/O APIC.

### Interrupt Flow
1. Hardware interrupt arrives.
2. CPU enters high IRQL and vector dispatches to ISR.
3. ISR performs minimal work and may queue a DPC.
4. DPC executes at `DISPATCH_LEVEL` to complete deferred work.

### MSI/MSI-X and APIC Virtualization
Interrupt virtualization and message-signaled interrupts are handled by dedicated kernel objects and virtualization layers on Hyper-V or device drivers.

## System Calls and SSDT

### System Call Entry
System calls transition from user mode to kernel mode through `syscall/sysenter` on x64 or `int 0x2e` / `sysenter` on x86. The dispatcher updates thread state and switch stack before calling the target service routine.

### SSDT and Shadow SSDT
The System Service Descriptor Table (SSDT) contains pointers to kernel service routines. Hooking or patching the SSDT is a classic kernel rootkit technique. In 64-bit Windows, a shadow SSDT is used for system calls from WOW64 processes.

### System Call Numbering
Each service has a fixed index. User-mode stubs resolve service numbers either via import tables or dynamic system call wrappers.

## Memory Manager

### Virtual Memory
The Memory Manager abstracts physical memory behind virtual address spaces. Key components:
- PTEs and page tables
- Page frame database (`PFN` entries)
- Virtual Address Descriptors (`VAD`)
- Working sets and page fault handling

Windows uses demand paging, copy-on-write, and memory-mapped sections to manage process address spaces.

### Paging and Page Faults
A page fault triggers the Memory Manager to resolve the missing mapping, allocate or retrieve the page, and update page tables. Fault handling can occur at `PASSIVE_LEVEL` or elevated IRQL depending on whether the page is resident.

### Pool Allocator
The kernel uses paged and nonpaged pool for dynamic allocations. Important aspects:
- Tagging for diagnostic clarity
- Allocation routines: `ExAllocatePoolWithTag`, `ExFreePoolWithTag`
- Lookaside lists and sub-pools for efficiency

### Memory Manager Data Structures
- `MMVAD`: describes committed ranges and protection attributes
- `MMPTE`: page table entry representing access rights and page state
- `MMPFN`: page frame number database entries
- `MMWSL`: working set list and page fault tracking

## Process and Thread Manager

### Process Manager
The Process Manager creates and terminates processes, sets up address spaces, and manages process credentials. It orchestrates image loading, handle table initialization, and process object creation.

### Thread Manager
Threads are the execution context of processes. The Thread Manager supports thread creation, state transitions, APC delivery, and scheduling. Each thread has a `KTHREAD` and associated user-mode thread information.

### Handle Tables
Handle tables mediate access to kernel objects. Each process has a handle table with `HANDLE_TABLE_ENTRY` slots. Handles are validated and reference-counted when used to access objects.

### Process and Thread Memory Layout
Process structures consist of `EPROCESS` with embedded `KPROCESS`, handle table pointers, and security context. Threads contain `ETHREAD`, `KTHREAD`, stack information, and APC state.

## Synchronization

### Spin Locks
`KSPIN_LOCK` is the primitive for protecting critical sections at `DISPATCH_LEVEL`. Spin locks disable normal interrupts or raise IRQL to prevent concurrent access on the same processor.

### Push Locks
`EX_PUSH_LOCK` supports shared and exclusive access, with fast path acquisition and wait block queuing. Used in file system and memory subsystem locks.

### Fast Mutex
`FAST_MUTEX` provides a hybrid mutex optimized for low-contention scenarios. It can block the requesting thread at `APC_LEVEL` and includes ownership and contention tracking.

### Kernel Timers and Work Items
- `KTIMER` schedules deferred execution after a delay or at a specific time.
- `WORK_QUEUE_ITEM` and thread pool work items execute callbacks in worker threads at passive IRQL.

### Synchronization Memory Layout
Dispatcher objects share `DISPATCHER_HEADER` layout. `KSPIN_LOCK` is typically a 4-byte value, while `KMUTANT` derives from `DISPATCHER_HEADER` with owner and APC state fields.

## I/O Manager and File System Stack

### I/O Manager
The I/O Manager manages IRP dispatch, device objects, driver stacks, and I/O completion. It is the central hub for file, device, and network I/O in kernel mode.

### File System Stack
File operations traverse layered file system drivers through IRP major functions such as `IRP_MJ_READ`, `IRP_MJ_WRITE`, `IRP_MJ_CREATE`, and `IRP_MJ_CLOSE`. File systems use `FSD` and `FSP` threads, cache manager interactions, and security callbacks.

### Driver Interaction
Drivers expose `DriverEntry`, create `DEVICE_OBJECT` and `FILE_OBJECT` structures, and hook dispatch routines. The I/O Manager queues IRPs to driver stacks and manages completion via `IoCompleteRequest`.

## Kernel Debugging

### Kernel Debugging Models
Windows supports local and remote kernel debugging with KD protocol, WinDbg, and hypervisor-based debugging. Core concepts include:
- Symbol resolution for kernel and drivers
- `!process`, `!thread`, `!object`, and `!vm` analysis commands
- Crash dump analysis with `!analyze -v`

### Debugging Memory Layouts
Kernel debugging requires understanding the layout of `EPROCESS`, `ETHREAD`, `KPCR`, `KPRCB`, and page tables. Inspecting these structures reveals object references, process address spaces, and interrupt state.

## Practical Workflows

### Kernel Component Analysis
To analyze a kernel component:
1. Identify the component's entry and dispatch paths.
2. Map object allocations, handle usage, and memory ownership.
3. Track IRQL transitions and synchronization behavior.
4. Cross-reference with driver or kernel debug symbols.

### Memory Manager Analysis
1. Inspect VAD ranges and committed pages.
2. Verify page table entries and working set state.
3. Analyze pool allocations and tagged memory usage.
4. Use tools such as WinDbg `!vm`, `!pool`, and `!pte`.

### Scheduler Analysis
1. Examine ready queues and current thread priorities.
2. Inspect `KPRCB` and `KTHREAD` state.
3. Identify blocked or waitable threads.
4. Correlate dispatcher object waits with DPC and APC activity.

## Common Mistakes
- Confusing user-mode thread state with kernel `KTHREAD` state.
- Analyzing IRP flows without considering I/O completion and cancel paths.
- Assuming pool allocations are contiguous or same-sized.
- Ignoring IRQL rules when reasoning about synchronization and deferred execution.

## References
- Windows Internals by Russinovich, Solomon, and Ionescu
- Microsoft Windows Kernel-Mode Driver Architecture
- Microsoft Debugging Tools for Windows
- Intel Software Developer Manual

## Cross-links
- `../patterns/kernel-objects.md`
- `../patterns/interrupt-handler.md`
- `../recipes/analyze-kernel-component.md`
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

