# Concurrency and Performance Knowledge

## Overview
Concurrency and performance engineering determine how a system behaves under load and across multiple execution contexts.

## Key Concepts
- thread-level parallelism
- task queues and work stealing
- lock-free data structures
- contention and cache locality

## Design Strategies
- minimize shared mutable state.
- prefer message-passing or event-driven concurrency.
- use thread pools for controlled parallel execution.
- avoid fine-grained locking in hot paths when possible.

## Practical Workflows
- identify hot code paths and lock contention.
- choose appropriate concurrency primitives for the workload.
- measure performance with representative data and load.

## Common Mistakes
- overusing global locks.
- ignoring false sharing and cache effects.
- building concurrency around thread identity instead of tasks.

## Cross-links
- `../patterns/service-graph.md`
- `../recipes/design-cpp-system.md`

## Related Material

### Knowledge
- [modular-design](modular-design.md)
- [system-design-overview](system-design-overview.md)

### Patterns
- [architecture-patterns](../patterns/architecture-patterns.md)
- [architecture-styles](../patterns/architecture-styles.md)
- [dependency-injection](../patterns/dependency-injection.md)

### Recipes
- [design-cpp-system](../recipes/design-cpp-system.md)
- [design-event-system](../recipes/design-event-system.md)
- [design-large-cpp-project](../recipes/design-large-cpp-project.md)

### Playbooks
- [architecture-review](../playbooks/architecture-review.md)
- [design-large-application](../playbooks/design-large-application.md)
- [plugin-architecture-review](../playbooks/plugin-architecture-review.md)

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

