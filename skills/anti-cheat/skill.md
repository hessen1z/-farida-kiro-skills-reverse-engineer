---
name: Anti-Cheat
version: 1.0
priority: critical
requires:
  - shared
  - reverse-engineering
  - debugging
  - windows-internals
  - game-security
tags:
  - cheat
  - security
  - runtime
description: Core anti-cheat skill covering detection, driver-based enforcement, runtime hooks, and game integrity mechanisms.
---

# Anti-Cheat Skill

## Purpose
Provide a reference skill for analyzing anti-cheat systems in native Windows games, including detection strategies, enforcement drivers, and runtime memory integrity checks.

## What this skill provides
- Knowledge of anti-cheat architecture and enforcement logic.
- Patterns for cheat detection, memory scanning, and runtime hooks.
- Recipes for analyzing anti-cheat drivers and bypass behavior.
- Playbooks for client and kernel enforcement workflows.

## Prerequisites
- `shared` for documentation conventions.
- `reverse-engineering` for pattern recovery and module inspection.
- `debugging` for live analysis and dump recovery.
- `windows-internals` for kernel and process behavior.
- `game-security` for security concepts and protections.

## Used by
- `game-security`
- `game-engines`

## Related Skills
- `debugging` — trace anti-cheat detection and crash behavior.
- `game-security` — connect anti-cheat protections to broader client security.
- `game-engines` — understand anti-cheat integration with engine subsystems.

## Entry Conditions
- A game client uses anti-cheat enforcement or kernel drivers.
- Cheat detection, process validation, or memory protection needs analysis.
- Integrations with launcher or server-side validation are present.

## Exit Conditions
- Anti-cheat enforcement components are identified.
- Detection and bypass points are documented.
- The anti-cheat attack surface is mapped.

## Typical Workflow
1. Enumerate client and driver modules involved in anti-cheat.
2. Identify hook points and integrity checks.
3. Trace enforcement logic and detection criteria.
4. Determine whether anti-cheat is self-contained or externally coordinated.
5. Document the system and its trust boundaries.

## Notes
- Anti-cheat systems frequently blend user-mode and kernel-mode controls.
- Keep analysis evidence-based and avoid speculation.

## Related Material

- Knowledge: [architecture](knowledge/architecture.md)
- Patterns: [driver-enforcement](patterns/driver-enforcement.md)
- Recipes: [analyze-driver](recipes/analyze-driver.md)
- Playbooks: [DetectionAndEnforcement](playbooks/DetectionAndEnforcement.md)
- Examples: [driver-analysis](examples/driver-analysis.md)
- References: [references](references/references.md)
- Rules: [anti-cheat-principles](rules/anti-cheat-principles.md)
- Prompts: [anti-cheat-analysis](prompts/anti-cheat-analysis.md)
- Checklists: [checklist](checklists/checklist.md)

