# Asset Pipelines Knowledge

## Overview

Asset pipelines manage the conversion, packaging, and loading of game resources such as textures, models, animations, and sound. They are critical for performance and runtime consistency.

## Core concepts

- Asset preprocessing: compression, conversion, and metadata generation.
- Package formats: archives, bundles, and virtual file systems.
- Streaming and on-demand resource loading.
- Asset registration and lifetime management.

## Runtime architecture

At runtime, engines typically:
- locate asset bundles or directories
- resolve asset identifiers and file paths
- load and decompress resources into memory
- register assets with rendering, physics, or audio subsystems

## Notes

- Custom asset formats may hide or encrypt resource data.
- Asset loading often happens in background threads to avoid stalls.

## References

- Game asset pipeline design documents
- Native game resource loading analysis

## Related Material

### Knowledge
- [engine-architecture](engine-architecture.md)
- [input-systems](input-systems.md)

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

### Checklists
- [checklist](../checklists/checklist.md)

