---
title: Hang Playbook
skill: debugging
category: playbooks
difficulty: intermediate
tags: [pe, kernel, debug]
updated: 2026-07-05
---
# Hang Playbook

## Objective
Analyze application or system hangs by locating blocked threads and understanding synchronization failures.

## Steps
1. Capture a hang dump or attach to the live process.
2. Enumerate threads and their wait states.
3. Identify locks, waits, or spinning loops.
4. Inspect thread call stacks and synchronization objects.
5. Check for blocked I/O, IPC, or deadlock conditions.

## Common Scenarios
- Thread pool exhaustion.
- Resource contention in rendering or physics loops.
- Blocking waits on network or file I/O.

## Best Practices
- Use thread-aware debugging commands to avoid misleading single-thread snapshots.
- Look for repeated stack patterns in stuck threads.
- Compare hang state to normal execution paths.

## Notes
- Hangs often involve a combination of blocked threads and scheduler pressure.
- External timeouts or watchdogs can provide additional clues.

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

