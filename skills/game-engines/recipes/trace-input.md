# Trace Input Recipe

## Purpose
Trace input processing in a game engine to understand how user input is captured, transformed, and consumed by game logic.

## Prerequisites
- Game binary or engine module.
- Debugger or disassembler with function tracing.
- Knowledge of input APIs used by the target engine.

## Inputs
- known input device APIs and controller support.
- module imports and input mapping functions.

## Steps
1. Identify raw input acquisition functions and device polling.
2. Trace input events to action mapping or command queues.
3. Confirm how input state is forwarded to the game update loop.
4. Inspect any dead zone, filtering, or smoothing logic.
5. Validate against observed input behavior.

## Verification
- Confirm input events map consistently to game actions.
- Identify sources of latency or missed input.
- Document the input pipeline and any custom device handling.

## Notes
- Some engines convert raw input to normalized virtual controls.
- Input processing may be split across multiple threads or systems.

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
- [analyze-startup](analyze-startup.md)
- [identify-engine](identify-engine.md)

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

