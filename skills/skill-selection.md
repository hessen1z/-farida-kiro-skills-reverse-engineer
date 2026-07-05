# Skill Selection

Purpose: Teach the AI how to decide which skills to load for a given task. Provide explicit examples and simple heuristics.

Selection rules
1. Identify the primary objective (recover, triage, reproduce, instrument).
2. Map objective to capabilities (which skill provides the needed outputs).
3. Load `analysis-engine` for any task requiring hypothesis generation or verification.
4. Load `shared` for templates and documentation.
5. Load `content-template` and `writing-guidelines` when authoring or reviewing repository content.
6. Load minimal domain skills required to perform evidence collection and verification.
7. Avoid loading unrelated expert skills to reduce noise; prefer minimal necessary skill set.

Examples
- Task: Recover RTTI
  - Load: `analysis-engine`, `assembly`, `cpp`, `windows-internals`, `reverse-engineering`

- Task: Pattern Scan
  - Load: `assembly`, `cpp`, `reverse-engineering`

- Task: Analyze PE
  - Load: `windows-internals`, `reverse-engineering`, `analysis-engine`

- Task: Analyze suspicious executable
  - Load: `malware-analysis`, `binary-analysis`, `windows-internals`, `analysis-engine`

- Task: Design defensive detections
  - Load: `detection-engineering`, `malware-analysis`, `windows-security`, `analysis-engine`

- Task: Reconstruct or build a desktop UI with Dear ImGui
  - Load: `gui-engineering`, `cpp`, `windows-internals`, `analysis-engine`

Heuristics
- If the task requires executable-level interpretation, include `assembly` and `cpp`.
- If the task requires system/environment constraints, include `windows-internals`.
- Always include `analysis-engine` for non-trivial decisions and `shared` for output formatting.

Operational note
- Skill selection should produce a compact set of skills (3–6) that together cover data collection, reasoning, and output generation.
