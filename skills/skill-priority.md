# Skill Priority

Purpose: Define priority tiers to guide which skills are considered core vs optional in orchestration.

Tiers

Core Skills
- `analysis-engine` — reasoning backbone
- `shared` — templates and standards
- `content-template` — canonical document scaffolds
- `writing-guidelines` — editorial rules and review guidance
- `reverse-engineering` — domain recovery for this repository

Secondary Skills
- `windows-internals` — OS-level constraints and behaviors
- `assembly` — instruction-level interpretation
- `cpp` — source-level mapping and examples
- `malware-analysis` — defensive malware triage and behavior interpretation
- `detection-engineering` — telemetry-driven detection design
- `gui-engineering` — desktop UI architecture, Dear ImGui implementation, and UI reconstruction workflows

Optional Skills
- `examples` — runnable examples and test harnesses
- `recipes` — step-by-step reproducible procedures
- `playbooks` — scenario-driven workflows

Expert Skills
- Tool-specific integrations (IDA, Ghidra, x64dbg) — load only when tool-specific actions are required

Usage guidance
- Prefer Core + 1–2 Secondary skills for most tasks.
- Load Expert skills only when a tool-specific action is required (e.g., script generation for IDA).
- Re-evaluate priorities periodically and keep this file synchronized with `skill-map.md`.
