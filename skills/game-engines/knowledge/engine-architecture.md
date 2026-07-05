# Game Engine Architecture

## Overview

Modern native game engines comprise systems for rendering, physics, input, audio, scripting, and asset management. The engine orchestrates these systems in a deterministic loop that updates game state and renders frames.

## Core systems

- Rendering pipeline: command submission, shaders, framebuffers, and swap chains.
- Physics and collision detection: rigid bodies, kinematics, and simulation steps.
- Input handling: polling devices, event queues, and input mapping.
- Asset management: streaming textures, meshes, sounds, and configuration data.
- Scene graph or entity-component system: hierarchical scene updates and object transforms.

## Runtime flow

A typical game engine follows:
1. initialize platform and graphics context
2. load assets and game data
3. enter the main loop
4. process input and update simulation
5. render the frame and present output
6. repeat until exit

## Engine modules

Game execution often splits into modules:
- executable or launcher
- core engine DLL
- game logic module
- renderer and graphics backend
- physics and audio modules
- scripting or runtime VM module

## Notes

- Game engines may use custom loaders for plugins, mod support, or anti-cheat integration.
- Discern engine ownership from game logic by module naming and import patterns.

## References

- Game engine architecture articles
- Native engine reverse engineering guides

## Related Material

### Knowledge
- [asset-pipelines](asset-pipelines.md)
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

