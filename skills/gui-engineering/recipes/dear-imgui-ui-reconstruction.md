# Dear ImGui UI Reconstruction Recipe

## Goal
Convert a screenshot, mockup, wireframe, or existing desktop application UI into a Dear ImGui implementation.

## Inputs
- reference screenshot or design file
- target window purpose
- expected interaction model
- desired styling direction

## Procedure
1. Analyze the reference and identify the main regions: header, content, sidebar, footer, tables, and controls.
2. Extract spacing, font hierarchy, color palette, padding, and component density.
3. Break the UI into reusable widgets and panels.
4. Implement layout skeletons in Dear ImGui with simple placeholder content.
5. Replace placeholders with custom DrawList visuals where necessary.
6. Apply theme tokens and verify consistency across the interface.
7. Review visual quality at different window sizes and DPI settings.

## Output
A reusable and maintainable ImGui-based UI implementation that closely matches the reference while preserving usability and code clarity.

## Notes
Focus on structure first, then visual polish. This tends to yield a more reliable implementation than trying to match every pixel at once.

## Related Material

### Knowledge
- [dpi-and-theming](../knowledge/dpi-and-theming.md)
- [drawlist](../knowledge/drawlist.md)
- [imgui-architecture](../knowledge/imgui-architecture.md)

### Patterns
- [widget-library-pattern](../patterns/widget-library-pattern.md)

### Recipes
- [clone-professional-ui](clone-professional-ui.md)
- [convert-figma-to-dear-imgui](convert-figma-to-dear-imgui.md)
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

- Start from the core objective and define the expected outcome before applying the workflow.
- Use the related examples, recipes, and playbooks as the first implementation reference.
- Keep the advice grounded in the surrounding skill context and verify the result against the available evidence.
- Favor practical, maintainable steps over abstract theory when this document is used in real work.
## Verification Checklist

- Confirm that the main objective is clear and the workflow is actionable.
- Ensure the document points to the most relevant examples, recipes, or playbooks.
- Validate that the terminology is consistent with the rest of the skill.
- Check that the practical guidance is specific enough to be used without further interpretation.
