# Analyze Tamper Recipe

## Purpose
Analyze runtime integrity checks and tamper-protection mechanisms in a game client.

## Prerequisites
- Protected game binary or module.
- Debugger and disassembler.
- Knowledge of common integrity check patterns.

## Inputs
- integrity check functions and code pages.
- expected vs actual memory contents.

## Steps
1. Locate runtime integrity validation routines.
2. Trace how memory regions or code pages are hashed or compared.
3. Identify trigger conditions for protection escalation.
4. Inspect bypass points or validation data.
5. Document the protection scope and affected areas.

## Verification
- Confirm the tamper check path is executed and validated.
- Validate whether bypassing the check preserves normal behavior.
- Record the scope and timing of the protection.

## Notes
- Some tamper checks are obfuscated or spread across multiple routines.
- Do not modify protected memory before capturing original state.

## References
- Anti-tamper and integrity protection guides

## Related Material

### Knowledge
- [anti-cheat](../knowledge/anti-cheat.md)

### Patterns
- [anti-debug](../patterns/anti-debug.md)
- [tamper-check](../patterns/tamper-check.md)

### Recipes
- [trace-anti-debug](trace-anti-debug.md)

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

