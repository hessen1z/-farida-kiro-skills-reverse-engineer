---
title: Playbook: Build Widget Library
skill: gui-engineering
category: playbooks
difficulty: intermediate
tags: [pe, windows, imgui, gui]
updated: 2026-07-05
---
# Playbook: Build Widget Library

## Purpose
Create a reusable set of UI widgets for a desktop application or tool suite.

## Steps
1. Identify recurring interface elements and shared behaviors.
2. Define a small component API for each widget.
3. Implement the widget in a reusable module or namespace.
4. Apply the shared theme system and style tokens.
5. Validate the widgets across different windows and states.

## Output
A maintainable widget library that reduces duplication and improves consistency across the UI.

## Related Material

### Knowledge
- [dpi-and-theming](../knowledge/dpi-and-theming.md)
- [drawlist](../knowledge/drawlist.md)
- [imgui-architecture](../knowledge/imgui-architecture.md)

### Patterns
- [widget-library-pattern](../patterns/widget-library-pattern.md)

### Recipes
- [clone-professional-ui](../recipes/clone-professional-ui.md)
- [convert-figma-to-dear-imgui](../recipes/convert-figma-to-dear-imgui.md)
- [dear-imgui-ui-reconstruction](../recipes/dear-imgui-ui-reconstruction.md)

### Playbooks
- [analyze-desktop-application](analyze-desktop-application.md)
- [analyze-figma-design](analyze-figma-design.md)
- [analyze-ui-screenshot](analyze-ui-screenshot.md)

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
## Practical Guidance

- Start from the concrete objective and define the expected outcome before applying the workflow.
- Use the related examples, recipes, playbooks, and references as the first implementation reference.
- Keep the guidance grounded in the surrounding skill context and verify the result with available evidence.
- Favor practical, maintainable steps over abstract theory when the document is used in real work.
## Verification Checklist

- Confirm that the main objective is clear and the workflow is actionable.
- Ensure the document points to the most relevant examples, recipes, or playbooks.
- Validate that the terminology is consistent with the rest of the skill.
- Check that the practical guidance is specific enough to be used without further interpretation.
