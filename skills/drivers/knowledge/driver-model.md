---
title: Windows Driver Model
skill: drivers
category: knowledge
difficulty: intermediate
tags: [pe, windows, driver, gui, kernel, debug]
updated: 2026-07-05
---
# Windows Driver Model

## Overview

Windows kernel drivers implement a standardized model for handling I/O requests, device objects, and driver lifecycle events.

## Core concepts

- `DriverEntry` as the driver's entry point.
- `DRIVER_OBJECT` and `DEVICE_OBJECT` structures.
- I/O request packets (IRPs) for service requests.
- dispatch routines for major function codes.
- driver unload and cleanup semantics.

## Runtime architecture

A driver typically:
- initializes in `DriverEntry`
- creates device and symbolic link objects
- installs dispatch routines in the `DRIVER_OBJECT`
- processes IRPs for read, write, device control, and power management
- cleans up in `DriverUnload`

## Notes

- Drivers must synchronize access to shared state and hardware.
- IRP completion may occur in the dispatch routine or deferred via an I/O completion routine.

## IRP Lifecycle and Dispatch

- A driver receives IRPs via the `MajorFunction` table installed in `DRIVER_OBJECT`.
- Common major functions: `IRP_MJ_CREATE`, `IRP_MJ_CLOSE`, `IRP_MJ_DEVICE_CONTROL`, `IRP_MJ_READ`, `IRP_MJ_WRITE`.
- A typical dispatch routine validates parameters, processes or forwards the IRP, and either completes it or queues it for later completion.

Pseudo-code example:

```c
NTSTATUS MyDispatch(PDEVICE_OBJECT DeviceObject, PIRP Irp) {
		PIO_STACK_LOCATION sl = IoGetCurrentIrpStackLocation(Irp);
		switch (sl->MajorFunction) {
			case IRP_MJ_CREATE: /* init */ break;
			case IRP_MJ_DEVICE_CONTROL: /* handle IOCTLs */ break;
		}
		IoCompleteRequest(Irp, IO_NO_INCREMENT);
		return STATUS_SUCCESS;
}
```

## Synchronization and Common Bugs

- Use appropriate synchronization (spinlocks for IRQL-critical paths, mutexes for pageable contexts).
- Beware of paging and running at DISPATCH_LEVEL; do not call paged APIs at high IRQL.
- Common bugs: double-free of device objects, missed IoDeleteSymbolicLink on unload, leaking IRPs.

## Debugging Tips

- Use `!drvobj` and `!devobj` in WinDbg to inspect driver and device objects.
- Trace IRP paths by instrumenting dispatch routines with debug prints or by setting breakpoints on `IoCreateDevice` and major functions.

## References

- Windows Driver Kit documentation
- Microsoft kernel driver architecture guides

## Related Material

### Patterns
- [irp-flow](../patterns/irp-flow.md)

### Recipes
- [analyze-irp](../recipes/analyze-irp.md)
- [debug-driver](../recipes/debug-driver.md)

### Playbooks
- [DriverCrash](../playbooks/DriverCrash.md)
- [DriverLifecycle](../playbooks/DriverLifecycle.md)

### Examples
- [driver-entry](../examples/driver-entry.md)
- [irp-completion](../examples/irp-completion.md)

### References
- [references](../references/references.md)

### Prompts
- [driver-analysis](../prompts/driver-analysis.md)

### Checklists
- [checklist](../checklists/checklist.md)
## Practical Guidance

- Start from the concrete objective and define the expected outcome before applying the workflow.
- Use the related examples, recipes, playbooks, and references as the first implementation reference.
- Keep the guidance grounded in the surrounding skill context and verify the result with available evidence.
- Favor practical, maintainable steps over abstract theory when the document is used in real work.
## Verification Checklist

- Confirm that the main objective is clear and the workflow is actionable.
- Ensure the document points to the most relevant examples, recipes, or playbooks.
- Validate that the terminology is consistent with the rest of the skill.
- Check that the practical guidance is specific enough to be used without further interpretation.

## Tools & Commands

- WinDbg: `!drvobj`, `!devobj`, `!irp` for driver and IRP inspection.
- Windows Driver Kit (WDK) tooling for build/test, `Driver Verifier` for runtime stress, and `symchk`/`symstore` for symbols.

## Validation Checklist (Driver)

- Verify dispatch routines correctly forward and complete IRPs under normal and error conditions.
- Run `Driver Verifier` and stress tests to detect resource leaks, race conditions, and incorrect IRQL usage.
