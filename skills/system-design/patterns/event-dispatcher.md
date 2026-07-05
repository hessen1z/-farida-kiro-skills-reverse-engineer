# Event Dispatcher Patterns

## Overview
Event dispatchers decouple event producers from consumers, enabling flexible and extensible systems.

## Patterns
- Use observer or publisher/subscriber patterns.
- Keep event payloads small and immutable.
- Use filtering or routing to reduce unnecessary event delivery.

## Practical Workflow
1. Define event types and payload interfaces.
2. Register listeners with clear lifecycle boundaries.
3. Dispatch events through a centralized dispatcher.
4. Handle errors in event handlers without stopping the dispatcher.

## Cross-References
- `../knowledge/system-design-overview.md`

## Related Material

### Knowledge
- [concurrency-and-performance](../knowledge/concurrency-and-performance.md)
- [modular-design](../knowledge/modular-design.md)
- [system-design-overview](../knowledge/system-design-overview.md)

### Patterns
- [architecture-patterns](architecture-patterns.md)
- [architecture-styles](architecture-styles.md)
- [dependency-injection](dependency-injection.md)

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
