---
title: renaming
skill: analysis-engine
category: 
difficulty: intermediate
tags: [pe, gui]
updated: 2026-07-05
---
Semantic Renaming Guidelines

Purpose: Provide rules for naming recovered symbols and data to maximize clarity and minimize error.

Principles
- Never use opaque placeholders such as `sub_xxxxx`, `func1`, `var1`, `temp` in final names.
- Infer intent before naming: prefer `PlayerController_Update` over `sub_14001` when evidence supports the mapping.

Required process before renaming
1. Gather evidence linking symbol to behavior (strings, RTTI, references, calling patterns).
2. List positive evidence and any uncertainties.
3. Propose name with rationale and confidence score.
4. Provide a verification action that would falsify the name if incorrect.

Naming conventions
- Use descriptive, camel-case or snake_case consistent across the repository.
- Include suffixes for ambiguity, e.g., `Maybe_Player_GetHealth_60pct` if confidence is low.

Rollback and history
- Always record previous names and rationale for changes in documentation and commit messages.
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
