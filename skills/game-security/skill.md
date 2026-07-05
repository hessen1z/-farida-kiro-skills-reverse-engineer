---
name: Game Security
version: 1.0
priority: critical
requires:
  - shared
  - reverse-engineering
  - debugging
  - windows-internals
  - assembly
tags:
  - game
  - security
  - anti-debug
  - protection
description: Core game security skill covering anti-cheat, anti-debug, client integrity, runtime protections, and secure engine analysis.
---

# Game Security Skill

## Purpose
Provide guidance for analyzing game security mechanisms, anti-debug protections, and runtime integrity controls. This skill focuses on the defensive and offensive aspects of game client security in native Windows environments.

## What this skill provides
- Knowledge of game anti-cheat and anti-debug patterns.
- Workflows for identifying runtime protections and integrity checks.
- Recipes for tracing security-related engine behavior.
- References for secure game client analysis.

## Prerequisites
- `shared` for documentation templates.
- `reverse-engineering` for binary and runtime recovery.
- `debugging` for crash, hang, and anti-debug inspection.
- `windows-internals` for OS-level protection behavior.
- `assembly` for low-level pattern recognition.

## Used by
- `anti-cheat`
- `reverse-engineering`
- `game-engines`

## Related Skills
- `debugging` — analyze anti-debug and crash behavior.
- `game-engines` — map security features to engine subsystems.
- `reverse-engineering` — recover protection logic and control flow.

## Entry Conditions
- A game client has anti-debug, anti-tamper, or cheat detection behavior.
- Runtime integrity or protection mechanisms require analysis.
- External modules or drivers are present for security enforcement.

## Exit Conditions
- Core game security protections are identified.
- Anti-debug and anti-cheat behavior are documented.
- Protection bypass or mitigation techniques are outlined for analysis.

## Typical Workflow
1. Identify security-related modules and entry points.
2. Analyze anti-debug and runtime integrity checks.
3. Trace protection behavior during initialization and gameplay.
4. Evaluate whether protections affect debugging or analysis.
5. Document security findings and verification steps.

## Notes
- Treat security analysis as a specialized subdomain of binary and debugging work.
- Do not make assumptions about anti-cheat behavior without evidence.

## Related Material

- Knowledge: [anti-cheat](knowledge/anti-cheat.md)
- Patterns: [anti-debug](patterns/anti-debug.md)
- Recipes: [analyze-tamper](recipes/analyze-tamper.md)
- Playbooks: [ClientSecurity](playbooks/ClientSecurity.md)
- Examples: [anti-debug-analysis](examples/anti-debug-analysis.md)
- References: [references](references/references.md)
- Rules: [security-principles](rules/security-principles.md)
- Prompts: [security-analysis](prompts/security-analysis.md)
- Checklists: [checklist](checklists/checklist.md)

