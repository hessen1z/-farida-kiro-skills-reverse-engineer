Router

Purpose: Route tasks to the appropriate skills and manage control flow.

Behavior
- Use `meta/skills.json` and `meta/dependencies.json` to build a directed acyclic graph of skills.
- Given a task, use `skill-selection.md` heuristics to choose an initial skill set.
- Route data and sub-tasks to skill-specific handlers in load order.
- Monitor for evidence or verification results and re-route as needed.

Notes
- Router should prefer minimal skill sets and escalate only when required.
