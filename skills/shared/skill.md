---
name: shared
version: 1.0
priority: core
requires: []
tags: [shared, common]
description: Common documentation, templates, and standards shared across the knowledge library.
---

# Shared Skill

Common documentation and guidelines shared across skills.

## What this skill provides
- Centralized guidelines, templates, and shared artifacts used by other skills.

## Prerequisites
- None (core support skill)

## Used by
- All other skills as a source of common documentation, templates, and standards.

## Related Skills
- `analysis-engine` — for reasoning templates
- `reverse-engineering` — for RE-specific templates

## Entry Conditions
- Any workflow that requires consistent documentation, templates, or shared rules.

## Exit Conditions
- When a consuming skill has applied the shared templates and recorded provenance.

## Typical Workflow
1. Consumer requests a template or guideline.
2. Shared skill provides the canonical template and formatting rules.
3. Consumer records usage and links the applied template in its `skill.md`.

## Related Artifacts
- Patterns: [patterns](../patterns/)
- Recipes: [recipes](../recipes/)
- Playbooks: [playbooks](../playbooks/)
- Examples: [examples](../examples/)
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
