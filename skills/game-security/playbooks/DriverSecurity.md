# Driver Security Playbook

## Objective
Analyze kernel-mode security and anti-cheat drivers used by game clients.

## Steps
1. Identify driver modules loaded by the game or launcher.
2. Inspect driver entry and device dispatch routines.
3. Trace monitoring or enforcement flows for process and memory state.
4. Evaluate interactions between kernel drivers and user-mode clients.
5. Document driver security boundaries and trust assumptions.

## Common Scenarios
- kernel drivers performing process memory scanning.
- secure drivers validating game module integrity.
- drivers enforcing protected input or cheat detection.

## Best Practices
- Use kernel debugging or logging to inspect driver behavior.
- Preserve system stability when analyzing security drivers.
- Correlate driver observations with user-mode security logic.

## Notes
- Kernel-mode security drivers may require signed drivers or special boot options.

## Related Material

### Knowledge
- [anti-cheat](../knowledge/anti-cheat.md)

### Patterns
- [anti-debug](../patterns/anti-debug.md)
- [tamper-check](../patterns/tamper-check.md)

### Recipes
- [analyze-tamper](../recipes/analyze-tamper.md)
- [trace-anti-debug](../recipes/trace-anti-debug.md)

### Playbooks
- [ClientSecurity](ClientSecurity.md)

### Examples
- [anti-debug-analysis](../examples/anti-debug-analysis.md)

### References
- [references](../references/references.md)

### Rules
- [security-principles](../rules/security-principles.md)

### Prompts
- [security-analysis](../prompts/security-analysis.md)

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
