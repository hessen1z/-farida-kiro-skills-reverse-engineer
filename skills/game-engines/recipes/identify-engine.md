# Identify Engine Recipe

## Purpose
Identify the underlying game engine or runtime used by a native game binary.

## Prerequisites
- Access to the game executable and associated modules.
- Disassembler or static analysis tool.
- Knowledge of common game engine naming conventions and module layouts.

## Inputs
- executable names and module imports.
- embedded strings and version metadata.
- initialization sequences and asset pipeline calls.

## Steps
1. Inspect the executable and modules for known engine signatures.
2. Identify module names that suggest engine components.
3. Look for common engine subsystems: rendering, physics, scripting, sound.
4. Trace initialization order and plugin registration.
5. Compare findings to public engine names or custom runtime patterns.

## Verification
- Confirm the engine type with module and string evidence.
- Validate the initialization sequence with observed behavior.
- Document any custom or mixed-engine components.

## Notes
- Some games combine a custom engine with third-party middleware.
- Engine signatures may be obfuscated or renamed to avoid detection.

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

