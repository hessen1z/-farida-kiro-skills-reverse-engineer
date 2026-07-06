---
title: Scalability Review Playbook
skill: system-design
category: playbooks
difficulty: intermediate
tags: [pe, gui]
updated: 2026-07-05
---
# Scalability Review Playbook

## Goal
Review system design decisions for scalability under load and growth.

## Steps
1. Identify bottlenecks in CPU, memory, I/O, or network.
2. Examine concurrent execution models and resource contention.
3. Confirm stateless or partitioned service design where possible.
4. Review caching, batching, and data locality strategies.
5. Validate scaling approach for both vertical and horizontal growth.

## Focus Areas
- concurrency model and thread usage
- data partitioning
- service scalability
- resource isolation

## Actions
- Look for shared mutable state that prevents scaling.
- Evaluate the impact of locking on throughput.
- Check whether services can be scaled independently.
- Ensure system health and failure isolation are documented.

## Cross References
- `../patterns/service-graph.md`
- `../recipes/design-memory-manager.md`

## Related Material

### Knowledge
- [concurrency-and-performance](../knowledge/concurrency-and-performance.md)
- [modular-design](../knowledge/modular-design.md)
- [system-design-overview](../knowledge/system-design-overview.md)

### Patterns
- [architecture-patterns](../patterns/architecture-patterns.md)
- [architecture-styles](../patterns/architecture-styles.md)
- [dependency-injection](../patterns/dependency-injection.md)

### Recipes
- [design-cpp-system](../recipes/design-cpp-system.md)
- [design-event-system](../recipes/design-event-system.md)
- [design-large-cpp-project](../recipes/design-large-cpp-project.md)

### Playbooks
- [architecture-review](architecture-review.md)
- [design-large-application](design-large-application.md)
- [plugin-architecture-review](plugin-architecture-review.md)

### Examples
- [di-example](../examples/di-example.md)
- [event-dispatcher-example](../examples/event-dispatcher-example.md)
- [memory-manager-example](../examples/memory-manager-example.md)

### References
- [references](../references/references.md)

### Rules
- [system-design-guidelines](../rules/system-design-guidelines.md)

### Prompts
- [architecture-review](../prompts/architecture-review.md)
- [plugin-architecture-review](../prompts/plugin-architecture-review.md)
- [scalability-review](../prompts/scalability-review.md)

### Checklists
- [system-design-checklist](../checklists/system-design-checklist.md)

