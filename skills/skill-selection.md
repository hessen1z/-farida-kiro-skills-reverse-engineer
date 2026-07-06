---
title: Skill Selection
skill: root
category: 
difficulty: advanced
tags: [pe, windows, malware, imgui, gui]
updated: 2026-07-05
---
# Skill Selection

## Purpose
This document describes how to choose an effective skill set for a task, how to route work across the repository, and how to load multiple skills without overcomplicating the context.

## Selection Workflow
1. Identify the primary objective: recover, triage, reproduce, instrument, document, design, or review.
2. Choose the smallest skill set that can support the objective reliably.
3. Load [analysis-engine](analysis-engine/skill.md) whenever the task requires reasoning, evidence framing, or verification.
4. Load [shared](shared/skill.md) whenever the task requires repository conventions, output structure, or formatting expectations.
5. Add domain skills only when the task requires them.
6. Add support skills such as [examples](examples/skill.md), [recipes](recipes/skill.md), or [playbooks](playbooks/skill.md) when the output needs to be packaged or reused.

## Routing Logic
- If the task is primarily analytical, start with [analysis-engine](analysis-engine/skill.md), [shared](shared/skill.md), and the relevant domain skill.
- If the task is documentation-heavy, add [content-template](content-template/skill.md) and [writing-guidelines](writing-guidelines/skill.md).
- If the task involves binaries or recovered structures, include [assembly](assembly/skill.md), [cpp](cpp/skill.md), and [reverse-engineering](reverse-engineering/skill.md).
- If the task involves suspicious binaries, include [binary-analysis](binary-analysis/skill.md) and [malware-analysis](malware-analysis/skill.md).
- If the task is aimed at security detection, include [detection-engineering](detection-engineering/skill.md) and [windows-security](windows-security/skill.md).

## Practical Scenarios
### Recover RTTI
Load: [analysis-engine](analysis-engine/skill.md), [assembly](assembly/skill.md), [cpp](cpp/skill.md), [windows-internals](windows-internals/skill.md), [reverse-engineering](reverse-engineering/skill.md)

### Pattern Scan
Load: [assembly](assembly/skill.md), [cpp](cpp/skill.md), [reverse-engineering](reverse-engineering/skill.md)

### Analyze PE Structure
Load: [windows-internals](windows-internals/skill.md), [reverse-engineering](reverse-engineering/skill.md), [analysis-engine](analysis-engine/skill.md)

### Analyze a Suspicious Executable
Load: [binary-analysis](binary-analysis/skill.md), [malware-analysis](malware-analysis/skill.md), [windows-internals](windows-internals/skill.md), [analysis-engine](analysis-engine/skill.md)

### Design Defensive Detections
Load: [detection-engineering](detection-engineering/skill.md), [malware-analysis](malware-analysis/skill.md), [windows-security](windows-security/skill.md), [analysis-engine](analysis-engine/skill.md)

### Reconstruct a Desktop UI with Dear ImGui
Load: [gui-engineering](gui-engineering/skill.md), [cpp](cpp/skill.md), [windows-internals](windows-internals/skill.md), [analysis-engine](analysis-engine/skill.md)

## Multi-Skill Loading Strategy
- Use 3–6 skills for most tasks.
- Load the reasoning core first, then the domain skill, then support skills if needed.
- Avoid loading expert skills unless the objective clearly requires them.

## Related Guidance
- See [skill-map.md](skill-map.md) for the overall dependency graph.
- See [skill-priority.md](skill-priority.md) for the priority categories.
- See [SYSTEM.md](SYSTEM.md) for repository-wide operating rules.
