---
title: Widget Library Pattern
skill: gui-engineering
category: patterns
difficulty: intermediate
tags: [pe, windows, imgui, gui]
updated: 2026-07-05
---
# Widget Library Pattern

## Intent
Create a reusable widget system for complex desktop interfaces. The goal is to capture repeated UI structures once and reuse them across multiple windows and panels.

## Pattern Structure
- define a small component interface for each widget
- pass styling and data through a shared context
- keep rendering code inside the widget implementation
- expose clear parameters for size, state, and interaction

## Typical Components
- panels
- cards
- tables
- toolbars
- property editors
- status indicators
- notifications
- command buttons

## Quality Bar
A widget library should support:
- consistent theme application
- simple integration into new windows
- predictable layout behavior
- low-maintenance styling changes

## Anti-Patterns
- embedding domain-specific code directly into window code
- scattering style constants across many files
- duplicating similar controls for each feature

## Related Material

### Knowledge
- [dpi-and-theming](../knowledge/dpi-and-theming.md)
- [drawlist](../knowledge/drawlist.md)
- [imgui-architecture](../knowledge/imgui-architecture.md)

### Recipes
- [clone-professional-ui](../recipes/clone-professional-ui.md)
- [convert-figma-to-dear-imgui](../recipes/convert-figma-to-dear-imgui.md)
- [dear-imgui-ui-reconstruction](../recipes/dear-imgui-ui-reconstruction.md)

### Playbooks
- [analyze-desktop-application](../playbooks/analyze-desktop-application.md)
- [analyze-figma-design](../playbooks/analyze-figma-design.md)
- [analyze-ui-screenshot](../playbooks/analyze-ui-screenshot.md)

### Examples
- [imgui-dashboard-example](../examples/imgui-dashboard-example.md)

### References
- [dear-imgui-resources](../references/dear-imgui-resources.md)

### Rules
- [ui-quality-rules](../rules/ui-quality-rules.md)

### Prompts
- [ui-reconstruction-prompt](../prompts/ui-reconstruction-prompt.md)

### Checklists
- [ui-quality-checklist](../checklists/ui-quality-checklist.md)

