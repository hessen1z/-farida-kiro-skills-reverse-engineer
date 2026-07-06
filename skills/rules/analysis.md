---
title: Analysis Rules
skill: rules
category: 
difficulty: intermediate
tags: [pe, gui]
updated: 2026-07-05
---
# Analysis Rules

## Purpose
These rules define the order in which the repository expects analysts to recover structural information from a binary or module.

## Core Sequence
1. Recover RTTI first so that the object model and type relationships are visible.
2. Recover vtables second to understand the virtual dispatch structure.
3. Recover classes third to reconstruct the higher-level object layout.
4. Rename symbols later, once the recovered structure has been verified.

## Practical Guidance
- Follow this sequence when the target is a compiled binary or a reconstructed object model.
- Do not rename symbols prematurely if the surrounding structure is still uncertain.
- Use the recovered structure to guide later documentation and verification steps.

## Related Guidance
- See [style.md](style.md) for naming and clarity expectations.
- See [documentation.md](documentation.md) for how recovered findings should be recorded.
