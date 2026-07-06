---
title: Router
skill: agent
category: 
difficulty: intermediate
tags: [pe, loader, gui]
updated: 2026-07-05
---
# Router

## Purpose
The router decides how tasks should be distributed across the available skills so that each step is handled by the most relevant capability.

## Routing Behavior
- Use the metadata under [meta](../meta) to build a view of the available skills and their dependencies.
- Apply the heuristics in [skill-selection.md](../skill-selection.md) to choose an initial skill set.
- Route sub-tasks to the most relevant skill handler in dependency order.
- Re-evaluate the routing decision when new evidence changes the problem statement or complexity.

## Practical Guidance
- Prefer the smallest skill set that can address the immediate sub-task.
- Escalate to additional skills only when the evidence or task scope indicates that the current set is insufficient.
- Keep routing decisions transparent so later reviewers can understand why a particular path was chosen.

## Related Guidance
- See [loader.md](loader.md) for how the initial skill set is discovered.
- See [planner.md](planner.md) for how sub-tasks are sequenced.
- See [validator.md](validator.md) for how the routed work is checked.
