---
title: DPI, Scaling, and Theming
skill: gui-engineering
category: knowledge
difficulty: intermediate
tags: [pe, windows, imgui, gui]
updated: 2026-07-05
---
# DPI, Scaling, and Theming

## Overview
Professional desktop UIs need to behave correctly across resolution and scaling changes. Dear ImGui implementations should treat theming, font scaling, and layout constraints as first-class concerns.

## Key Ideas
- use theme tokens for colors, spacing, radii, and font sizes
- support high-DPI layouts by computing sizes from the current display scale
- avoid hardcoded pixel values where a responsive layout is more appropriate
- test interfaces at multiple scaling factors and window sizes

## Practical Guidance
- derive font sizes from a base scale rather than fixed constants
- keep padding and spacing consistent through a shared style layer
- validate component layout after resizing and restoring windows

## Common Problems
- controls become cramped on high-DPI displays
- rounded surfaces look inconsistent across resolutions
- fonts appear too small or misaligned after scaling changes

## Related Material

### Knowledge
- [drawlist](drawlist.md)
- [imgui-architecture](imgui-architecture.md)

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

## Tools & Commands

- Test with multiple DPI settings using Windows Display settings or command-line tools to simulate scaling factors.
- Use automated screenshot diffs to detect layout regressions across scales.

## Validation Checklist

- Confirm fonts and layouts remain readable at high and low DPI settings.
- Verify that theme tokens produce consistent results across components.

## Example Workflow

1. Load the UI and set display scaling to common factors (100%, 125%, 150%, 200%).
2. Capture screenshots and compare against baseline for layout regressions.

