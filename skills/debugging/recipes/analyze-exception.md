# Analyze Exception Recipe

## Purpose
Inspect exception records and handlers to determine how an exception was raised and whether it was handled.

## Prerequisites
- Access to a live process or crash dump.
- Symbol files and module information.
- Debugger with exception inspection support.

## Inputs
- exception code and faulting address.
- thread context and register state.
- exception handler chain or runtime function table.

## Steps
1. Identify the exception code and flags.
2. Determine whether the exception was handled or unhandled.
3. Examine exception handler registration and filters.
4. Inspect the faulting instruction and memory context.
5. Follow the stack to the handler or crash site.

## Verification
- Confirm exception origin and propagation path.
- Verify handler addresses and filter results.
- Check for exception-based obfuscation patterns.

## Notes
- Some legit code uses exceptions for control flow.
- Distinguish between C++ exceptions, SEH, and access violations.

## References
- Microsoft exception handling documentation
- WinDbg exception analysis

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
- [analyze-hang](analyze-hang.md)
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

