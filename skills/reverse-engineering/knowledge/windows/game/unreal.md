---
title: Unreal Engine Notes
skill: reverse-engineering
category: knowledge
difficulty: intermediate
tags: [pe, unreal, gui]
updated: 2026-07-05
---
# Unreal Engine Notes

Guidance for reversing games built on Unreal Engine: locating core globals (`GWorld`, `GNames`), understanding `UObject` layout, and identifying `ProcessEvent` and reflection hooks.

## Key Targets

- `GWorld`, `GNames`, and `GUObjectArray`: central globals for object enumeration.
- `UObject` layout: object header, name index, class pointer — reconstructing this enables high-level object inspection.
- `ProcessEvent`: central dispatch for events; hooking it provides dynamic visibility into gameplay logic.

## Workflow

1. Search for string references and pattern signatures tied to `GNames` and `ProcessEvent`.
2. Use runtime dumps to scan for global pointers and validate offsets.
3. Reconstruct `UObject` layout by inspecting object lists and common field offsets.

## Tools and Techniques

- IDA Pro / Ghidra with UE-specific plugins
- Runtime instrumentation to locate `ProcessEvent` and object lists

## Common Pitfalls

- Different Unreal versions change offsets and object array layouts — verify against the running build.
- Stripped symbols require reliance on patterns and heuristics; validate carefully.

## Verification Checklist

- [ ] Located `GWorld`/`GNames` pointers and validated object enumeration.
- [ ] Confirmed `ProcessEvent` address and signature.

## Related Material

- Knowledge: [source-engine](../game/source-engine.md)
