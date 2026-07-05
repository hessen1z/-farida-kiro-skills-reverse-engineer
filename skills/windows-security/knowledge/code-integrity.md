# Code Integrity Knowledge

## Overview
Windows code integrity enforces that only trusted, signed binaries may execute in secure contexts. This includes kernel-mode drivers, protected processes, and features such as Device Guard, Credential Guard, and HVCI.

## Key Concepts
- Driver Signature Enforcement (DSE) validates signatures for kernel-mode drivers.
- Code integrity policies may require certificates from Microsoft or trusted authorities.
- Hypervisor-protected Code Integrity (HVCI) extends validation into virtualization.

## Analysis Considerations
- Unsigned or improperly signed binaries may be blocked or fail to load.
- Code integrity metadata is stored in PE headers and Authenticode signatures.
- Runtime evidence of integrity failures may appear in system event logs or load errors.

## Evidence
- driver load failures with `0xC0000428` or integrity violation codes.
- blocked module loads for unsigned or altered images.
- signature validation metadata within PE digital signatures.

## References
- Microsoft Code Integrity documentation
- Device Guard / Credential Guard architecture

## Related Material

### Knowledge
- [mitigations](mitigations.md)
- [protected-process](protected-process.md)

### Patterns
- [aslr](../patterns/aslr.md)
- [cfg](../patterns/cfg.md)
- [code-signing](../patterns/code-signing.md)

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

