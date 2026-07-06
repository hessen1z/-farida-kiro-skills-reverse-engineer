---
title: Code Integrity Analysis Example
skill: windows-security
category: examples
difficulty: intermediate
tags: [pe, windows, driver, gui, kernel]
updated: 2026-07-05
---
# Code Integrity Analysis Example

## Scenario
Investigate a kernel-mode driver or protected service that fails to load under the current Windows code integrity policy.

## Steps
1. Inspect the binary's signature and PE certificate directory.
2. Use a signature validation tool to verify the Authenticode signature.
3. Review system event logs and driver load errors for integrity failure codes.
4. Compare the observed load behavior to current policy settings such as driver signing enforcement and secure boot.
5. Note whether HVCI or Device Guard affects the target.

## Outcome
- A clear explanation of why the image is blocked or accepted.
- Evidence of code integrity policy interaction with the target binary.
- Actionable next steps for trusted load or policy mitigation.

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
- [mitigations](mitigations.md)
- [protected-process](protected-process.md)

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

