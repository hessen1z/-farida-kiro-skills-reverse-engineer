---
title: Client Security Playbook
skill: game-security
category: playbooks
difficulty: intermediate
tags: [pe, anti-cheat, driver, kernel, debug]
updated: 2026-07-05
---
# Client Security Playbook

## Objective
Analyze game client security posture, focusing on anti-cheat, anti-debug, and tamper protection components.

## Steps
1. Enumerate game client modules and identify security components.
2. Inspect anti-debug and anti-tamper detection logic.
3. Trace external driver or service interactions.
4. Evaluate whether protections are passive detection or active enforcement.
5. Document the overall attack surface and protection boundaries.

## Common Scenarios
- client-side anti-cheat checks running in game processes
- kernel-mode drivers monitoring process and memory state
- tamper checks on executable pages and asset containers

## Best Practices
- Avoid modifying protected memory before capturing evidence.
- Use minimal instrumentation to avoid protection escalation.
- Document all protection triggers and bypass conditions.

## Notes
- Security analysis may reveal both legitimate protections and false positives.
- Treat anti-cheat as part of the broader game security model.

## Related Material

### Knowledge
- [anti-cheat](../knowledge/anti-cheat.md)

### Patterns
- [anti-debug](../patterns/anti-debug.md)
- [tamper-check](../patterns/tamper-check.md)

### Recipes
- [analyze-tamper](../recipes/analyze-tamper.md)
- [trace-anti-debug](../recipes/trace-anti-debug.md)

### Playbooks
- [DriverSecurity](DriverSecurity.md)

### Examples
- [anti-debug-analysis](../examples/anti-debug-analysis.md)

### References
- [references](../references/references.md)

### Rules
- [security-principles](../rules/security-principles.md)

### Prompts
- [security-analysis](../prompts/security-analysis.md)

### Checklists
- [checklist](../checklists/checklist.md)

