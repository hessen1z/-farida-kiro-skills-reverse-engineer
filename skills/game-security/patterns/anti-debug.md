# Anti-Debug Pattern

## Pattern Name
Debugger detection and blocking

## Problem
Detect and handle code paths intended to identify or hinder debuggers.

## Context
Anti-debug techniques are used to prevent analysis, tampering, or cheating.

## Recognition
- calls to `IsDebuggerPresent`, `CheckRemoteDebuggerPresent`
- `NtQueryInformationProcess` with `ProcessDebugPort`
- self-debugging or process injection checks
- timing checks around `QueryPerformanceCounter`

## Evidence
- conditional branches on debugger presence
- exceptions or traps when a debugger is detected
- unusual thread or handle enumeration behavior

## Resolution / Action
- identify the debug detection logic.
- trace how the result affects runtime behavior.
- use less intrusive debugging methods when analyzing.

## Notes
- Anti-debug logic may be layered with anti-tamper protections.
- Some protections use normal OS APIs to avoid detection.

## References
- Windows anti-debugging articles

## Related Material

### Knowledge
- [anti-cheat](../knowledge/anti-cheat.md)

### Patterns
- [tamper-check](tamper-check.md)

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
