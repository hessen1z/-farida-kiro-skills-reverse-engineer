---
title: Reviewer
skill: agent
category: 
difficulty: intermediate
tags: [pe, gui]
updated: 2026-07-05
---
# Reviewer

## Purpose
The reviewer checks whether a plan or completed output is consistent with the repository’s expectations for quality, evidence, and maintainability.

## Responsibilities
- Compare the observed evidence against the expected evidence in the plan.
- Flag discrepancies and propose corrective actions when the evidence is weak or inconsistent.
- Produce an error-analysis report when the workflow fails or produces low-confidence results.
- Review newly added or modified content for clarity, completeness, and consistency with the surrounding repository.

## Review Workflow
1. Accept the plan or output from the planner or executor.
2. Compare the actual results with the expected verification steps.
3. Validate the output with the validator and identify any missing evidence or weak assumptions.
4. Record the review outcome and any follow-up actions for the next iteration.

## Practical Guidance
- Focus the review on correctness, evidence quality, and integration rather than stylistic redesign.
- Prefer specific findings over vague criticism. A good review tells the reader what is wrong, why it matters, and how to correct it.
- If the output cannot be verified, treat it as provisional and call out the missing evidence.

## Related Guidance
- See [validator.md](validator.md) for execution-time validation rules.
- See [planner.md](planner.md) for how the workflow was originally structured.
- See [SYSTEM.md](../SYSTEM.md) for the repository-wide operating principles.
