# Windows Security Checklist

## Preparation
- [ ] Identify the target binary and its protection mitigations.
- [ ] Confirm whether the process is protected or uses PPL.
- [ ] Gather PE metadata and process-level security attributes.

## Diagnostics
- [ ] Check for DEP, ASLR, CFG, and other mitigations.
- [ ] Inspect process access and handle restrictions.
- [ ] Analyze code integrity and runtime validation behavior.

## Validation
- [ ] Confirm mitigation enforcement with runtime evidence.
- [ ] Document whether security features block debugging.
- [ ] Record protection boundaries and trust requirements.

## Notes
- [ ] Process protection is enforced by the kernel.
- [ ] Avoid destructive analysis on protected processes.

## Related Material

### Knowledge
- [code-integrity](../knowledge/code-integrity.md)
- [mitigations](../knowledge/mitigations.md)
- [protected-process](../knowledge/protected-process.md)

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

