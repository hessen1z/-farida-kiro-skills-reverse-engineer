---
title: common-failures
skill: analysis-engine
category: 
difficulty: intermediate
tags: [pe, gui]
updated: 2026-07-05
---
Common Failures in Analysis

List of common reasoning failures, with causes and mitigations.

1. Jumping to conclusions
- Cause: overreliance on single strong-looking evidence.
- Mitigation: require at least one independent verification for high-impact claims.

2. Ignoring contradictory evidence
- Cause: confirmation bias.
- Mitigation: routinely search for evidence against the preferred hypothesis and document it.

3. Overfitting
- Cause: matching noise to a detailed hypothesis.
- Mitigation: prefer simple hypotheses; validate with held-out observations.

4. Pattern hallucination
- Cause: applying heuristic patterns beyond their valid domain.
- Mitigation: require verification for heuristic matches; track false-positive rates.

5. Confirmation bias
- Cause: sampling evidence selectively.
- Mitigation: predefine evidence collection plan and follow it before ranking hypotheses.

6. Tunnel vision
- Cause: focusing on one line of inquiry to exclusion.
- Mitigation: maintain at least two alternative hypotheses during early stages.

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
