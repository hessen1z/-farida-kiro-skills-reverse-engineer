---
title: Security Playbook
skill: debugging
category: playbooks
difficulty: intermediate
tags: [pe, kernel, debug]
updated: 2026-07-05
---
# Security Playbook

## Objective
Use debugging to analyze security issues such as exploitation, anti-debug protections, and unauthorized behavior.

## Steps
1. Attach a debugger or instrument the binary with dynamic tracing.
2. Observe runtime checks, encryption/decryption, or integrity validation.
3. Identify anti-debug and anti-tamper mechanisms.
4. Trace security-related control flow and memory protections.
5. Document the exploit surface and runtime protections.

## Common Scenarios
- Anti-debug detection through API calls or timing checks.
- Runtime code integrity validation.
- Unauthorized privilege escalation paths.

## Best Practices
- Use isolated environments to avoid affecting production systems.
- Preserve evidence of protection checks and bypass logic.
- Combine debugger observation with static analysis.

## Notes
- Security debugging often requires kernel or hardware-assisted tracing.
- Observe both user-mode and system-mode interactions.

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
- [Performance](Performance.md)

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

