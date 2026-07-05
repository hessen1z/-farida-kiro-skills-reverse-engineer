# Playbook: Analyze Figma Design

## Purpose
Translate a Figma-based UI design into a structured Dear ImGui implementation plan.

## Steps
1. Review the design system, component library, and spacing rules.
2. Extract typography, color tokens, button styles, card styles, and icon conventions.
3. Identify reusable components and state variations.
4. Map each design section to ImGui widgets or custom draw commands.
5. Produce a build plan with style tokens and implementation notes.

## Output
A design-to-code plan that identifies:
- reusable components
- style tokens
- layout strategy
- implementation complexity
- any custom graphics requirements

## Checklist
- design system tokens are captured
- components are mapped to implementation units
- missing UX details are flagged
- the plan can support incremental implementation

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
- [analyze-ui-screenshot](analyze-ui-screenshot.md)
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
