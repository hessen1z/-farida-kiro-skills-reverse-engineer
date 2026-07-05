Agent Loader

Purpose: Define the loader behavior for agents consuming this skill library.

Order of operations
1. Read `SYSTEM.md` — the canonical constitution for the library.
2. Load `meta/skills.json` and `meta/dependencies.json` to build the dependency graph.
3. Consult `skill-priority.md` and `skill-selection.md` to choose an initial skill subset.
4. Load required skill `skill.md` files in dependency order.

Failure handling
- If a skill file is missing, log and skip non-critical skills; abort if a core skill is missing.

Notes
- Loader must avoid loading domain knowledge before reading `SYSTEM.md`.
