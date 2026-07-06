---
title: Game Analysis Checklist
skill: checklists
category: 
difficulty: intermediate
tags: [pe, gui, dll]
updated: 2026-07-05
---
# Game Analysis Checklist

## Purpose
Use this checklist for game-focused reverse engineering and SDK reconstruction tasks where the objective is to understand gameplay systems, engine structures, or runtime behavior.

## Core Workflow
- [ ] Identify the module base and the primary executable or module of interest.
- [ ] Review the PE structure and relevant metadata.
- [ ] Recover RTTI, vtables, and classes to reconstruct the object model.
- [ ] Recover globals and important strings that expose engine or gameplay state.
- [ ] Locate the player, camera, and rendering-related systems.
- [ ] Perform pattern scanning where relevant to discover signatures or structures.
- [ ] Build or refine the SDK scaffolding for the recovered interfaces.
- [ ] Verify the findings against runtime or static evidence.
- [ ] Export the results in a form that is suitable for handoff or later review.

## Practical Guidance
- Keep the checklist focused on the highest-value recovery steps first.
- Cross-check findings against the surrounding engine or game-specific knowledge rather than treating them in isolation.

## Related Guidance
- See [binary.md](binary.md) for general binary triage.
- See [dll.md](dll.md) for module-oriented analysis.
