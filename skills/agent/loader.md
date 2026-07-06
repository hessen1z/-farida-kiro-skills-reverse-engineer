---
title: Agent Loader
skill: agent
category: 
difficulty: intermediate
tags: [pe, loader, gui]
updated: 2026-07-05
---
# Agent Loader

## Purpose
The loader is the entry point that makes the repository usable to an agent or tooling workflow. It determines which skills to load, in what order, and how to respond when required metadata or dependencies are missing.

## Responsibilities
- Read the repository constitution from [SYSTEM.md](../SYSTEM.md).
- Load skill metadata from [meta](../meta) so the available capabilities are visible to the agent.
- Apply the selection rules from [skill-selection.md](../skill-selection.md) and [skill-priority.md](../skill-priority.md).
- Resolve dependencies before loading any skill-specific content.

## Required Workflow
1. Read [SYSTEM.md](../SYSTEM.md) first so the agent works from the repository’s operating rules.
2. Load the metadata files under [meta](../meta) to build a view of available skills and dependencies.
3. Choose a small initial skill set using the selection heuristics in [skill-selection.md](../skill-selection.md).
4. Load the selected skill manifests in dependency order.
5. If a required skill is unavailable, fail gracefully for critical dependencies and skip only non-critical ones.

## Failure Handling
- Missing core skills should stop the workflow because the agent cannot safely operate without them.
- Missing optional or support skills should only reduce capability, not block the primary task.
- Any load failure should be reported with the missing skill name and the dependency path that caused it.

## Practical Guidance
- Prefer a minimal initial load. Overloading the context with too many skills makes reasoning less reliable.
- Re-evaluate the skill set if the task changes from analysis to authoring, verification, or output packaging.
- Keep the loader deterministic so the same inputs produce the same initial skill set.

## Related Guidance
- See [planner.md](planner.md) for plan construction after the loader resolves the initial skills.
- See [router.md](router.md) for how tasks are dispatched once the skill set is known.
- See [validator.md](validator.md) for how outputs are checked after execution.
