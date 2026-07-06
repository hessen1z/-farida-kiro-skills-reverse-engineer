---
title: Design Detection Pipeline
skill: detection-engineering
category: recipes
difficulty: intermediate
tags: [pe, gui]
updated: 2026-07-05
---
# Design Detection Pipeline

## Goal
Create a defensive detection pipeline that collects telemetry, evaluates logic, and routes actionable alerts.

## Steps
1. Define the detection objective and threat behavior.
2. Select the telemetry source and required context.
3. Design event normalization and enrichment.
4. Implement rule evaluation and correlation logic.
5. Validate the output and tune for false positives.

## Related Material

### Knowledge
- [detection-engineering-fundamentals](../knowledge/detection-engineering-fundamentals.md)
- [telemetry-and-pipelines](../knowledge/telemetry-and-pipelines.md)

### Patterns
- [monitoring-loop](../patterns/monitoring-loop.md)

### Playbooks
- [analyze-detection-pipeline](../playbooks/analyze-detection-pipeline.md)

### References
- [references](../references/references.md)

### Rules
- [style](../rules/style.md)

### Prompts
- [design-prompt](../prompts/design-prompt.md)

### Checklists
- [validation-checklist](../checklists/validation-checklist.md)
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
