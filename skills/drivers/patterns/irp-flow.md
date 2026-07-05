# IRP Flow Pattern

## Pattern Name
I/O request packet (IRP) flow

## Problem
Identify how a driver receives and processes I/O requests from the OS and user-mode applications.

## Context
IRPs are the primary mechanism for communicating I/O requests to kernel drivers.

## Recognition
- `IoCreateDevice`, `IoCreateSymbolicLink`
- setting `MajorFunction` entries in `DRIVER_OBJECT`
- switch statements or tables handling `IRP_MJ_` codes
- calls to `IoCompleteRequest`

## Evidence
- dispatch routines for read, write, device control, and create/close.
- completion paths that set `IoStatus.Status` and `IoStatus.Information`.
- use of `IoGetCurrentIrpStackLocation`

## Resolution / Action
- trace the request from dispatch entry to completion.
- identify deferred processing or worker queue usage.
- verify resource cleanup and error handling.

## Notes
- Some drivers use fast I/O or direct I/O for performance.
- IRP cancellation and power management add complexity.

## References
- Windows driver development documentation

## Related Material

### Knowledge
- [driver-model](../knowledge/driver-model.md)

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

