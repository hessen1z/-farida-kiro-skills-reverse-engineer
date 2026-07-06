---
title: Skill Map
skill: root
category: 
difficulty: intermediate
tags: [pe, windows, anti-cheat, malware, gui, kernel]
updated: 2026-07-05
---
# Skill Map

## Purpose
This document describes the repository’s skill dependency graph, the intended execution flow, and the practical routing patterns used by autonomous agents.

## Skill Layers
The library is organized in layers so that agents can begin with reasoning and evidence framing before moving into specialized domain work.

### Foundation Layer
- [analysis-engine](analysis-engine/skill.md) — reasoning, hypothesis generation, evidence scoring, and verification planning.
- [shared](shared/skill.md) — repository conventions, templates, and documentation standards.
- [content-template](content-template/skill.md) — scaffolding for new documentation artifacts.
- [writing-guidelines](writing-guidelines/skill.md) — style, editorial quality, and review expectations.

### Domain Layer
- [windows-internals](windows-internals/skill.md) — OS, kernel, and subsystem context.
- [assembly](assembly/skill.md) and [cpp](cpp/skill.md) — low-level and source-level interpretation.
- [reverse-engineering](reverse-engineering/skill.md) — binary recovery, structure reconstruction, and behavioral analysis.
- [binary-analysis](binary-analysis/skill.md) — binary triage and static analysis workflows.
- [malware-analysis](malware-analysis/skill.md) — suspicious binary triage and behavior interpretation.
- [detection-engineering](detection-engineering/skill.md) — telemetry and detection-oriented workflow design.
- [windows-security](windows-security/skill.md) and [anti-cheat](anti-cheat/skill.md) — defense and enforcement-oriented context.
- [game-engines](game-engines/skill.md) and [game-security](game-security/skill.md) — engine-specific analysis and protection review.

### Support Layer
- [examples](examples/skill.md) — runnable demonstrations and concrete implementations.
- [recipes](recipes/skill.md) — repeatable step-by-step procedures.
- [playbooks](playbooks/skill.md) — scenario-driven workflows and operating procedures.
- [references](references/skill.md) — curated external material and supporting references.

## Dependency Graph
The main dependency relationships are:
- [analysis-engine](analysis-engine/skill.md) → independent reasoning core
- [shared](shared/skill.md) → foundational repository conventions
- [content-template](content-template/skill.md) → depends on [shared](shared/skill.md)
- [writing-guidelines](writing-guidelines/skill.md) → depends on [shared](shared/skill.md) and [content-template](content-template/skill.md)
- [assembly](assembly/skill.md) → depends on [windows-internals](windows-internals/skill.md)
- [cpp](cpp/skill.md) → depends on [assembly](assembly/skill.md) and [shared](shared/skill.md)
- [reverse-engineering](reverse-engineering/skill.md) → depends on [assembly](assembly/skill.md), [cpp](cpp/skill.md), [windows-internals](windows-internals/skill.md), [analysis-engine](analysis-engine/skill.md), and [shared](shared/skill.md)
- [malware-analysis](malware-analysis/skill.md) → depends on [binary-analysis](binary-analysis/skill.md), [reverse-engineering](reverse-engineering/skill.md), [windows-internals](windows-internals/skill.md), [analysis-engine](analysis-engine/skill.md), and [shared](shared/skill.md)
- [detection-engineering](detection-engineering/skill.md) → depends on [malware-analysis](malware-analysis/skill.md), [windows-security](windows-security/skill.md), [analysis-engine](analysis-engine/skill.md), and [shared](shared/skill.md)

## Execution Flow
1. Start with [analysis-engine](analysis-engine/skill.md) to frame the objective and define evidence expectations.
2. Load [shared](shared/skill.md) and the relevant authoring templates when the task involves documentation or review.
3. Add domain skills such as [windows-internals](windows-internals/skill.md), [assembly](assembly/skill.md), [cpp](cpp/skill.md), or [reverse-engineering](reverse-engineering/skill.md) according to the target artifact.
4. Use [examples](examples/skill.md), [recipes](recipes/skill.md), and [playbooks](playbooks/skill.md) to package and verify the work.

## Orchestration Examples
### Crash Triage
- [analysis-engine](analysis-engine/skill.md) → frame failure hypotheses
- [windows-internals](windows-internals/skill.md) → identify OS and subsystem constraints
- [reverse-engineering](reverse-engineering/skill.md) → inspect the target artifact and locate the failure path

### Binary Recovery
- [analysis-engine](analysis-engine/skill.md) → define evidence and verification steps
- [assembly](assembly/skill.md) and [cpp](cpp/skill.md) → interpret implementation details
- [reverse-engineering](reverse-engineering/skill.md) → recover structures and runtime behavior

### Detection Design
- [analysis-engine](analysis-engine/skill.md) → transform observations into testable hypotheses
- [detection-engineering](detection-engineering/skill.md) and [windows-security](windows-security/skill.md) → map behavior to detection logic

## Practical Routing Guidance
- Keep the initial skill set compact and evidence-driven.
- Add support skills only when packaging, reuse, or documentation quality requires them.
- Prefer a root-cause-first workflow over broad, undirected analysis.

## Related Guidance
- Use [skill-priority.md](skill-priority.md) to decide which skills should be loaded first.
- Use [skill-selection.md](skill-selection.md) to choose the right skill set for a task.
- Use [SYSTEM.md](SYSTEM.md) for repository-wide operating rules.
