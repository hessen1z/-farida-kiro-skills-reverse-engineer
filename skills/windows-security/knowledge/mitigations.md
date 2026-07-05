# Windows Security Mitigations

## Overview

Windows includes built-in mitigations to protect processes and the operating system from exploitation. These mitigations affect how code executes and how security tools observe runtime behavior.

## Common mitigations

- Data Execution Prevention (DEP)
- Address Space Layout Randomization (ASLR)
- Control Flow Guard (CFG)
- Driver Signature Enforcement (DSE)
- Hypervisor-protected code integrity (HVCI)

## Process protection

- Protected processes and protected process light (PPL)
- Private namespaces and secure handle access
- Process and job object restrictions

## Notes

- These mitigations can impact debugging and analysis when attached to protected targets.
- Some mitigations are enforced by the kernel or by a hypervisor.

## References

- Microsoft Windows security documentation
- Exploit mitigation guides

## Related Material

### Knowledge
- [code-integrity](code-integrity.md)
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

