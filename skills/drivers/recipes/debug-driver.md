---
title: Debug Driver Recipe
skill: drivers
category: recipes
difficulty: intermediate
tags: [pe, windows, driver, kernel, debug]
updated: 2026-07-05
---
# Debug Driver Recipe

## Purpose
Debug kernel drivers, identify driver crashes or misbehaviors, and diagnose I/O path failures.

## Prerequisites
- Kernel debugger or crash dump access.
- Driver binary and symbol files.
- Knowledge of driver objects and IRP handling.

## Inputs
- driver module name and loaded address.
- IRP dispatch routines and failure paths.
- device object and power management state.

## Steps
1. Connect to the target using a kernel debugger.
2. Load driver symbols and confirm module list.
3. Inspect `DriverEntry`, device creation, and dispatch table.
4. Trace IRP handling and completion paths.
5. Analyze crashes and call stacks using `!analyze -v`.

## Verification
- Confirm the fault is within driver code or device handling.
- Validate that IRP status codes are handled correctly.
- Ensure clean driver unload and cleanup.

## Notes
- Kernel debugger commands include `!process`, `!thread`, and `!irp`.
- Keep the target stable when debugging drivers.

## References
- Windows kernel debugging documentation
- Driver analysis resources

## Related Material

### Knowledge
- [driver-model](../knowledge/driver-model.md)

### Patterns
- [irp-flow](../patterns/irp-flow.md)

### Recipes
- [analyze-irp](analyze-irp.md)

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

