---
name: Game Engines
version: 1.0
priority: critical
requires:
  - shared
  - reverse-engineering
  - windows-internals
  - assembly
tags:
  - game
  - engine
  - rendering
  - physics
  - runtime
description: Core game engine skill covering engine architecture, rendering loops, asset pipelines, input handling, and runtime behavior for game analysis.
---

# Game Engines Skill

## Purpose
Provide a structured skill for analyzing game engine internals, runtime flow, module interaction, and asset/loading behavior. This includes rendering, physics, animation, input, and game engine-specific debugging patterns.

## What this skill provides
- Engine architecture fundamentals for modern native games.
- Knowledge of rendering loops, update systems, and resource pipelines.
- Patterns for game event loops, plugin systems, and engine hooks.
- Recipes for analyzing game startup, asset loading, and runtime state.
- References for game-specific debugging and reverse engineering.

## Prerequisites
- `shared` for documentation and templates.
- `reverse-engineering` for binary and runtime recovery.
- `windows-internals` for OS interaction and memory behavior.
- `assembly` for instruction-level engine analysis.

## Used by
- `game-security`
- `anti-cheat`
- `reverse-engineering`

## Related Skills
- `reverse-engineering` — reconstructs game data structures and control flow.
- `debugging` — traces engine behavior and identifies runtime failures.
- `windows-internals` — explains OS-level engine interactions.

## Entry Conditions
- A game binary or module requires analysis.
- Runtime behavior, crashes, or asset loading issues need investigation.
- Engine-specific hooks, plugins, or rendering loops are present.

## Exit Conditions
- Key engine subsystems are mapped and documented.
- Game loops, input handling, and asset pipelines are identified.
- Engine-specific module interactions and plugin extensions are understood.

## Typical Workflow
1. Identify the game executable and module layout.
2. Map the engine initialization and main loop.
3. Analyze asset loading, rendering, and input dispatch.
4. Recover game-specific data structures and hooks.
5. Validate findings against engine version and build artifacts.

## Notes
- Focus on native engine internals; do not document high-level gameplay mechanics.
- Keep examples practical and tied to observable binary behavior.

## Related Material

- Knowledge: [asset-pipelines](knowledge/asset-pipelines.md)
- Patterns: [asset-loader](patterns/asset-loader.md)
- Recipes: [analyze-startup](recipes/analyze-startup.md)
- Playbooks: [AssetLoading](playbooks/AssetLoading.md)
- Examples: [engine-discovery](examples/engine-discovery.md)
- References: [references](references/references.md)
- Prompts: [engine-analysis](prompts/engine-analysis.md)
- Checklists: [checklist](checklists/checklist.md)

