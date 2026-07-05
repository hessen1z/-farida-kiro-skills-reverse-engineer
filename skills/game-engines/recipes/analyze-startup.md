# Analyze Startup Recipe

## Purpose
Analyze the startup sequence of a game executable or engine module to identify initialization order, asset loading, and plugin registration.

## Prerequisites
- The game binary and module set.
- A debugger or disassembler to inspect the entry point and initialization routines.
- Knowledge of engine version or build type when available.

## Inputs
- module load order and dependencies.
- entry point and TLS callback information.
- initialization functions and startup timing.

## Steps
1. Identify the process entry point and loader initialization steps.
2. Inspect TLS callbacks and early initialization routines.
3. Trace engine module initialization and plugin registration.
4. Identify asset loading functions and resource file paths.
5. Document key startup timing and subsystem initialization order.

## Verification
- Confirm module initialization matches observed startup behavior.
- Validate asset paths and loader callbacks with actual game files.
- Identify any deferred loaders or dynamic module resolution.

## Notes
- Many engines use virtual file systems or packed asset containers.
- Launchers may inject or patch engine modules during startup.

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
- [identify-engine](identify-engine.md)
- [trace-input](trace-input.md)

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

