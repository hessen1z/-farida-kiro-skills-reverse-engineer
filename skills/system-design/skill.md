---
name: System Design
version: 1.0
priority: critical
requires:
  - shared
  - cpp
  - windows-internals
tags:
  - architecture
  - design
  - engineering
description: Core system design skill covering software architecture, modular systems, performance engineering, and scalable C++ system design.
---

# System Design Skill

## Purpose
Provide a production-grade reference for software architecture, modular design, system scalability, and maintainable C++ engineering. This skill helps design large applications, plugin systems, event systems, and robust runtime architectures.

## What this skill provides
- Knowledge of architecture styles, design patterns, SOLID principles, dependency injection, and layered design.
- Patterns for plugin systems, event dispatchers, job systems, memory managers, and service graphs.
- Recipes for designing large C++ projects, logging systems, memory managers, and plugin architectures.
- Playbooks for reviewing architecture, improving maintainability, optimizing performance, and designing APIs.
- Examples for scalable C++ architecture and system design best practices.

## Prerequisites
- `shared` for documentation conventions.
- `cpp` for implementation examples and architecture patterns.
- `windows-internals` for platform-aware system design.

## Used by
- `networking`
- `game-engines`
- `hypervisor`

## Related Skills
- `cpp` — system implementation and type-safe architecture.
- `networking` — distributed system architecture and protocol design.
- `debugging` — maintainability and testable design for reliability.

## Entry Conditions
- A large C++ system or architectural review is required.
- Modularity, performance, or scalability decisions need evaluation.
- Plugin, event, or job system design is part of the system.

## Exit Conditions
- Architecture is documented with clear modular boundaries.
- Design patterns and scalability concerns are understood.
- Maintainability, testing, and performance features are mapped.

## Typical Workflow
1. Identify system requirements and desired quality attributes.
2. Select an architecture style and map core subsystems.
3. Define module boundaries, interfaces, and dependency flow.
4. Evaluate performance, memory, and concurrency trade-offs.
5. Document the architecture with examples, patterns, and best practices.

## Notes
- Large systems require disciplined layering and explicit ownership.
- Avoid premature optimization; balance clarity with performance.

## Related Material

- Knowledge: [concurrency-and-performance](knowledge/concurrency-and-performance.md)
- Patterns: [architecture-patterns](patterns/architecture-patterns.md)
- Recipes: [design-cpp-system](recipes/design-cpp-system.md)
- Playbooks: [architecture-review](playbooks/architecture-review.md)
- Examples: [di-example](examples/di-example.md)
- References: [references](references/references.md)
- Rules: [system-design-guidelines](rules/system-design-guidelines.md)
- Prompts: [architecture-review](prompts/architecture-review.md)
- Checklists: [system-design-checklist](checklists/system-design-checklist.md)

