---
title: Detection and Enforcement Playbook
skill: anti-cheat
category: playbooks
difficulty: intermediate
tags: [pe, anti-cheat, driver, kernel]
updated: 2026-07-05
---
# Detection and Enforcement Playbook

## Objective
Analyze how anti-cheat systems detect suspicious activity and enforce protections.

## Steps
1. Identify detection logic and suspicious behavior signatures.
2. Trace data collection, scanning, and validation paths.
3. Determine enforcement actions such as process termination, blocking, or reporting.
4. Correlate detection events with user-mode or kernel-mode components.
5. Document how the system responds to cheat indicators.

## Common Scenarios
- memory scanner finds injected code or modified game memory.
- hook detector discovers inline patches or imported function redirections.
- kernel driver intercepts process or thread creation for monitoring.

## Best Practices
- Separate detection evidence from enforcement effects.
- Avoid altering detection paths during analysis.
- Preserve the original runtime environment for reproducibility.

## Notes
- Some anti-cheat detection is continuous, while enforcement may be periodic.
- Enforcement responses vary from warnings to secure termination.

## Related Material

### Knowledge
- [architecture](../knowledge/architecture.md)

### Patterns
- [driver-enforcement](../patterns/driver-enforcement.md)
- [hook-detection](../patterns/hook-detection.md)
- [memory-scan](../patterns/memory-scan.md)

### Recipes
- [analyze-driver](../recipes/analyze-driver.md)
- [analyze-user-mode](../recipes/analyze-user-mode.md)

### Examples
- [driver-analysis](../examples/driver-analysis.md)
- [user-mode-analysis](../examples/user-mode-analysis.md)

### References
- [references](../references/references.md)

### Rules
- [anti-cheat-principles](../rules/anti-cheat-principles.md)

### Prompts
- [anti-cheat-analysis](../prompts/anti-cheat-analysis.md)

### Checklists
- [checklist](../checklists/checklist.md)

