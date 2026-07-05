# Performance Playbook

## Objective
Debug performance regressions by measuring runtime bottlenecks, thread contention, and resource usage.

## Steps
1. Capture performance data with a profiler or live debugger.
2. Identify hotspots and frequently executed code paths.
3. Examine thread activity and synchronization overhead.
4. Validate whether the regression is CPU, memory, or I/O bound.
5. Trace from the symptom to the offending function.

## Common Scenarios
- Frame rate drops in game loops.
- High CPU usage from busy waits.
- Memory thrashing or cache misses.

## Best Practices
- Use performance counters and timeline views when available.
- Correlate profiler data with debugger snapshots.
- Avoid optimizing without first identifying root cause.

## Notes
- Some slowdowns appear only under specific inputs or configurations.
- Instrumentation should minimize its own overhead.

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
- [Crash](Crash.md)
- [Hang](Hang.md)
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

