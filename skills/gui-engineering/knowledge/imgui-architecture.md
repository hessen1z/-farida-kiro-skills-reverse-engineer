# Dear ImGui Architecture

## Overview
Dear ImGui is an immediate-mode GUI library designed for building highly customized desktop interfaces in C++. It is especially suitable for tools, debuggers, launchers, visualizers, reverse engineering utilities, and game-related desktop applications.

## Theory
Unlike retained-mode UI systems, Dear ImGui rebuilds the interface every frame from the current application state. This makes it highly flexible for tools that need fast iteration, custom rendering, and direct control over visual output.

## Internal Architecture
A typical Dear ImGui application contains:
- a frame loop that begins and ends the UI frame
- widget submission through immediate-mode commands
- a DrawList pipeline for custom geometry and rendering
- backend integration for a rendering API such as DirectX 11, DirectX 12, OpenGL, or Vulkan
- a font atlas and texture system for text and icons

## Rendering Flow
1. Start a new frame.
2. Submit widgets and custom draw commands.
3. The library records draw commands into DrawLists.
4. The backend uploads the generated geometry and textures.
5. The frame is rendered to the target surface.

## Memory and Performance Considerations
- prefer reusable widgets over one-off UI code
- build custom rendering with DrawList when fidelity and performance matter
- avoid unnecessary allocations inside the frame loop
- keep state changes deterministic and localized

## Common Mistakes
- relying too heavily on default widgets for custom visuals
- building one-off UI code instead of reusable components
- ignoring font, atlas, and DPI concerns

## Best Practices
- separate layout logic from visual implementation
- use DrawList for custom panels, gradients, shadows, and rounded surfaces
- maintain a consistent theme system for spacing, colors, and typography

## Related Material

### Knowledge
- [dpi-and-theming](dpi-and-theming.md)
- [drawlist](drawlist.md)

### Patterns
- [widget-library-pattern](../patterns/widget-library-pattern.md)

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

