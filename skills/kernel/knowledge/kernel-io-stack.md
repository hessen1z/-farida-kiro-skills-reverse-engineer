# Kernel I/O and Driver Interaction

## Overview
The Windows I/O Manager and file system stack coordinate device access, IRP dispatch, and driver interaction. This knowledge document explains how kernel-mode components expose devices, process file operations, and route I/O through layered driver stacks.

## I/O Manager Architecture

### IRP Lifecycle
I/O requests are represented by an I/O Request Packet (`IRP`). The I/O Manager creates the IRP and dispatches it to a driver's dispatch routine. The IRP flows through a stack of device objects and may be completed synchronously or asynchronously.

### Device Objects
Drivers create `DEVICE_OBJECT` structures with `IoCreateDevice`. Each device object includes:
- `DriverObject` pointer
- `DeviceExtension` for driver-specific state
- `StackSize` indicating IRP stack depth
- `Flags` for buffering and power management

### File Objects
File operations are represented by `FILE_OBJECT` structures. They track file handles, create contexts, and shared access. File objects are created on `IRP_MJ_CREATE` and destroyed on `IRP_MJ_CLEANUP` / `IRP_MJ_CLOSE`.

## File System Stack

### Major Function Dispatch
File system drivers implement major function dispatch tables for operations such as:
- `IRP_MJ_CREATE`
- `IRP_MJ_READ`
- `IRP_MJ_WRITE`
- `IRP_MJ_DEVICE_CONTROL`
- `IRP_MJ_CLEANUP`
- `IRP_MJ_CLOSE`

The I/O Manager passes IRPs to `DriverObject->MajorFunction[MajorCode]`.

### Fast I/O and Caching
Fast I/O callbacks provide lightweight path execution for common file operations without full IRP dispatch. The Cache Manager integrates with file systems to improve read/write performance and reduce disk access.

## Driver Interaction

### Dispatch Routines
A driver’s dispatch routine handles the IRP and may:
- process the request directly
- queue it for later work
- call `IoCompleteRequest` to finish it
- pass it down the device stack with `IoCallDriver`

### Completion and Cancellation
Completion routines run after a lower driver finishes processing an IRP. Cancellation routines support aborting requests if a handle is closed or a timeout occurs.

### Plug and Play and Power
Driver interaction also includes Plug and Play notifications, power management callbacks, and dynamic device state transitions. These extend the I/O Manager with device enumeration and runtime resource control.

## Internal Memory Layout

### IRP Stack Locations
An `IRP` contains an array of `IO_STACK_LOCATION` entries. Each driver in the stack has its own stack location, control flags, and context.

### Device and File Metadata
`DEVICE_OBJECT` and `FILE_OBJECT` structures are allocated from nonpaged pool and contain pointers to driver-specific extensions and open instance state.

## Practical Workflows

### Analyze Driver Dispatch
1. Identify the driver and its `DriverObject` in a memory dump.
2. Examine major function pointers and `DeviceObject` stack depth.
3. Trace an IRP through `IoCallDriver` and completion routines.
4. Validate whether the request is completed at the correct stack level.

### Analyze File System Stack
1. Map a file handle to its `FILE_OBJECT` and underlying device objects.
2. Inspect fast I/O callbacks and fallback IRP dispatch routes.
3. Correlate file operations with cache manager activity and media access.

## Common Mistakes
- Treating `FILE_OBJECT` contents as stable across I/O requests.
- Ignoring the stacked nature of IRP stack locations when diagnosing dispatch failures.
- Assuming IRPs are always completed in the same driver that created them.

## References
- Windows Internals: I/O Manager chapter
- MSDN documentation for IRP, DRIVER_OBJECT, and DEVICE_OBJECT

## Cross-links
- `../knowledge/kernel-architecture.md`
- `../recipes/analyze-kernel-component.md`
- `../examples/kernel-driver-dispatch.md`

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

