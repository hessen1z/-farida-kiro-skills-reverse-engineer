---
title: Analyze Code Integrity Recipe
skill: windows-security
category: recipes
difficulty: intermediate
tags: [pe, windows, driver, gui, kernel]
updated: 2026-07-05
---
# Analyze Code Integrity Recipe

## Purpose
Determine whether a Windows binary or driver is subject to code integrity policies and whether those policies are enforced at load time.

## Prerequisites
- Access to PE metadata and digital signature tools.
- Knowledge of Windows Authenticode and kernel code integrity enforcement.
- Ability to inspect system event logs and driver load status.

## Inputs
- PE image and certificate information.
- driver loading logs and error codes.
- code integrity policy configuration.

## Steps
1. Inspect the binary's digital signature with tools like `sigcheck` or `osslsigncode`.
2. Check the PE sections for a signature directory and catalog information.
3. Evaluate the system's code integrity policy (e.g. secure boot, HVCI, driver signing enforcement).
4. Reproduce load attempts and capture any integrity failure codes or event log entries.
5. Compare observed behavior with expected policy enforcement.

## Verification
- A signed image that loads successfully under current policy is validated.
- An image rejected due to integrity results in documented error codes and policy mismatch.
- Signed-but-modified images are flagged as integrity failures.

## Notes
- Kernel-mode driver integrity is enforced at a different level than user-mode process loading.
- Secure boot and Device Guard can impose stricter signing requirements.

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
- [analyze-protected-process](analyze-protected-process.md)
- [analyze-security-policy](analyze-security-policy.md)

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

