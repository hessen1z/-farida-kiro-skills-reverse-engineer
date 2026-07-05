# Protected Process Knowledge

## Overview
Protected Process Light (PPL) and Protected Process (PP) mechanisms restrict access to sensitive Windows processes. These protections are enforced by the kernel and require signed binaries, trusted relationships, or special system policies.

## Key Concepts
- Protected processes only allow trusted code to interact with them.
- PPL extends protection to a broader set of system services and security-sensitive processes.
- Access is controlled at the process object level and via security tokens.

## Analysis Considerations
- Standard debuggers often cannot attach to protected processes.
- Process handles, snapshots, and memory access may be denied.
- A protected process may still be analyzed indirectly by examining inter-process communication or loaded module metadata.

## Evidence
- `ProcessProtectionClass` values in process objects.
- denied access errors when attaching or opening process handles.
- presence of `PPL` signatures and protected signing requirements.

## References
- Microsoft Protected Process documentation
- Windows process protection architecture guides

## Related Material

### Knowledge
- [code-integrity](code-integrity.md)
- [mitigations](mitigations.md)

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

