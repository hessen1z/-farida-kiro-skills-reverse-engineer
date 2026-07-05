# Modular Design Knowledge

## Overview
Modular design divides a system into discrete components with well-defined responsibilities and interfaces.

## Key Concepts
- separation of concerns
- information hiding
- interface contracts
- module independence

## Benefits
- improved maintainability
- easier testing
- isolated evolution of subsystems
- clearer ownership and team boundaries

## Design Strategies
- keep modules focused on a single responsibility.
- define stable interfaces and avoid exposing internal details.
- use adapters or facades to isolate platform-specific behavior.

## Practical Workflows
- decompose features into service modules.
- identify shared data and minimize direct coupling.
- document module boundaries and dependencies.

## Common Mistakes
- large "God" modules with mixed responsibilities.
- cyclic dependencies between modules.
- leaking implementation details through interfaces.

## Cross-links
- `../patterns/architecture-styles.md`
- `../rules/system-design-guidelines.md`

## Related Material

### Knowledge
- [concurrency-and-performance](concurrency-and-performance.md)
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

