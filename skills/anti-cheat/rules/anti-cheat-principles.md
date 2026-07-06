---
title: Anti-Cheat Rules
skill: anti-cheat
category: rules
difficulty: intermediate
tags: [pe, anti-cheat, driver, gui, kernel]
updated: 2026-07-05
---
# Anti-Cheat Rules

## Rule 1: Evidence over assumption
Base anti-cheat conclusions on observed runtime and binary evidence.

## Rule 2: Understand enforcement chains
Trace how user-mode and kernel-mode components interact before attacking a bypass.

## Rule 3: Avoid destructive analysis
Preserve original binaries, dumps, and driver state during anti-cheat investigation.

## Rule 4: Separate detection from response
Document detection mechanisms independently from enforcement behavior.

## Rule 5: Respect system stability
Kernel-mode anti-cheat analysis must minimize impact on the host system.

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

### Prompts
- [anti-cheat-analysis](../prompts/anti-cheat-analysis.md)

### Checklists
- [checklist](../checklists/checklist.md)
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
