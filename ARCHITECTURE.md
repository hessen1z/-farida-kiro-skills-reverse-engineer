# Repository Architecture

## Purpose
This repository is designed to separate domain knowledge from shared infrastructure, tooling, and release outputs.

## Architectural Layers

### Domain Skills
Domain skills are folders under `skills/` that contain a `skill.md` manifest and domain-specific content. Examples:
- `binary-analysis`
- `game-security`
- `malware-analysis`
- `networking`
- `windows-security`

### Shared Infrastructure
Shared infrastructure provides repository-wide templates, guidelines, patterns, and tooling support. It is not a domain skill and should not be loaded as one.
- `shared/`
- `content-template/`
- `templates/`
- `patterns/`
- `playbooks/`
- `snippets/`
- `tools/`
- `meta/`
- `writing-guidelines/`

### Release Artifacts
Release artifacts are stored in `Release v1.0/` at the repository root. This folder contains packaging outputs, validation reports, and release metadata.

## Clean Separation Rules
- Skills must be domain-focused and contain `skill.md`.
- Shared infrastructure may contain templates, patterns, and reusable resources.
- Release artifacts must never appear inside the `skills/` folder.

## Agent Loading
Agents should select skills based on `skill.md` metadata and use the skill selection guidance in `skill-selection.md`, `skill-map.md`, and `skill-priority.md`.

## Folder Classification
- Skill folders: those containing `skill.md`.
- Shared infrastructure: folders with reusable content and templates.
- Release output: `Release v1.0/` outside `skills/`.

## Naming Conventions
- Use lowercase with hyphens for folder names when possible.
- Keep skill folder names short and domain-specific.
- Use explicit naming for support folders: `shared`, `content-template`, `tools`, `meta`, `Release v1.0`.

## Stability and Growth
The repository is intentionally structured to allow domain skills to grow while keeping support content separate. Future additions should preserve this boundary.

## Notes
- `templates/`, `patterns/`, `playbooks/`, and `snippets/` are shared resources and should be treated as repository infrastructure, not as standalone skills.
- `Release v1.0/` is intentionally placed outside `skills/` to reflect its role as release output rather than library content.
