---
name: Content Template
version: 1.0
priority: high
requires:
  - shared
tags:
  - template
  - documentation
  - standard
description: Reusable Markdown scaffolds and content templates for skills, knowledge articles, patterns, recipes, playbooks, examples, references, rules, checklists, and prompts.
---

# Content Template Skill

Purpose: Provide canonical reusable templates and structure guidelines for all repository document types.

## What this skill provides
- Standardized templates for new content artifacts.
- A single source of truth for document structure and section naming.
- Consistent writing structure across skills, patterns, recipes, playbooks, examples, references, rules, checklists, and prompts.

## Prerequisites
- `shared` (repository-wide documentation and conventions)

## Used by
- `writing-guidelines`
- `reverse-engineering`
- `binary-analysis`
- Any skill author creating new documentation artifacts.

## Related Skills
- `writing-guidelines` — editorial rules for how templates should be used.
- `shared` — common documentation conventions and style.

## Entry Conditions
- When a new document type is first created.
- When existing content needs to be refactored to match repository conventions.

## Exit Conditions
- Document structure is aligned with the repository’s canonical templates.
- New content is easy to review, reuse, and maintain.

## Typical Workflow
1. Choose the template for the document type.
2. Copy the template into the new file.
3. Adapt the example headings and supporting text to the topic you are documenting.
4. Validate the finished document against writing guidelines and repository style.

## Templates Included
- `skill-template.md`
- `knowledge/knowledge-template.md`
- `patterns/pattern-template.md`
- `recipes/recipe-template.md`
- `playbooks/playbook-template.md`
- `examples/example-template.md`
- `references/reference-template.md`
- `rules/rule-template.md`
- `checklists/checklist-template.md`
- `prompts/prompt-template.md`

## Related Material

- Knowledge: [knowledge-template](knowledge/knowledge-template.md)
- Patterns: [pattern-template](patterns/pattern-template.md)
- Recipes: [recipe-template](recipes/recipe-template.md)
- Playbooks: [playbook-template](playbooks/playbook-template.md)
- Examples: [example-template](examples/example-template.md)
- References: [reference-template](references/reference-template.md)
- Rules: [rule-template](rules/rule-template.md)
- Prompts: [prompt-template](prompts/prompt-template.md)
- Checklists: [checklist-template](checklists/checklist-template.md)
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
