# Control Flow Guard Pattern

## Pattern Name
Control Flow Guard (CFG)

## Problem
Detect code that uses Control Flow Guard to validate indirect call targets.

## Context
CFG is a Windows mitigation that intercepts indirect calls and validates targets against a function table.

## Recognition
- presence of `__guard_check_icall` or `__guard_dispatch_icall` imports
- CFG metadata sections in the PE image
- indirect call redirection through guard thunk functions

## Evidence
- protection against indirect call hijacking
- crashes or exceptions when indirect target validation fails
- security metadata embedded in executable sections

## Resolution / Action
- identify CFG-protected functions and guard metadata
- use matching symbol data to understand indirect call paths
- consider how CFG affects dynamic instrumentation

## Notes
- CFG limits exploitability but can be bypassed by returning to legitimate function targets.
- Debugging CFG-protected code may require understanding thunk dispatch paths.

## References
- Microsoft Control Flow Guard documentation

## Related Material

### Knowledge
- [code-integrity](../knowledge/code-integrity.md)
- [mitigations](../knowledge/mitigations.md)
- [protected-process](../knowledge/protected-process.md)

### Patterns
- [aslr](aslr.md)
- [code-signing](code-signing.md)
- [process-protection](process-protection.md)

### Recipes
- [analyze-code-integrity](../recipes/analyze-code-integrity.md)
- [analyze-protected-process](../recipes/analyze-protected-process.md)
- [analyze-security-policy](../recipes/analyze-security-policy.md)

### Playbooks
- [ExploitMitigations](../playbooks/ExploitMitigations.md)
- [Mitigations](../playbooks/Mitigations.md)
- [ProcessProtection](../playbooks/ProcessProtection.md)

### Examples
- [code-integrity](../examples/code-integrity.md)
- [mitigations](../examples/mitigations.md)
- [protected-process](../examples/protected-process.md)

### References
- [references](../references/references.md)

### Rules
- [mitigation-guidelines](../rules/mitigation-guidelines.md)

### Prompts
- [code-integrity-analysis](../prompts/code-integrity-analysis.md)
- [mitigations-analysis](../prompts/mitigations-analysis.md)
- [protected-process-analysis](../prompts/protected-process-analysis.md)

### Checklists
- [checklist](../checklists/checklist.md)

