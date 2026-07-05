# Capture Dump Recipe

## Purpose
Collect a reliable crash or hang dump for later post-mortem analysis.

## Prerequisites
- Target process or system in a consistent failed state.
- Debugger capable of capturing user or kernel dumps.
- Knowledge of crash type and desired dump detail level.

## Inputs
- live process handle or kernel debugger connection.
- dump type (`mini`, `full`, `heap`, `triage`).
- symbol path and module mapping.

## Steps
1. Identify the target process or system event.
2. Choose the appropriate dump type for the problem.
3. Use WinDbg, Task Manager, or `procdump` to create the dump.
4. Verify the dump contains process memory, threads, and module list.
5. Save the dump with original metadata and symbol path notes.

## Verification
- Confirm the dump opens in the debugger.
- Check the loaded modules and symbol status.
- Ensure the faulting thread and exception record are present.

## Notes
- For hangs, prefer full user-mode dumps with thread and handle data.
- For kernel crashes, collect a complete memory dump when possible.

## References
- Microsoft dump collection guidance
- Sysinternals Procdump documentation

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

