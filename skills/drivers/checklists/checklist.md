---
title: Drivers Checklist
skill: drivers
category: checklists
difficulty: intermediate
tags: [pe, driver, gui, kernel, debug]
updated: 2026-07-05
---
# Drivers Checklist

## Preparation
- [ ] Identify the driver binary and target kernel environment.
- [ ] Confirm driver symbols and debug configuration.
- [ ] Gather crash dumps and driver load metadata.

## Diagnostics
- [ ] Locate `DriverEntry` and dispatch table initialization.
- [ ] Inspect IRP handling for create, read, write, and device control.
- [ ] Trace driver synchronization and resource use.
- [ ] Check driver unload and cleanup behavior.

## Validation
- [ ] Confirm driver crash or misbehavior is reproduced.
- [ ] Verify IRP completion paths and error handling.
- [ ] Document driver lifecycle and kernel interaction.

## Notes
- [ ] Keep kernel debugging safe and non-destructive.
- [ ] Preserve dump files and original driver binaries.

## Related Material

### Knowledge
- [driver-model](../knowledge/driver-model.md)

### Patterns
- [irp-flow](../patterns/irp-flow.md)

### Recipes
- [analyze-irp](../recipes/analyze-irp.md)
- [debug-driver](../recipes/debug-driver.md)

### Playbooks
- [DriverCrash](../playbooks/DriverCrash.md)
- [DriverLifecycle](../playbooks/DriverLifecycle.md)

### Examples
- [driver-entry](../examples/driver-entry.md)
- [irp-completion](../examples/irp-completion.md)

### References
- [references](../references/references.md)

### Prompts
- [driver-analysis](../prompts/driver-analysis.md)
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
