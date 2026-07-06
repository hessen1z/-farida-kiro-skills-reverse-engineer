---
title: C++ SDK Loader
skill: sdk
category: cpp
difficulty: intermediate
tags: [pe, loader, gui, elf]
updated: 2026-07-05
---
# C++ SDK Loader

## Purpose
This folder provides a lightweight C++ scaffold for loading repository metadata from [meta](../../meta) and exposing simple helpers for skill discovery and pattern lookup.

## Scope
- Read repository metadata from the JSON indexes under [meta](../../meta).
- Expose a minimal API for locating skills and patterns.
- Keep the implementation self-contained and easy to integrate into tooling.

## Practical Guidance
- Use this scaffold as a starting point for host tools, analysis utilities, or internal automation.
- Keep the API narrow and predictable so it remains easy to reason about.
- Extend it only when there is a clear use case such as richer skill filtering or workflow-specific lookups.

## Related Material
- See [sdk/python/loader.py](../python/loader.py) for a Python equivalent.
- See [sdk/typescript/README.md](../typescript/README.md) for a TypeScript-oriented scaffold.
