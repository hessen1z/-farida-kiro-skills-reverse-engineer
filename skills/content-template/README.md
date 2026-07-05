# Content Template Skill

This directory defines reusable Markdown templates for the repository. Use these templates whenever you create new skill artifacts to ensure consistent structure and review readiness.

Directories:
- `skill-template.md` — skill metadata and structure template
- `knowledge/` — knowledge article templates
- `patterns/` — pattern documentation templates
- `recipes/` — repeatable procedure templates
- `playbooks/` — scenario workflow templates
- `examples/` — runnable example templates
- `references/` — reference and source templates
- `rules/` — rule documentation templates
- `checklists/` — checklist templates
- `prompts/` — prompt templates

How to use
1. Copy the appropriate template for the file type.
2. Replace placeholder headings and content with topic-specific information.
3. Keep section names intact unless the topic requires a small, justified deviation.
4. Apply `writing-guidelines/skill.md` rules for tone, clarity, and review readiness.

Repository integration
- `meta/skills.json` includes `content-template` as an authoring support skill.
- `meta/dependencies.json` records that `content-template` depends on `shared`.
- `skill-selection.md` recommends loading `content-template` with authoring tasks.
