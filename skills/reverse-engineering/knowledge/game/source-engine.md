---
title: Source Engine Notes
skill: reverse-engineering
category: knowledge
difficulty: intermediate
tags: [pe, debug]
updated: 2026-07-05
---
# Source Engine Notes

Notes and practical patterns for reversing games built on Valve's Source engine. Focuses on interface discovery, object layouts, and common engine conventions used by mods and plugins.

## Key Artifacts

- `CreateInterface` exports: search for strings like `CreateInterface("VEngineClient"...)` to locate factory functions that return interface pointers.
- Global pointers and singletons: `g_pEngine`, `g_pClient`, `g_pEntityList` are common naming conventions used by developers.
- VTables and virtual methods: many engine hooks and callbacks are virtual; reconstructing vtables helps locate core systems.

## Typical Workflow

1. Identify modules that expose `CreateInterface` and enumerate available interfaces.
2. Locate references to interface pointers in data sections or global variables.
3. Reconstruct vtables by resolving indirect call sites and cross-referencing with RTTI or exported type names.
4. Use pattern scanning to locate global symbols across builds where symbols are stripped.

## Tools and Techniques

- IDA Pro/Ghidra: use cross-references and virtual function identification plugins.
- Pattern-scan utilities: create signatures for `CreateInterface` string usage and common vtable access patterns.
- Runtime inspection: debug and dump global pointers (`g_p*`) once found to validate offsets.

## Common Pitfalls

- Assuming interface names are consistent across versions; validate against strings and exports.
- Mistaking compiler-generated thunks for meaningful stubs — confirm via cross-references.

## Verification Checklist

- [ ] Discovered `CreateInterface` calls and validated returned pointers.
- [ ] Reconstructed vtables for core interfaces.
- [ ] Validated offsets and function pointers using a running process or test harness.

## Practical Tools & Commands

- Use IDA/Ghidra and pattern-scan utilities to locate `CreateInterface` strings and exported factories.
- Use a running process to dump global pointers (`g_p*`) and verify vtable entries in memory.

## Practical Validation

- Load a minimal plugin or test harness that calls discovered interfaces to confirm correct function pointers and offsets.
- Document any version-specific differences discovered during analysis.

## Related Material

- Recipes: [Find_Offsets.md](../../recipes/Find_Offsets.md)
- Knowledge: [common-instructions](../assembly/common-instructions.md)
