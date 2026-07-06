---
title: Analyze Hypervisor Playbook
skill: hypervisor
category: playbooks
difficulty: intermediate
tags: [pe, gui, kernel, debug]
updated: 2026-07-05
---
# Analyze Hypervisor Playbook

## Objective
Analyze a hypervisor environment to understand guest isolation, virtualization controls, and performance characteristics.

## Steps
1. Identify the hypervisor type and supported virtualization extensions.
2. Inspect VMCS/VMCB setup and exit control configuration.
3. Review memory virtualization through EPT/NPT.
4. Analyze VM exit reasons and handler implementations.
5. Validate interrupt and I/O virtualization behavior.
6. Document security boundaries and isolation guarantees.

## Common Scenarios
- hypervisor boot or startup failures
- EPT violation debugging
- guest performance issues due to frequent exits
- VBS secure kernel load or credential protection anomalies

## Best Practices
- use hardware documentation when interpreting VMCS/VMCB fields.
- correlate VM exit logs with guest instruction execution.
- preserve guest state before making any hypervisor changes.
- separate security analysis from performance tuning.

## Outcome
- a complete map of hypervisor guest transition behavior
- identified misconfigurations or security violations in the virtualization stack
- recommended corrections for EPT, exit handling, or VBS setup

## Related Material

### Knowledge
- [hyper-v-vbs](../knowledge/hyper-v-vbs.md)
- [hypervisor-architecture](../knowledge/hypervisor-architecture.md)
- [virtualization-fundamentals](../knowledge/virtualization-fundamentals.md)

### Patterns
- [ept-management](../patterns/ept-management.md)
- [hypervisor-patterns](../patterns/hypervisor-patterns.md)

### Recipes
- [analyze-ept](../recipes/analyze-ept.md)
- [analyze-hypervisor](../recipes/analyze-hypervisor.md)
- [analyze-vbs](../recipes/analyze-vbs.md)

### Playbooks
- [analyze-hyper-v](analyze-hyper-v.md)
- [analyze-vbs](analyze-vbs.md)

### Examples
- [ept-layout](../examples/ept-layout.md)
- [vm-entry-exit](../examples/vm-entry-exit.md)

### References
- [references](../references/references.md)

### Rules
- [hypervisor-guidelines](../rules/hypervisor-guidelines.md)

### Prompts
- [hypervisor-analysis](../prompts/hypervisor-analysis.md)
- [vbs-analysis](../prompts/vbs-analysis.md)
- [vmcs-analysis](../prompts/vmcs-analysis.md)

### Checklists
- [checklist](../checklists/checklist.md)

