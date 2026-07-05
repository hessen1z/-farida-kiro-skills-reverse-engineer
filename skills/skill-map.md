# Skill Map

Purpose: Describe the complete skill ecosystem, dependency graph, execution order, recommended workflows, and common combinations.

Dependency graph (high-level)
- `analysis-engine` (reasoning backbone)
  ↳ `shared` (templates)
    ↳ `content-template` (document scaffolds)
      ↳ `writing-guidelines` (editorial rules)
  ↳ `windows-internals`
    ↳ `assembly`
    ↳ `cpp`
      ↳ `reverse-engineering`
        ↳ `examples`, `recipes`, `documentation`  ↳ `malware-analysis`
    ↳ `detection-engineering`
      ↳ `windows-security`
        ↳ `anti-cheat`
    ↳ `gui-engineering`
      ↳ `ui-ux-engineering`
Execution order (typical)
1. `analysis-engine` — frame reasoning and verification.
2. `shared` — provide templates and formatting.
3. `windows-internals` / `assembly` / `cpp` — supply environment and type-level expectations.
4. `reverse-engineering` — perform domain-specific recovery and produce artifacts.
5. `examples` / `recipes` / `documentation` — verify and package outputs.

Recommended workflow (example)
"I have a crash":
- `analysis-engine` → triage and hypothesis generation
- `windows-internals` → environment constraints and expected behaviors
- `reverse-engineering` → binary analysis and function/class recovery
- `examples` → reproduce, verify
- `recipes` → produce repeatable steps
- `documentation` → finalize report

Common combinations
- Pattern Scan: `assembly` + `cpp` + `reverse-engineering` + `examples`
- RTTI Recovery: `analysis-engine` + `assembly` + `cpp` + `reverse-engineering`
- Crash Triage: `analysis-engine` + `windows-internals` + `reverse-engineering`

Decision matrix (high-level)
- Input: Crash dump → Load `analysis-engine`, `windows-internals`, `reverse-engineering`.
- Input: Stripped binary with no symbols → Load `assembly`, `cpp`, `reverse-engineering`, `analysis-engine`.
- Input: Pattern/signature task → Load `assembly`, `reverse-engineering`, `examples`.

Notes
- This file describes orchestration only. Do not add domain knowledge here; reference the domain skill files for details.

Links
- Use `skill-selection.md` to decide which skills to load for a given task.
- Use `skill-priority.md` to understand core vs optional skills.
