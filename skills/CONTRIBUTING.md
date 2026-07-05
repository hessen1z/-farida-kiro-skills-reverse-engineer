# Contributing to AI Security Library

## Overview
This document describes how to contribute safely to the repository, with a focus on maintaining the clean separation between domain skills, shared infrastructure, tooling, and release artifacts.

## Repository Structure
- `skills/` contains domain skill folders.
- `shared/`, `content-template/`, `templates/`, `patterns/`, `playbooks/`, `snippets/`, and `tools/` are shared infrastructure and support resources.
- `Release v1.0/` is the release artifacts folder and must remain outside `skills/`.

## Contribution Workflow
1. Open an issue describing the change.
2. Create a branch for the feature or fix.
3. Implement the change in the appropriate location.
4. Ensure documentation updates are limited to root-level repository organization or shared infrastructure, unless the issue explicitly targets a skill.
5. Submit a pull request with a concise description and links to any affected files.

## Adding New Skills
- Only add a new top-level folder under `skills/` if it represents domain-specific knowledge.
- Each new skill must include `skill.md` and supporting content.
- Do not add pure infrastructure folders as new skills.

## Documentation and Standards
- Use `content-template/` to scaffold new content.
- Follow `writing-guidelines/README.md` for style, terminology, and formatting.
- Keep skill metadata consistent with the existing repository pattern.

## Review and Validation
- Verify that any new or modified skill includes `skill.md` and appropriate subfolders.
- Confirm that release artifacts remain outside `skills/`.
- Check that shared infrastructure is not incorrectly treated as a skill.
- Ensure root documentation is updated when repository organization changes.

## Release Artifacts
- All release packages, validation reports, and archive files belong in `Release v1.0/` at the repository root level, not inside `skills/`.

## Communication
- When in doubt, discuss the proposed change before implementing it.
- Preserve the repository's architecture and avoid broad structural changes unless the proposal is clearly beneficial and low risk.