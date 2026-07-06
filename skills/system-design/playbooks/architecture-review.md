---
title: Architecture Review Playbook
skill: system-design
category: playbooks
difficulty: intermediate
tags: [pe, gui]
updated: 2026-07-05
---
# Architecture Review Playbook

## Goal
Review a system architecture for modularity, scalability, and maintainability.

## Steps
1. Catalog system components and their responsibilities.
2. Evaluate module boundaries and dependency direction.
3. Confirm that runtime services are isolated and testable.
4. Verify platform-specific code is abstracted behind interfaces.
5. Examine performance-critical paths for unnecessary coupling.

## Focus Areas
- component cohesion and coupling
- interface clarity
- layering and dependency flow
- scaling through modular subsystems

## Actions
- Diagram the service and module graph.
- Identify unnecessary shared state or global access.
- Check for stable service initialization order.
- Ensure failure modes do not compromise the whole system.

## Cross References
- `../patterns/architecture-styles.md`
- `../recipes/design-cpp-system.md`

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
- [design-large-application](design-large-application.md)
- [plugin-architecture-review](plugin-architecture-review.md)
- [scalability-review](scalability-review.md)

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

