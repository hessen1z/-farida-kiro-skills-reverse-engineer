---
title: Design Large Application Playbook
skill: system-design
category: playbooks
difficulty: intermediate
tags: [pe, gui]
updated: 2026-07-05
---
# Design Large Application Playbook

## Goal
Guide the design and review of a large application architecture for extensibility, maintainability, and performance.

## Steps
1. Identify business requirements and quality attributes.
2. Define subsystems, interfaces, and ownership boundaries.
3. Specify data flow and cross-component communication.
4. Validate concurrency, resource management, and scaling strategies.
5. Review implementation plans for modularity and test coverage.

## Focus Areas
- architectural coherence and subsystem boundaries
- integration points and API stability
- runtime performance and failure isolation
- developer productivity and maintenance overhead

## Actions
- diagram the application architecture and service graph.
- review module dependencies and interface contracts.
- ensure platform-specific concerns are abstracted.
- confirm monitoring, logging, and diagnostics are integrated.

## Cross References
- `../recipes/design-large-cpp-project.md`
- `../patterns/architecture-patterns.md`
- `../rules/system-design-guidelines.md`

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

