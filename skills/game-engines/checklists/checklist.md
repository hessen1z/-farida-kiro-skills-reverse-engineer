---
title: Game Engines Checklist
skill: game-engines
category: checklists
difficulty: intermediate
tags: [pe, loader]
updated: 2026-07-05
---
# Game Engines Checklist

## Preparation
- [ ] Identify the game executable and engine modules.
- [ ] Confirm launch configuration and plugin/loaders.
- [ ] Gather asset paths and resource files.

## Diagnostics
- [ ] Locate main loop and subsystem update order.
- [ ] Enumerate rendering, physics, and input modules.
- [ ] Inspect startup initialization and TLS callbacks.
- [ ] Validate asset loading and resource registration.

## Validation
- [ ] Confirm behavior against engine version and build artifacts.
- [ ] Map engine modules to distinct responsibilities.
- [ ] Document runtime hooks, plugin systems, and custom loaders.

## Notes
- [ ] Keep engine analysis grounded in module boundaries.
- [ ] Watch for late-loaded or injected components.
- [ ] Preserve any evidence of engine-specific load order anomalies.

## Related Material

### Knowledge
- [asset-pipelines](../knowledge/asset-pipelines.md)
- [engine-architecture](../knowledge/engine-architecture.md)
- [input-systems](../knowledge/input-systems.md)

### Patterns
- [asset-loader](../patterns/asset-loader.md)
- [game-loop](../patterns/game-loop.md)
- [plugin-system](../patterns/plugin-system.md)

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

