# Game Loop Pattern

## Pattern Name
Main game loop

## Problem
Identify the central execution loop that drives rendering, input processing, and simulation updates.

## Context
Game engines typically run a tight loop to maintain frame timing and update game state.

## Recognition
- repeated calls to platform wait/poll APIs
- frame timing or delta time calculations
- rendering submission and swap chain presentation
- input polling and update function calls

## Evidence
- a single top-level function that iterates continuously
- repeated module calls across frames
- thread structures pinned to GPU or rendering cores

## Resolution / Action
- inspect the loop body for critical systems and hooks
- identify subsystem update order
- locate frame pacing or render target management

## Examples
- `while (!quit) { update(); render(); present(); }`

## Notes
- Some engines use separate threads for rendering and simulation.
- Frame rate limiting and vsync checks often appear near the loop.

## Related Material

### Knowledge
- [asset-pipelines](../knowledge/asset-pipelines.md)
- [engine-architecture](../knowledge/engine-architecture.md)
- [input-systems](../knowledge/input-systems.md)

### Patterns
- [asset-loader](asset-loader.md)
- [plugin-system](plugin-system.md)
- [rendering-loop](rendering-loop.md)

### Recipes
- [analyze-startup](../recipes/analyze-startup.md)
- [identify-engine](../recipes/identify-engine.md)
- [trace-input](../recipes/trace-input.md)

### Playbooks
- [AssetLoading](../playbooks/AssetLoading.md)
- [InputAndRendering](../playbooks/InputAndRendering.md)

### Examples
- [engine-discovery](../examples/engine-discovery.md)
- [plugin-discovery](../examples/plugin-discovery.md)

### References
- [references](../references/references.md)

### Prompts
- [engine-analysis](../prompts/engine-analysis.md)

### Checklists
- [checklist](../checklists/checklist.md)

