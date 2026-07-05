# Plugin System Pattern

## Pattern Name
Engine plugin or module extension

## Problem
Identify dynamic modules or plugin registration systems used by game engines.

## Context
Many engines support plugin DLLs or script-based extensions loaded at runtime.

## Recognition
- custom module loading and registration callbacks
- plugin directories and extension discovery logic
- exported functions for initialization or registration

## Evidence
- runtime calls to `LoadLibrary` or custom loader functions
- data structures that store module handles and callback tables
- strings referencing plugin folders or module lists

## Resolution / Action
- trace plugin discovery and initialization flow
- identify hooks or patches inserted by plugins
- determine whether plugins run in the engine or game logic context

## Notes
- Plugins may be loaded early or lazily during runtime.
- Security-sensitive game engines may validate plugin signatures.

## References
- Game engine plugin architecture

## Related Material

### Knowledge
- [asset-pipelines](../knowledge/asset-pipelines.md)
- [engine-architecture](../knowledge/engine-architecture.md)
- [input-systems](../knowledge/input-systems.md)

### Patterns
- [asset-loader](asset-loader.md)
- [game-loop](game-loop.md)
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

