---
title: verification
skill: analysis-engine
category: 
difficulty: intermediate
tags: [pe, gui]
updated: 2026-07-05
---
Verification Practices

Principles
- Every non-trivial conclusion requires explicit verification steps.
- Verification must be independent where possible and designed to increase or decrease confidence measurably.

Verification strategies
- Replication: reproduce the observation with an independent method or tool.
- Cross-check: use orthogonal evidence sources (e.g., memory read vs. log file).
- Controlled test: perform a minimal experiment designed to elicit expected behavior if hypothesis is true.
- Falsification test: design a test that would clearly contradict the hypothesis if it were false.

Verification workflow
1. For each hypothesis, list available verification methods and required resources.
2. Prioritize methods by expected information gain per unit cost/time.
3. Execute the highest-priority verifications and record results with provenance.
4. Update evidence and confidence; repeat until confidence meets threshold or hypothesis rejected.

Auditability
- Record verification attempts, outcomes, tools, commands, and timestamps.
- When a verification fails, log why it failed (environment, tool error, contradictory evidence).

## Related Material

- Skill overview: [skill.md](skill.md)
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
