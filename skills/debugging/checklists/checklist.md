# Debugging Checklist

## Preparation
- [ ] Identify target binary and whether it is user-mode or kernel-mode.
- [ ] Confirm symbols and debugger configuration.
- [ ] Capture crash dumps, hang dumps, or live trace data.

## Diagnostics
- [ ] Run automated analysis (`!analyze -v`, `!analyze -v` in kernel mode).
- [ ] Enumerate loaded modules and symbol status.
- [ ] Recover the call stack and inspect the faulting instruction.
- [ ] Verify exception handlers and SEH chain.
- [ ] Inspect thread states, locks, and wait objects.

## Validation
- [ ] Confirm the root cause module or code path.
- [ ] Validate reproducibility and environment factors.
- [ ] Document the debugging steps and evidence.
- [ ] Preserve memory images and dumps for later review.

## Security
- [ ] Check for anti-debugging or anti-tamper behavior.
- [ ] Avoid altering corrupted state when preserving evidence.
- [ ] Keep debugging environment isolated from production.

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

