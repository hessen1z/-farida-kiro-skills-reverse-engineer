---
title: Service Graph Example
skill: system-design
category: examples
difficulty: intermediate
tags: [pe, gui]
updated: 2026-07-05
---
# Service Graph Example

## Overview
A service graph example demonstrates dependency-based startup order for modular services.

## Components
- `ServiceA` depends on `ServiceB`.
- `ServiceB` depends on `ServiceC`.
- A graph builder computes initialization order.

## Notes
- Use topological sort to avoid dependency cycles.
- Initialize services only after all dependencies are ready.
- Shutdown in reverse order to avoid service use-after-free.

## Cross References
- `../patterns/service-graph.md`
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
- [architecture-review](../playbooks/architecture-review.md)
- [design-large-application](../playbooks/design-large-application.md)
- [plugin-architecture-review](../playbooks/plugin-architecture-review.md)

### Examples
- [di-example](di-example.md)
- [event-dispatcher-example](event-dispatcher-example.md)
- [memory-manager-example](memory-manager-example.md)

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
## Practical Guidance

- Start from the concrete objective and define the expected outcome before applying the workflow.
- Use the related examples, recipes, playbooks, and references as the first implementation reference.
- Keep the guidance grounded in the surrounding skill context and verify the result with available evidence.
- Favor practical, maintainable steps over abstract theory when the document is used in real work.
## Verification Checklist

- Confirm that the main objective is clear and the workflow is actionable.
- Ensure the document points to the most relevant examples, recipes, or playbooks.
- Validate that the terminology is consistent with the rest of the skill.
- Check that the practical guidance is specific enough to be used without further interpretation.
