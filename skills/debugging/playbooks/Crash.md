# Crash Playbook

## Objective
Guide the debugging workflow for application crashes, from initial triage through root cause identification.

## Steps
1. Collect crash information and crash dumps.
2. Confirm the system and module state at the time of the crash.
3. Load symbols and run automated analysis.
4. Recover the call stack and examine the faulting instruction.
5. Inspect surrounding code, data, and exception handling.
6. Map the crash to a specific module, function, and input state.

## Common Scenarios
- Access violations from invalid pointers.
- Buffer overruns in image or audio decoding loops.
- Race conditions and timing-dependent crashes.

## Best Practices
- Start with the simplest evidence: `!analyze -v`, `k`, `lm`.
- Validate whether the crash is user-mode or kernel-mode.
- Confirm reproducibility on a controlled test case.

## Notes
- Hardware faults or anti-debug methods can mimic crashes.
- Preserve the original crash artifacts for later review.

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
- [analyze-crash](../recipes/analyze-crash.md)
- [analyze-exception](../recipes/analyze-exception.md)
- [analyze-hang](../recipes/analyze-hang.md)

### Playbooks
- [Hang](Hang.md)
- [Performance](Performance.md)
- [Security](Security.md)

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

