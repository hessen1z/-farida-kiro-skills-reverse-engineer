# Asset Loading Playbook

## Objective
Diagnose asset loading failures, streaming issues, and resource pipeline bottlenecks in game engines.

## Steps
1. Identify the asset loader and file formats used by the engine.
2. Trace loader calls from the asset manager to the file system.
3. Inspect resource initialization and runtime registration.
4. Check for missing or corrupted asset containers.
5. Validate streaming, caching, and memory usage.

## Common Scenarios
- missing textures or models due to incorrect paths.
- slow streaming from disk or decompression bottlenecks.
- asset loader failures caused by container mismatch.

## Best Practices
- Record loader parameters and file paths.
- Compare actual asset formats to expected engine formats.
- Use function hooks to monitor asset requests.

## Notes
- Some engines use compressed or encrypted asset packages.
- Asset loading may occur in background threads or streaming systems.

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
- [InputAndRendering](InputAndRendering.md)

### Examples
- [engine-discovery](../examples/engine-discovery.md)
- [plugin-discovery](../examples/plugin-discovery.md)

### References
- [references](../references/references.md)

### Prompts
- [engine-analysis](../prompts/engine-analysis.md)

### Checklists
- [checklist](../checklists/checklist.md)

