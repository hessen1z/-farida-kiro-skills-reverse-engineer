---
title: Game Security Checklist
skill: game-security
category: checklists
difficulty: intermediate
tags: [pe, anti-cheat, driver, gui, debug]
updated: 2026-07-05
---
# Game Security Checklist

## Preparation
- [ ] Identify all game client and security-related modules.
- [ ] Confirm whether anti-cheat or anti-debug components are present.
- [ ] Collect relevant symbol and module metadata.

## Diagnostics
- [ ] Locate anti-debug and tamper detection routines.
- [ ] Trace security-related API calls and runtime checks.
- [ ] Examine driver or service interactions.
- [ ] Validate whether protections are active or passive.

## Validation
- [ ] Confirm protection triggers and bypass conditions.
- [ ] Document security findings and scope.
- [ ] Preserve evidence prior to modification.

## Notes
- [ ] Use minimal instrumentation to avoid protection escalation.
- [ ] Treat security analysis as part of the larger game engine and debugging workflow.

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

### Examples
- [anti-debug-analysis](../examples/anti-debug-analysis.md)

### References
- [references](../references/references.md)

### Rules
- [security-principles](../rules/security-principles.md)

### Prompts
- [security-analysis](../prompts/security-analysis.md)
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
