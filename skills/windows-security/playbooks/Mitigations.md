---
title: Windows Security Mitigations Playbook
skill: windows-security
category: playbooks
difficulty: intermediate
tags: [pe, windows, driver, gui, debug]
updated: 2026-07-05
---
# Windows Security Mitigations Playbook

## Purpose
Review a Windows executable or driver to assess exploit hardening and runtime protections.

## Approach
- Inspect the PE header for ASLR, DEP, CFG, and other mitigation flags.
- Use system and debugger tools to verify process mitigation state and security features at runtime.
- Compare mitigation findings to exploit strategies and analysis constraints.

## Steps
1. Start by examining the binary's optional header and load configuration.
2. Identify compile-time protections: ASLR, DEP, CFG, SEHOP, ControlFlowGuard.
3. Verify runtime enforcement: process mitigation APIs, status queries, and policy checks.
4. Document any mismatches between binary metadata and runtime state.

## Outcome
- A mitigation profile that reveals the binary's attack surface.
- Clear guidance on which protections are effective and which require bypass.

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
- [ExploitMitigations](ExploitMitigations.md)
- [ProcessProtection](ProcessProtection.md)

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

