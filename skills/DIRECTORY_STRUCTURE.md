# Directory Structure

## Root Layout
- `Release v1.0/` — release artifacts, package outputs, validation reports, and release metadata.
- `skills/` — domain skills and associated knowledge modules.
- `shared/` — shared documentation, templates, and common guidance.
- `content-template/` — canonical content scaffolds for new skill artifacts.
- `templates/` — reusable repository templates and script examples.
- `patterns/` — shared pattern descriptions used across skills.
- `playbooks/` — shared procedural workflows and operational playbooks.
- `snippets/` — reusable code or platform snippets.
- `tools/` — support tooling and audit prompts.
- `meta/` — repository metadata, schemas, and agent-related utilities.
- `writing-guidelines/` — editorial and authoring guidelines.
- `skill-map.md` — skill dependency and workflow relationships.
- `skill-priority.md` — skill categorization and loading priority.
- `skill-selection.md` — skill selection guidance for agents.
- `SYSTEM.md` — repository-wide system description and capabilities.

## `skills/` Folder
Each skill folder is domain-specific and typically includes:
- `skill.md`
- `knowledge/`
- `patterns/`
- `playbooks/`
- `recipes/`
- `examples/`
- `prompts/`
- `rules/`
- `checklists/`
- `references/`

## Infrastructure vs Skills
- Skills are folders with `skill.md` and domain-specific content.
- Shared infrastructure folders provide reusable resources and do not represent standalone domain skills.
- The following folders are shared infrastructure, not skill folders:
  - `shared/`
  - `content-template/`
  - `templates/`
  - `patterns/`
  - `playbooks/`
  - `snippets/`
  - `tools/`
  - `meta/`
  - `writing-guidelines/`

## Release Artifacts
- `Release v1.0/` is outside `skills/` and stores packaged release outputs, validation reports, and documentation for the v1.0 release.

## Adding New Content
- Add new domain knowledge under `skills/` only.
- Add new shared templates or support resources under the appropriate infrastructure folder.
- Do not add new release artifacts inside `skills/`.

## Consistency Notes
- Keep the separation between domain knowledge and infrastructure explicit.
- Use the root `README.md` and `ARCHITECTURE.md` documents as the single source of truth for repository organization.
- Avoid creating new top-level skill folders for shared templates or support assets.