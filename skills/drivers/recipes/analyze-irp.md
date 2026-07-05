# Analyze IRP Recipe

## Purpose
Analyze I/O request packet handling within a driver to identify dispatch behavior, error conditions, and resource usage.

## Prerequisites
- Driver binary and dispatch routine access.
- Debugger or disassembler to inspect IRP handling.
- Knowledge of Windows major function codes.

## Inputs
- `IRP_MJ_*` dispatch handlers.
- stack locations and completion routines.
- device context and synchronization state.

## Steps
1. Identify `IRP_MJ_CREATE`, `IRP_MJ_READ`, `IRP_MJ_WRITE`, and `IRP_MJ_DEVICE_CONTROL` handlers.
2. Inspect how the driver retrieves the current IRP stack location.
3. Trace how the IRP is completed and when `IoCompleteRequest` is called.
4. Review error handling and cancelation paths.
5. Validate whether the driver uses completion routines or worker threads.

## Verification
- Confirm the IRP status and information fields are set correctly.
- Verify that all allocation and cleanup paths are covered.
- Document any potential race conditions or deadlocks.

## Notes
- Some drivers forward IRPs to lower drivers in a filter stack.
- IRP cancellation handling is critical for robust drivers.

## References
- Windows driver model and IRP documentation

## Related Material

### Knowledge
- [driver-model](../knowledge/driver-model.md)

### Patterns
- [irp-flow](../patterns/irp-flow.md)

### Recipes
- [debug-driver](debug-driver.md)

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

