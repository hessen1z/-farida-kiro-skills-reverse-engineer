---
title: Driver Entry Example
skill: drivers
category: examples
difficulty: intermediate
tags: [pe, driver, gui, debug]
updated: 2026-07-05
---
# Driver Entry Example

## Scenario
Analyze a driver's `DriverEntry` and device creation flow.

## Steps
1. Inspect `DriverEntry` for `IoCreateDevice` and `IoCreateSymbolicLink` calls.
2. Review the driver object's `MajorFunction` table assignments.
3. Identify whether the driver sets a `DriverUnload` routine.
4. Document the initialization path and error handling.

## Outcome
- Confirm the driver's initial setup path.
- Identify any missing cleanup or initialization failures.
- Determine whether the driver is a filter or function driver.

## Related Material

### Knowledge
- [driver-model](../knowledge/driver-model.md)

### Patterns
- [irp-flow](../patterns/irp-flow.md)

### Recipes
- [analyze-irp](../recipes/analyze-irp.md)
- [debug-driver](../recipes/debug-driver.md)

### Playbooks
- [DriverCrash](../playbooks/DriverCrash.md)
- [DriverLifecycle](../playbooks/DriverLifecycle.md)

### Examples
- [irp-completion](irp-completion.md)

### References
- [references](../references/references.md)

### Prompts
- [driver-analysis](../prompts/driver-analysis.md)

### Checklists
- [checklist](../checklists/checklist.md)
## Practical Guidance

- Start from the core objective and define the expected outcome before applying the workflow.
- Use the related examples, recipes, and playbooks as the first implementation reference.
- Keep the advice grounded in the surrounding skill context and verify the result against the available evidence.
- Favor practical, maintainable steps over abstract theory when this document is used in real work.

## Example Walkthrough

1. Open the driver's binary in your disassembler (Ghidra/IDA).
2. Locate `DriverEntry` and follow cross-references to initialization routines.
3. Identify `IoCreateDevice` and `IoCreateSymbolicLink` call sites and note error paths.
4. Map major function table assignments and trace IRP handlers.
5. Verify `DriverUnload` presence and ensure cleanup for created symbolic links and devices.

### WinDbg quick checks

- `lmv m <drivername>` — confirm base and size.
- `u <DriverEntry>` — disassemble the entry routine.
- `dt nt!_DRIVER_OBJECT` — inspect driver object fields if present in memory.

### Validation

- Reproduce initialization steps under controlled environment (VM) and ensure device creation succeeds.
- Confirm no stale symbolic links remain after unload.
