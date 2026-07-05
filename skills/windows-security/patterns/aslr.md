# ASLR Pattern

## Pattern Name
Address Space Layout Randomization (ASLR)

## Problem
Detect code or binaries that use ASLR to randomize load addresses and reduce exploit reliability.

## Context
ASLR randomizes module bases and memory regions at process startup.

## Recognition
- dynamic module base addresses across runs
- imports of `GetModuleHandle` or `LoadLibrary` used with randomized modules
- PE image flags indicating compatible ASLR

## Evidence
- difficulty predicting absolute addresses
- need for runtime relocation to find functions and data
- reliance on base relocations for data references

## Resolution / Action
- use runtime module enumeration rather than static addresses
- inspect the PE optional header for ASLR support
- adjust analysis for randomized memory layouts

## Notes
- ASLR is often combined with DEP and CFG.
- Image rebasing is required for non-ASLR binaries.

## References
- Microsoft ASLR documentation

## Related Material

### Knowledge
- [code-integrity](../knowledge/code-integrity.md)
- [mitigations](../knowledge/mitigations.md)
- [protected-process](../knowledge/protected-process.md)

### Patterns
- [cfg](cfg.md)
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

