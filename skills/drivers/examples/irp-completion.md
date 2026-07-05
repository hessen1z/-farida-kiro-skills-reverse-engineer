# IRP Completion Example

## Scenario
Analyze how a driver completes I/O request packets and returns status to the OS.

## Steps
1. Inspect the dispatch routine for calls to `IoCompleteRequest`.
2. Verify `IoStatus.Status` and `IoStatus.Information` are set correctly.
3. Check whether the IRP is completed immediately or deferred.
4. Document any completion routines or worker thread handoffs.

## Outcome
- Confirm proper IRP completion semantics.
- Identify potential race conditions or lost IRPs.
- Understand how the driver signals I/O results.

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
- [driver-entry](driver-entry.md)

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
