---
title: Directory Structure
skill: root
category: 
difficulty: intermediate
tags: [pe, gui]
updated: 2026-07-05
---
# Directory Structure

## Root Layout
- [ARCHITECTURE.md](ARCHITECTURE.md) — describes the repository architecture and content boundaries.
- [README.md](README.md) — entry point and overview for the library.
- [CONTRIBUTING.md](CONTRIBUTING.md) — contribution workflow and review checklist.
- [skill-map.md](skill-map.md), [skill-priority.md](skill-priority.md), and [skill-selection.md](skill-selection.md) — helper documents for skill discovery and loading.
- [SYSTEM.md](SYSTEM.md) — repository-wide system description and capabilities.
- [content-template](content-template) — canonical scaffolds for new content.
- [writing-guidelines](writing-guidelines) — editorial instructions and formatting standards.
- Shared infrastructure folders such as [patterns](patterns), [playbooks](playbooks), [snippets](snippets), [tools](tools), and [meta](meta) — reusable repository assets.

## Skill Folder Structure
Each domain skill folder typically includes:
- skill.md — manifest and metadata.
- knowledge/ — concept and architecture documentation.
- patterns/ — recurring technical signatures and heuristics.
- playbooks/ — operational workflows.
- recipes/ — task-oriented procedures.
- examples/ — walkthroughs and practical demonstrations.
- prompts/ — prompt guidance and review prompts.
- rules/ — governance and security principles.
- checklists/ — validation and audit checklists.
- references/ — supporting citations and resources.

## Infrastructure vs Skills
- Skill folders are domain-focused and contain a skill manifest.
- Infrastructure folders provide shared resources and should not be treated as domain skills.
- Common infrastructure folders include [shared](shared), [content-template](content-template), [templates](templates), [patterns](patterns), [playbooks](playbooks), [snippets](snippets), [tools](tools), [meta](meta), and [writing-guidelines](writing-guidelines).

## Navigation Guide
- Start with [README.md](README.md) for orientation.
- Use [ARCHITECTURE.md](ARCHITECTURE.md) to understand responsibilities and boundaries.
- Use the domain skill folders for topic-specific content.
- Use the shared infrastructure folders when you need reusable templates, guidance, or support resources.

## Maintenance Notes
Keep the separation between domain knowledge and support infrastructure explicit. New top-level skill folders should only be created when they represent a real domain-specific body of knowledge.