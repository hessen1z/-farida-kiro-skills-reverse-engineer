# Anti-Debug Analysis Example

## Scenario
Analyze a game client to identify debugger detection and understand how it changes runtime flow.

## Steps
1. Search for `IsDebuggerPresent` and related APIs.
2. Break on detection calls and inspect the return path.
3. Determine whether the client disables features or exits.
4. Document the protection scope and any bypass points.

## Outcome
- Identify debugger detection points.
- Understand how detection affects game behavior.
- Provide evidence for further analysis or bypass work.

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
- [ClientSecurity](../playbooks/ClientSecurity.md)
- [DriverSecurity](../playbooks/DriverSecurity.md)

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
