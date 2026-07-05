---
name: gui-engineering
version: 1.0
priority: high
requires:
  - shared
  - analysis-engine
  - cpp
  - windows-internals
  - reverse-engineering
tags:
  - gui
  - imgui
  - ui
  - desktop
  - rendering
description: Production-quality GUI engineering skill focused on Dear ImGui, reusable widgets, desktop UI architecture, rendering quality, and modern application interfaces.
---

# GUI Engineering Skill

## Purpose
Teach the AI how to build professional desktop interfaces using Dear ImGui and related rendering technologies. The skill focuses on reusable widgets, clean architecture, rendering quality, maintainability, and pixel-accurate reproduction of modern desktop applications from screenshots, Figma designs, Photoshop mockups, and existing Windows software.

## Scope
This skill covers:
- Dear ImGui architecture and rendering pipeline
- DrawList-based custom rendering
- reusable widget libraries and UI architecture
- DPI scaling, themes, styling, colors, icons, and layout systems
- docking, multi-viewport, tables, property grids, overlays, notifications, and modern panels
- screenshot, Figma, and desktop-app reverse engineering workflows for UI reconstruction
- performance, rendering optimization, and production-quality C++ organization

## What this skill provides
- a structured reference for building polished desktop UIs with Dear ImGui
- practical guidance for extracting layouts from screenshots and design files
- reusable patterns, recipes, playbooks, examples, and checklists for professional UI engineering
- production-oriented guidance for reverse engineering tools, launchers, dashboards, and desktop utilities

## Prerequisites
- `shared` — documentation and templates
- `analysis-engine` — structured reasoning and review
- `cpp` — production C++ implementation
- `windows-internals` — Windows-specific UI and rendering behavior
- `reverse-engineering` — UI reconstruction workflows from existing software

## Used by
- desktop tooling and reverse engineering workflows
- anti-cheat and game tool UI development
- launcher, dashboard, and analytics tooling
- UI quality review and component reuse planning

## Related Skills
- `graphics-programming` — broader rendering concepts
- `directx-11` — backend integration
- `directx-12` — high-performance backend integration
- `rendering` — rendering architecture independent of API
- `ui-ux-engineering` — UX principles and design systems

## Entry Conditions
- A desktop UI, tool window, dashboard, launcher, or interface needs to be designed or reconstructed.
- A screenshot, Figma design, or existing software UI needs to be translated into Dear ImGui.

## Exit Conditions
- The interface implementation is documented with architecture, widget strategy, rendering plan, and quality checks.

## Related Material

- Knowledge: [dpi-and-theming](knowledge/dpi-and-theming.md)
- Patterns: [widget-library-pattern](patterns/widget-library-pattern.md)
- Recipes: [clone-professional-ui](recipes/clone-professional-ui.md)
- Playbooks: [analyze-desktop-application](playbooks/analyze-desktop-application.md)
- Examples: [imgui-dashboard-example](examples/imgui-dashboard-example.md)
- References: [dear-imgui-resources](references/dear-imgui-resources.md)
- Rules: [ui-quality-rules](rules/ui-quality-rules.md)
- Prompts: [ui-reconstruction-prompt](prompts/ui-reconstruction-prompt.md)
- Checklists: [ui-quality-checklist](checklists/ui-quality-checklist.md)

