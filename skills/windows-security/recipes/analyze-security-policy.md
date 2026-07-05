# Analyze Windows Security Policy Recipe

## Purpose
Inspect Windows security policy settings that control code integrity, process protection, and mitigation enforcement.

## Prerequisites
- Access to local security policy tools and system configuration utilities.
- Knowledge of Windows security features such as Secure Boot, HVCI, and driver signing.
- Ability to query registry and group policy settings.

## Inputs
- current code integrity and secure boot configuration.
- process protection and PPL policy state.
- mitigation enforcement settings such as CFG and DEP.

## Steps
1. Query the system for secure boot and code integrity policy status.
2. Check registry and policy settings for driver signing enforcement.
3. Determine whether HVCI or Device Guard is enabled.
4. Inspect protected process and process protection policy values.
5. Correlate policy state with observed runtime behavior and load failures.

## Verification
- The current policy state is documented and matches observed target behavior.
- Any mismatches between configured policy and runtime evidence are identified.
- The analysis clarifies whether bypass or a trusted environment is required.

## Notes
- Policy may be enforced by the kernel or by firmware-level features like Secure Boot.
- Some settings require a reboot to take effect and may only apply after system restart.

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
- [analyze-code-integrity](analyze-code-integrity.md)
- [analyze-protected-process](analyze-protected-process.md)

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

