# Trace Anti-Debug Recipe

## Purpose
Trace anti-debug detection and understand how it affects runtime behavior in a protected game client.

## Prerequisites
- Game binary or module containing anti-debug checks.
- Debugger capable of tracing API calls and execution flow.
- Familiarity with common Windows debug detection APIs.

## Inputs
- protection-related imports and strings.
- known debugger detection functions.

## Steps
1. Identify anti-debug APIs and detection points.
2. Instrument or break on debugger detection calls.
3. Observe the result of the detection and how it changes program flow.
4. Check for secondary protections triggered by detection.
5. Document bypass or mitigation strategies for analysis.

## Verification
- Confirm the debugger detection path executes during startup or runtime.
- Verify whether bypassing the check changes behavior.
- Document the affected modules and protection boundaries.

## Notes
- Anti-debug traces may take multiple runs to observe reliably.
- Combine static analysis with live debugging for robust evidence.

## References
- Windows debugger detection API documentation

## Related Material

### Knowledge
- [anti-cheat](../knowledge/anti-cheat.md)

### Patterns
- [anti-debug](../patterns/anti-debug.md)
- [tamper-check](../patterns/tamper-check.md)

### Recipes
- [analyze-tamper](analyze-tamper.md)

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

