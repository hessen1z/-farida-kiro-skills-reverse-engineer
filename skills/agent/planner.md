---
title: Planner
skill: agent
category: 
difficulty: intermediate
tags: [pe, loader, gui]
updated: 2026-07-05
---
# Planner

## Purpose
The planner converts a task into a structured sequence of steps that can be executed with the repository’s available skills and evidence policy.

## Planning Workflow
1. Load the relevant workflow metadata from [meta](../meta) to identify appropriate templates.
2. Translate the workflow into skill loads and concrete action items.
3. Estimate the expected information gain and verification cost for each step.
4. Produce a prioritized plan with verification actions, fallback options, and clear completion criteria.

## Output Expectations
A good plan should make the following explicit:
- the objective of the task,
- the skill set required to proceed,
- the evidence that should be collected,
- the verification step for each major decision,
- and any rollback or fallback action if the first approach fails.

## Practical Guidance
- Keep the plan narrow at first. Broad plans are harder to execute and validate.
- Prefer steps that generate evidence early so the agent can refine the approach quickly.
- Make the plan explicit enough that a reviewer can follow the reasoning chain without needing hidden context.

## Related Guidance
- See [loader.md](loader.md) for how the initial skill set is selected.
- See [router.md](router.md) for how the plan is dispatched to the right capabilities.
- See [validator.md](validator.md) for how the plan’s outputs are checked.
