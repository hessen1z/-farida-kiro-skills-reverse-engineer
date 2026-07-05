# Playbook: Analyze UI Screenshot

## Purpose
Analyze a screenshot of a desktop UI and plan a Dear ImGui reconstruction.

## Steps
1. Identify the overall layout and structure.
2. Extract major regions such as header, toolbar, content area, sidebar, and footer.
3. Record the visual hierarchy, spacing, and alignment.
4. Determine which parts can be built with standard widgets and which parts require custom DrawList rendering.
5. Produce a reconstruction plan with component breakdown and implementation order.

## Output
A structured UI analysis note with:
- region map
- color and typography assumptions
- widget inventory
- custom rendering plan
- implementation priorities

## Checklist
- the target screenshot is clearly understood
- the component structure is decomposed
- custom visuals are explicitly identified
- the plan is actionable for implementation

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
- [analyze-ui-video](analyze-ui-video.md)

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

