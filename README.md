# AI Security Library

## Purpose
This repository is a structured knowledge library for AI-assisted security analysis, reverse engineering, game security, and tooling workflows.

## Architecture
- `skills/` contains domain skills and knowledge modules.
- `Release v1.0/` contains release artifacts and packaging outputs, intentionally located outside `skills/`.
- `shared/`, `content-template/`, `templates/`, `patterns/`, `playbooks/`, `snippets/`, `tools/`, and `meta/` are shared infrastructure or repository support content, not individual domain skills.

## Skill Graph
Skills are defined by folders containing `skill.md` and associated content.
- Core reasoning and validation: `analysis-engine`
- Shared documentation and templates: `shared`, `content-template`, `writing-guidelines`
- Domain skills: `binary-analysis`, `game-security`, `malware-analysis`, `networking`, `windows-security`, etc.

## How Skills Work
Each skill folder typically includes:
- `skill.md` — skill metadata and purpose
- `knowledge/` — domain knowledge articles
- `patterns/` — recurring patterns and detection heuristics
- `playbooks/` — procedural workflows
- `recipes/` — task-specific instructions
- `examples/` — practical examples
- `rules/` — governance or security principles
- `prompts/` — prompt engineering guidance
- `checklists/` — validation and audit checklists
- `references/` — supporting references and citations

## How Agents Load Skills
Agents should load skills by selecting folders with `skill.md` metadata and use `skill-selection.md`, `skill-priority.md`, and `skill-map.md` as guidance.

## Folder Structure
Refer to `DIRECTORY_STRUCTURE.md` for the complete repository layout.

## Versioning
This release is version `1.0`. Release artifacts and validation reports are stored in `Release v1.0/` outside the skills folder.

## Adding New Skills
1. Create a top-level folder under `skills/`.
2. Add `skill.md` with metadata, purpose, and dependencies.
3. Add supporting content in the appropriate subfolders.
4. Use `content-template/` and `writing-guidelines/` to standardize new files.
5. Do not add shared infrastructure as skills.

## Writing Guidelines
Follow `writing-guidelines/README.md` and `content-template/` when authoring new content.

## Contribution Guidelines
See `CONTRIBUTING.md` for the contribution workflow, review expectations, and repository conventions.

## License
This repository includes an official `LICENSE` file at the repository root.

## Roadmap
See `ROADMAP_v1.1.md` for planned future evolution and extension points.
