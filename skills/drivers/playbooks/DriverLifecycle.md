# Driver Lifecycle Playbook

## Objective
Understand the lifecycle of a Windows driver from load to unload.

## Steps
1. Identify `DriverEntry` and initial device creation.
2. Trace dispatch table setup and major function handlers.
3. Inspect runtime state and resource allocation.
4. Review driver unload and cleanup procedures.
5. Validate device object deletion and symbolic link removal.

## Common Scenarios
- device objects left registered after unload.
- dispatch routines missing error handling.
- cleanup paths not releasing allocated resources.

## Best Practices
- Confirm `DriverUnload` cleans up all created objects.
- Ensure IRPs are completed before freeing related data.
- Document lifecycle transitions and error handling.

## Notes
- Some drivers intentionally remain loaded until reboot.
- Device cleanup is essential for driver stability.

## Related Material

### Knowledge
- [driver-model](../knowledge/driver-model.md)

### Patterns
- [irp-flow](../patterns/irp-flow.md)

### Recipes
- [analyze-irp](../recipes/analyze-irp.md)
- [debug-driver](../recipes/debug-driver.md)

### Playbooks
- [DriverCrash](DriverCrash.md)

### Examples
- [driver-entry](../examples/driver-entry.md)
- [irp-completion](../examples/irp-completion.md)

### References
- [references](../references/references.md)

### Prompts
- [driver-analysis](../prompts/driver-analysis.md)

### Checklists
- [checklist](../checklists/checklist.md)
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
