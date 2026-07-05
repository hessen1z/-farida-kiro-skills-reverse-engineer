---
name: Assembly Skill
version: 1.0
priority: medium
requires:
	- windows
tags:
	- assembly
	- calling-conventions
	- registers
description: Low-level assembly knowledge and calling convention reference for Windows.
---

# Assembly Skill

Reference material for assembly idioms, calling conventions, and register usage on Windows.

## What this skill provides
- Low-level instruction semantics, calling convention references, and patterns useful for analysis.

## Prerequisites
- `windows-internals`, `shared`

## Used by
- `reverse-engineering`, `cpp`, `examples`

## Related Skills
- `cpp`, `reverse-engineering`, `analysis-engine`

## Entry Conditions
- When interpreting disassembly, constructing signatures, or mapping calling behavior.

## Exit Conditions
- When an instruction-level interpretation or pattern match has been recorded and linked to higher-level hypotheses.

## Typical Workflow
1. Normalize disassembly snippets.
2. Match idioms against curated patterns.
3. Emit annotated observations for hypothesis generation.
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
