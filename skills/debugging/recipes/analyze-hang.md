# Analyze Hang Recipe

## Purpose
Identify the cause of a hang by examining thread states, synchronization waits, and resource contention.

## Prerequisites
- Hang dump or live process attachment.
- Knowledge of expected application behavior.
- Debugger or profiler with thread inspection.

## Inputs
- list of threads and their states.
- synchronization objects and wait chains.
- relevant module and I/O activity.

## Steps
1. Attach to the hung process or load the hang dump.
2. Enumerate all threads and note those that are blocked.
3. Inspect each blocked thread's stack trace.
4. Identify waiting objects and ownership relationships.
5. Correlate thread states with known application logic.

## Verification
- Confirm the hang occurs consistently in the same code path.
- Validate that thread waits are not transient or idle-related.
- Reproduce the hang with reduced instrumentation.

## Notes
- Hangs can be due to deadlocks, infinite loops, or blocked I/O.
- Use timelines or repeated snapshots for intermittent hangs.

## References
- WinDbg thread and synchronization debugging

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
- [capture-dump](capture-dump.md)

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

