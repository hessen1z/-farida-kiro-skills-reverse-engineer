# Analyze Anti-Cheat Driver Recipe

## Purpose
Analyze a kernel-mode anti-cheat driver to understand its enforcement and monitoring behavior.

## Prerequisites
- Driver binary and symbols.
- Kernel debugger or static analysis tool.
- Access to the corresponding user-mode anti-cheat client.

## Inputs
- driver entry point and dispatch routines.
- callback registration and device interfaces.
- process and memory monitoring logic.

## Steps
1. Identify the driver load path and device name.
2. Inspect `DriverEntry` and dispatch table initialization.
3. Trace process and thread callback registration.
4. Examine memory inspection and hook detection routines.
5. Document enforcement responses and user-mode communication.

## Verification
- Confirm the driver monitors relevant game processes.
- Validate whether the driver blocks or reports suspicious activity.
- Match kernel and user-mode components.

## Notes
- Use kernel debugging carefully on live systems.
- Preserve driver symbols and original driver files.

## References
- Windows kernel debugging documentation
- Anti-cheat driver analysis guides

## Related Material

### Knowledge
- [architecture](../knowledge/architecture.md)

### Patterns
- [driver-enforcement](../patterns/driver-enforcement.md)
- [hook-detection](../patterns/hook-detection.md)
- [memory-scan](../patterns/memory-scan.md)

### Recipes
- [analyze-user-mode](analyze-user-mode.md)

### Playbooks
- [DetectionAndEnforcement](../playbooks/DetectionAndEnforcement.md)

### Examples
- [driver-analysis](../examples/driver-analysis.md)
- [user-mode-analysis](../examples/user-mode-analysis.md)

### References
- [references](../references/references.md)

### Rules
- [anti-cheat-principles](../rules/anti-cheat-principles.md)

### Prompts
- [anti-cheat-analysis](../prompts/anti-cheat-analysis.md)

### Checklists
- [checklist](../checklists/checklist.md)

