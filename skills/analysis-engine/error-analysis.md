---
title: error-analysis
skill: analysis-engine
category: 
difficulty: intermediate
tags: [pe, gui]
updated: 2026-07-05
---
Error Analysis and Postmortem

Purpose: Systematically review mistakes and improve future reasoning.

Process
1. Describe the incorrect conclusion and its context.
2. List evidence that was missed or misinterpreted.
3. Identify root cause: data quality, model bias, flawed heuristics, or process error.
4. Propose corrective actions: additional checks, tooling improvements, or updated patterns.
5. Track whether corrective actions were implemented and their effectiveness.

Metrics
- Time to detect error
- Number of downstream tasks affected
- Severity and cost of incorrect action

Reporting
- Each postmortem must include a concise action item list with owners and deadlines.
## Practical Guidance

- Start from the core objective and define the expected outcome before applying the workflow.
- Use the related examples, recipes, and playbooks as the first implementation reference.
- Keep the advice grounded in the surrounding skill context and verify the result against the available evidence.
- Favor practical, maintainable steps over abstract theory when this document is used in real work.

## Related Material

- Skill overview: [skill.md](skill.md)
## Verification Checklist

- Confirm that the main objective is clear and the workflow is actionable.
- Ensure the document points to the most relevant examples, recipes, or playbooks.
- Validate that the terminology is consistent with the rest of the skill.
- Check that the practical guidance is specific enough to be used without further interpretation.
