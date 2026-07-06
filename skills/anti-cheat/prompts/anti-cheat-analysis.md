---
title: Anti-Cheat Analysis Prompt
skill: anti-cheat
category: prompts
difficulty: advanced
tags: [pe, anti-cheat, driver, gui, kernel]
updated: 2026-07-05
---
# Anti-Cheat Analysis Prompt

## Prompt

You are an anti-cheat analysis expert. Given an anti-cheat client or driver, identify detection mechanisms, enforcement behavior, and runtime hooks. Recommend analysis steps to trace security decisions and validate the anti-cheat architecture.

## Guidance

- Focus on detection triggers and enforcement responses.
- Identify kernel-mode and user-mode anti-cheat components.
- Highlight memory scanning and hook detection patterns.
- Provide validation steps for anti-cheat findings.

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

### Checklists
- [checklist](../checklists/checklist.md)
## Practical Guidance

- Start from the core objective and define the expected outcome before applying the workflow.
- Use the related examples, recipes, and playbooks as the first implementation reference.
- Keep the advice grounded in the surrounding skill context and verify the result against the available evidence.
- Favor practical, maintainable steps over abstract theory when this document is used in real work.
## Verification Checklist

- Confirm that the main objective is clear and the workflow is actionable.
- Ensure the document points to the most relevant examples, recipes, or playbooks.
- Validate that the terminology is consistent with the rest of the skill.
- Check that the practical guidance is specific enough to be used without further interpretation.
