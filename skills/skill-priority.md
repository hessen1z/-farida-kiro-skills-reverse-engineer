---
title: Skill Priority
skill: root
category: 
difficulty: advanced
tags: [pe, windows, anti-cheat, driver, malware, gui, kernel]
updated: 2026-07-05
---
# Skill Priority

## Purpose
This document defines the loading priority for skills so that autonomous agents can begin with the most valuable capabilities first and avoid unnecessary context overhead.

## Priority Categories

### Mandatory Skills
These should be loaded for almost any non-trivial analysis or documentation workflow.
- [analysis-engine](analysis-engine/skill.md) — required for reasoning, evidence framing, and verification.
- [shared](shared/skill.md) — required for repository conventions and formatting expectations.

### Core Skills
These provide the main operational backbone for most tasks.
- [reverse-engineering](reverse-engineering/skill.md) — central domain capability for structural analysis and recovery.
- [windows-internals](windows-internals/skill.md) — provides OS and subsystem context required by many workflows.
- [assembly](assembly/skill.md) and [cpp](cpp/skill.md) — foundational interpretation skills for binary and source-level work.
- [content-template](content-template/skill.md) and [writing-guidelines](writing-guidelines/skill.md) — necessary when producing or reviewing repository content.

### Optional Skills
These add value when the task requires specific context or packaging.
- [binary-analysis](binary-analysis/skill.md) — useful for initial triage and static inspection.
- [malware-analysis](malware-analysis/skill.md) — useful when the target is suspicious or malicious.
- [detection-engineering](detection-engineering/skill.md) — useful for telemetry and detection-oriented work.
- [examples](examples/skill.md), [recipes](recipes/skill.md), [playbooks](playbooks/skill.md), and [references](references/skill.md) — useful for producing reusable output and packaging results.

### Expert Skills
These should be loaded only when a task explicitly requires a specialized path.
- [game-engines](game-engines/skill.md)
- [game-security](game-security/skill.md)
- [gui-engineering](gui-engineering/skill.md)
- [anti-cheat](anti-cheat/skill.md)
- [hypervisor](hypervisor/skill.md)
- [kernel](kernel/skill.md)
- [drivers](drivers/skill.md)

## Recommendations for Autonomous Agents
- Begin with the mandatory and core skills, then add optional skills only when the evidence suggests they are necessary.
- Load expert skills only when the task is clearly within their domain.
- If the task is documentation-heavy, add [content-template](content-template/skill.md) and [writing-guidelines](writing-guidelines/skill.md) early.
- If the task is binary-focused, add [reverse-engineering](reverse-engineering/skill.md), [assembly](assembly/skill.md), and [cpp](cpp/skill.md) before broader support skills.

## Practical Prioritization Examples
- Binary triage: [analysis-engine](analysis-engine/skill.md) + [shared](shared/skill.md) + [windows-internals](windows-internals/skill.md) + [reverse-engineering](reverse-engineering/skill.md)
- RTTI recovery: [analysis-engine](analysis-engine/skill.md) + [assembly](assembly/skill.md) + [cpp](cpp/skill.md) + [reverse-engineering](reverse-engineering/skill.md)
- Detection design: [analysis-engine](analysis-engine/skill.md) + [detection-engineering](detection-engineering/skill.md) + [windows-security](windows-security/skill.md)

## Related Guidance
- See [skill-map.md](skill-map.md) for the overall dependency graph and execution flow.
- See [skill-selection.md](skill-selection.md) for concrete task-based selection patterns.
- See [SYSTEM.md](SYSTEM.md) for the repository-wide operating rules.
