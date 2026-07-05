Linting Guidelines

Purpose: Define minimal quality checks for new files added to the library.

Checks
- Frontmatter (for `skill.md`) must include `name`, `version`, `priority`, and `requires`.
- Files must include provenance links (for knowledge items) where applicable.
- Code examples must compile or include small test harnesses where feasible.
- No placeholder names in final outputs (see `renaming.md`).

Automation
- Prefer automated tools from `tools/` for checking references and duplicates.
