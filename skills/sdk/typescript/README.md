---
title: TypeScript SDK Loader
skill: sdk
category: typescript
difficulty: intermediate
tags: [pe, loader, gui]
updated: 2026-07-05
---
# TypeScript SDK Loader

## Purpose
This folder provides an npm-style scaffold for reading repository metadata from [meta](../../meta) and exposing simple library-loading helpers for skill and pattern discovery.

## Scope
- Read the repository JSON indexes under [meta](../../meta).
- Expose lightweight helpers such as `Library.load(skillName)` and `Library.findPattern(name)`.
- Remain compatible with a simple documentation-first repository layout.

## Practical Guidance
- Use this scaffold as a lightweight interface layer for tooling or documentation-driven automation.
- Keep the API simple and predictable so it is easy to embed in scripts or tests.
- Expand it only when a real integration need emerges.

## Related Material
- See [sdk/python/loader.py](../python/loader.py) for a Python implementation.
- See [sdk/cpp/README.md](../cpp/README.md) for the C++ version.
