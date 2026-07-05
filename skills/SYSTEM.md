SYSTEM

Philosophy
- This library is designed to separate domain knowledge from reasoning. Agents should prefer explicit evidence and verification over inference without provenance.

Goals
- Provide a machine-readable index of capabilities, workflows, and patterns.
- Offer a single canonical source of truth (`SYSTEM.md`) for agent orchestration and policies.
- Ensure reproducible, auditable analysis outputs.

Scope
- Includes skills, patterns, recipes, playbooks, examples, and documentation required for reverse-engineering and allied analysis tasks.
- Does NOT include external tool binaries, private data, or unrelated domain knowledge.

Rules
- Always read `SYSTEM.md` before loading any domain skill.
- Record provenance for every evidence item, including file, command, timestamp.
- Do not rename symbols without explicit evidence and a verification plan.

Skill loading order
1. Read `SYSTEM.md` and `meta/skills.json`.
2. Select skills via `skill-selection.md` heuristics.
3. Load core skills (`analysis-engine`, `shared`, `reverse-engineering`) first, then secondary skills.

Reasoning process
- Use `analysis-engine` templates: Observe → Hypothesize → Score Evidence → Verify → Conclude.
- Maintain multiple hypotheses until verification sufficiently discriminates among them.

Evidence policy
- Classify evidence as direct, indirect, or inferred; store provenance for each.
- Prefer independent corroboration before high-confidence claims.
- When evidence conflicts, do not discard; instead, validate both sources and record findings.

Naming policy
- Use semantic, descriptive names. Avoid placeholders in final outputs.
- Record previous names and rationale for changes; include confidence and verification steps.

Verification policy
- Every actionable recommendation must include at least one independent verification step.
- Prioritize verification methods by expected information gain and cost.

Documentation policy
- Reports must include: summary, evidence list, hypotheses considered, verification steps executed, confidence, and next actions.
- Link to `meta/` JSON files where applicable to aid automation.

Reading order for agents
1. `SYSTEM.md`
2. `meta/skills.json` and `meta/dependencies.json`
3. `skill-selection.md` and `skill-priority.md`
4. Specific `skill.md` files for selected skills

Appendix
- `meta/` contains machine-readable indexes for skills, workflows, patterns, and examples.
- `agent/` contains guidance for building loaders, planners, routers, validators, and reviewers.
