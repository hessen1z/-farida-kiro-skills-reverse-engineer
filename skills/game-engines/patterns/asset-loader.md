# Asset Loader Pattern

## Pattern Name
Resource asset loader

## Problem
Identify code paths that load game assets, parse containers, or stream resources at runtime.

## Context
Assets such as textures, models, sounds, and configuration files are typically loaded through a centralized asset manager or loader subsystem.

## Recognition
- file path strings referencing `.pak`, `.res`, `.dds`, `.fbx`, `.wav`
- calls to file I/O APIs like `CreateFile`, `ReadFile`, `MapViewOfFile`
- parsing loops over asset headers or chunked containers
- resource registration functions in engine modules

## Evidence
- runtime functions that open and parse asset packages
- memory allocations tied to resource loading
- repeated use of loader-specific APIs and structures

## Resolution / Action
- trace asset path construction and container parsing
- identify whether assets are decompressed or decrypted
- confirm loader behavior against observed file types

## Notes
- Streaming loaders may use background threads or asynchronous I/O.
- Custom asset containers may hide file extensions or use obfuscation.

## References
- Game resource and asset pipeline analysis

## Related Material

### Knowledge
- [asset-pipelines](../knowledge/asset-pipelines.md)
- [engine-architecture](../knowledge/engine-architecture.md)
- [input-systems](../knowledge/input-systems.md)

### Patterns
- [game-loop](game-loop.md)
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

