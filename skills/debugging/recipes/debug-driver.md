# Debug Driver Recipe

## Purpose
Debug Windows kernel drivers and diagnose driver crashes, hangs, and IRP issues.

## Prerequisites
- Kernel debugger and appropriate target setup.
- Symbol files for the driver and Windows kernel.
- Boot configuration for local or remote kernel debugging.

## Inputs
- driver binary and symbol path.
- crash dump or live kernel connection.
- device and IRP context information.

## Steps
1. Connect the kernel debugger to the target machine.
2. Load symbols for `ntoskrnl.exe` and the driver.
3. Use `!analyze -v` for bug check analysis.
4. Inspect the IRP stack and device objects.
5. Examine driver entry points and dispatch routines.

## Verification
- Confirm the bug check code and crash module.
- Validate driver data structures and synchronization state.
- Reproduce the driver fault in a controlled environment.

## Notes
- Kernel debugging requires careful target isolation.
- Use non-destructive commands when analyzing live systems.

## References
- Windows kernel debugging documentation

## Related Material

### Knowledge
- [anti-debugging](../knowledge/anti-debugging.md)
- [debugging](../knowledge/debugging.md)
- [kernel-debugging](../knowledge/kernel-debugging.md)

### Patterns
- [breakpoint](../patterns/breakpoint.md)
- [exception-handler](../patterns/exception-handler.md)
- [stack-unwind-failure](../patterns/stack-unwind-failure.md)

### Recipes
- [analyze-crash](analyze-crash.md)
- [analyze-exception](analyze-exception.md)
- [analyze-hang](analyze-hang.md)

### Playbooks
- [Crash](../playbooks/Crash.md)
- [Hang](../playbooks/Hang.md)
- [Performance](../playbooks/Performance.md)

### Examples
- [kernel-debugging](../examples/kernel-debugging.md)
- [stack-unwind](../examples/stack-unwind.md)
- [winDbg-crash-analysis](../examples/winDbg-crash-analysis.md)

### References
- [references](../references/references.md)

### Rules
- [debugging-principles](../rules/debugging-principles.md)

### Prompts
- [debug-process](../prompts/debug-process.md)
- [exception-analysis](../prompts/exception-analysis.md)
- [hang-analysis](../prompts/hang-analysis.md)

### Checklists
- [checklist](../checklists/checklist.md)

