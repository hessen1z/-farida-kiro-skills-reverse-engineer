---
title: Playbook: Unity (IL2CPP) Analysis
skill: playbooks
category: 
difficulty: intermediate
tags: [pe, unity]
updated: 2026-07-05
---
# Playbook: Unity (IL2CPP) Analysis

## Objective
Extract metadata and generate a usable SDK for IL2CPP-based Unity games.

## Scope
- Unity builds that use IL2CPP rather than Mono.
- Native game binaries and game data packages.

## Required Skills
- Basic Unity binary analysis.
- IL2CPP metadata extraction and type reconstruction.

## Workflow
1. Locate `global-metadata.dat` and any native images in the game package.
2. Use `Il2CppDumper` or `Il2CppInspector` to extract type and method tables.
3. Apply recovered symbols to the disassembly and rename functions consistently.
4. Reconstruct types and generate headers for runtime instrumentation.
5. Validate the SDK with a minimal harness or runtime inspection.

## Decision Tree
- If metadata is present and parseable, proceed with dump generation.
- If metadata is obfuscated or missing, inspect the native binaries and packaging layout.
- If the SDK fails to load, re-check the exported metadata and symbol mapping.

## Practical Commands
- `Il2CppDumper.exe <game.exe> <output>`
- `Il2CppInspector.exe <metadata>`

## Validation
- [ ] Metadata is parsed correctly and mapped to function pointers.
- [ ] The generated SDK can be used for dynamic testing or instrumentation.

## Common Pitfalls
- Using the wrong metadata package version for the target build.
- Failing to match the exported symbols with the correct binary architecture.

## Evidence Collection
- Capture the metadata dump, exported headers, and any successful runtime validation results.

## Documentation
- Record the target build version, metadata file locations, and any caveats in the generated SDK.

## Related Recipes
- [Build_SDK](../recipes/Build_SDK.md)
- [Recover_Classes](../recipes/Recover_Classes.md)

## Related Patterns
- [virtual-call](../patterns/virtual-call.md)

## References
- Il2CppDumper documentation
- Unity IL2CPP internals references

