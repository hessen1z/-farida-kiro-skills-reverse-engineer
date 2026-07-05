---
name: Windows Security
version: 1.0
priority: critical
requires:
  - shared
  - windows-internals
  - debugging
  - assembly
  - reverse-engineering
tags:
  - security
  - windows
  - kernel
description: Core Windows security skill covering process protection, code integrity, memory protections, and system hardening analysis.
---

# Windows Security Skill

## Purpose
Provide a comprehensive skill for analyzing Windows security features, process protection, code integrity, and kernel defenses. This skill covers security-relevant OS behavior, mitigation mechanisms, and protected execution environments.

## What this skill provides
- Knowledge of Windows security mitigations and protection systems.
- Patterns for memory, process, and code integrity checks.
- Recipes for analyzing protected processes, secure boot drivers, and exploit mitigations.
- References for Windows security architecture.

## Prerequisites
- `shared` for documentation templates.
- `windows-internals` for OS protection semantics.
- `debugging` for crash and exception analysis.
- `assembly` for low-level detection patterns.
- `reverse-engineering` for analyzing protected binaries.

## Used by
- `kernel`
- `anti-cheat`
- `game-security`

## Related Skills
- `windows-internals` — explains security kernel behavior.
- `debugging` — diagnoses security-related faults.
- `anti-cheat` — overlaps with process integrity and protection.

## Entry Conditions
- A Windows process or kernel component is protected by security mitigations.
- Code integrity or exploit protection needs analysis.
- System hardening features affect debugging or analysis.

## Exit Conditions
- Security mitigations are identified and mapped.
- Protection boundaries and bypass conditions are documented.
- The effect of Windows security features on analysis is understood.

## Typical Workflow
1. Determine applicable Windows mitigations and protection levels.
2. Analyze process, module, and kernel protection behavior.
3. Trace runtime decisions around code integrity and memory protections.
4. Document evidence and verify the security model.

## Notes
- Windows Security includes both built-in mitigations and platform-specific protections.
- Be careful when analyzing features that can trigger system-level restrictions.

## Related Material

- Knowledge: [code-integrity](knowledge/code-integrity.md)
- Patterns: [aslr](patterns/aslr.md)
- Recipes: [analyze-code-integrity](recipes/analyze-code-integrity.md)
- Playbooks: [ExploitMitigations](playbooks/ExploitMitigations.md)
- Examples: [code-integrity](examples/code-integrity.md)
- References: [references](references/references.md)
- Rules: [mitigation-guidelines](rules/mitigation-guidelines.md)
- Prompts: [code-integrity-analysis](prompts/code-integrity-analysis.md)
- Checklists: [checklist](checklists/checklist.md)

