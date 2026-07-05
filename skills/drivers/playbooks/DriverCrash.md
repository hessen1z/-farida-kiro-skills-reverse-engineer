# Driver Crash Playbook

## Objective
Analyze crashes involving kernel drivers, device objects, or driver initialization failures.

## Steps
1. Load the crash dump or attach a kernel debugger.
2. Identify the crashing driver and bug check code.
3. Inspect the driver call stack and IRP state.
4. Review driver initialization and device creation paths.
5. Evaluate whether synchronization or invalid memory access caused the crash.

## Common Scenarios
- invalid memory access in driver dispatch routines.
- race conditions between driver and kernel objects.
- driver unload or cleanup failures.

## Best Practices
- Verify driver symbols and module load addresses.
- Use `!analyze -v` and `!irp` to inspect driver state.
- Preserve crash dumps for repeatable analysis.

## Notes
- Driver crashes may involve both the driver and the kernel.
- Keep kernel debugging commands minimal to reduce side effects.

## Related Material

### Knowledge
- [driver-model](../knowledge/driver-model.md)

### Patterns
- [irp-flow](../patterns/irp-flow.md)

### Recipes
- [analyze-irp](../recipes/analyze-irp.md)
- [debug-driver](../recipes/debug-driver.md)

### Playbooks
- [DriverLifecycle](DriverLifecycle.md)

### Examples
- [driver-entry](../examples/driver-entry.md)
- [irp-completion](../examples/irp-completion.md)

### References
- [references](../references/references.md)

### Prompts
- [driver-analysis](../prompts/driver-analysis.md)

### Checklists
- [checklist](../checklists/checklist.md)

