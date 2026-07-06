---
title: Recipe: Convert Figma to Dear ImGui
skill: gui-engineering
category: recipes
difficulty: intermediate
tags: [pe, imgui, gui]
updated: 2026-07-05
---
# Recipe: Convert Figma to Dear ImGui

## Goal
Translate a Figma design into an implementation plan and then into a Dear ImGui UI.

## Procedure
1. Extract the component structure, spacing, typography, color tokens, and interaction states.
2. Map Figma components to ImGui widgets or custom draw operations.
3. Implement the base layout first, then refine the styling.
4. Introduce reusable components for repeated patterns.
5. Validate the result against the design and quality checklist.

## Output
A maintainable Dear ImGui implementation aligned to the source design.

## Related Material

### Knowledge
- [dpi-and-theming](../knowledge/dpi-and-theming.md)
- [drawlist](../knowledge/drawlist.md)
- [imgui-architecture](../knowledge/imgui-architecture.md)

### Patterns
- [widget-library-pattern](../patterns/widget-library-pattern.md)

### Recipes
- [clone-professional-ui](clone-professional-ui.md)
- [dear-imgui-ui-reconstruction](dear-imgui-ui-reconstruction.md)
- [recreate-aaa-desktop-tool](recreate-aaa-desktop-tool.md)

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
