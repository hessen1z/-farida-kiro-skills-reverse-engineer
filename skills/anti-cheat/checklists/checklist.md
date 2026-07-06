---
title: Anti-Cheat Checklist
skill: anti-cheat
category: checklists
difficulty: intermediate
tags: [pe, anti-cheat, driver, gui, kernel]
updated: 2026-07-05
---
# Anti-Cheat Checklist

## Preparation
- [ ] Identify anti-cheat components in the game client and system.
- [ ] Confirm whether kernel drivers or user-mode modules are present.
- [ ] Collect relevant binaries, symbols, and configuration data.

## Diagnostics
- [ ] Locate memory scanning and hook detection routines.
- [ ] Identify anti-cheat kernel callbacks and device interfaces.
- [ ] Trace detection and enforcement logic.
- [ ] Document the runtime communication paths.

## Validation
- [ ] Confirm detection triggers and enforcement actions.
- [ ] Validate whether bypass conditions affect game behavior.
- [ ] Preserve evidence and avoid modifying protected state.

## Notes
- [ ] Anti-cheat often spans both user-mode and kernel-mode components.
- [ ] Keep analysis evidence-based and avoid assumptions.

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

### Playbooks
- [DetectionAndEnforcement](../playbooks/DetectionAndEnforcement.md)

### Examples
- [driver-analysis](../examples/driver-analysis.md)
- [user-mode-analysis](../examples/user-mode-analysis.md)

### References
- [references](../references/references.md)

### Rules
- [anti-cheat-principles](../rules/anti-cheat-principles.md)

### Prompts
- [anti-cheat-analysis](../prompts/anti-cheat-analysis.md)
## Practical Guidance

- Start from the concrete objective and define the expected outcome before applying the workflow.
- Use the related examples, recipes, playbooks, and references as the first implementation reference.
- Keep the guidance grounded in the surrounding skill context and verify the result with available evidence.
- Favor practical, maintainable steps over abstract theory when the document is used in real work.
## Verification Checklist

- Confirm that the main objective is clear and the workflow is actionable.
- Ensure the document points to the most relevant examples, recipes, or playbooks.
- Validate that the terminology is consistent with the rest of the skill.
- Check that the practical guidance is specific enough to be used without further interpretation.
