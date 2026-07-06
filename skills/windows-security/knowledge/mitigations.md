---
title: Windows Security Mitigations
skill: windows-security
category: knowledge
difficulty: intermediate
tags: [pe, windows, driver, gui, kernel, debug]
updated: 2026-07-05
---
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

## Practical Guidance

- When analyzing protected targets, plan for controlled environments that allow mitigation-aware tracing (instrumented builds, test policies).
- Record expected debugger limitations and prefer offline artifact collection when kernel-enforced mitigations prevent live inspection.

## Tools & Commands

- Use `sigcheck`/`signtool` to inspect code signing and `bcdedit`/`systeminfo` to enumerate enabled mitigations.
- For hypervisor-based mitigations, use hypervisor debugging tools to inspect secure kernel state where available.

## Validation Checklist

- Verify which mitigations are enabled on the target and document their impact on analysis tooling.
- Confirm alternative artifact collection methods when live debugging is restricted by mitigations.

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

