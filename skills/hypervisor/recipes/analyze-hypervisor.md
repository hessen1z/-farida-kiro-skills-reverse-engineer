---
title: Analyze Hypervisor Recipe
skill: hypervisor
category: recipes
difficulty: intermediate
tags: [pe, gui, debug]
updated: 2026-07-05
---
# Analyze Hypervisor Recipe

## Purpose
Analyze a hypervisor implementation or environment to understand its virtualization controls, guest state management, and isolation boundaries.

## Prerequisites
- access to hypervisor code, logs, or debug output.
- knowledge of VT-x/AMD-V and VMCS/VMCB internals.
- ability to inspect guest and host state transitions.

## Inputs
- hypervisor initialization sequence.
- VMCS/VMCB structures and control fields.
- EPT/NPT tables and VM exit records.

## Steps
1. Identify the virtualization extensions in use.
2. Inspect root and non-root mode transition setup.
3. Examine VMCS/VMCB control fields and guest/host state areas.
4. Analyze VM exit reasons and handler routines.
5. Validate memory virtualization through EPT/NPT mappings.

## Verification
- Confirm the hypervisor enforces proper guest isolation.
- Verify VM exit handling is comprehensive and secure.
- Ensure nested virtualization and device emulation are correctly configured.

## Notes
- hypervisor failure modes often arise from improper VM exit emulation or invalid memory mappings.
- keep performance and security trade-offs explicit when analyzing virtualization design.

## References
- `../knowledge/virtualization-fundamentals.md`
- `../patterns/hypervisor-patterns.md`

## Related Material

### Knowledge
- [hyper-v-vbs](../knowledge/hyper-v-vbs.md)
- [hypervisor-architecture](../knowledge/hypervisor-architecture.md)
- [virtualization-fundamentals](../knowledge/virtualization-fundamentals.md)

### Patterns
- [ept-management](../patterns/ept-management.md)
- [hypervisor-patterns](../patterns/hypervisor-patterns.md)

### Recipes
- [analyze-ept](analyze-ept.md)
- [analyze-vbs](analyze-vbs.md)
- [analyze-vm-exit](analyze-vm-exit.md)

### Playbooks
- [analyze-hyper-v](../playbooks/analyze-hyper-v.md)
- [analyze-hypervisor](../playbooks/analyze-hypervisor.md)
- [analyze-vbs](../playbooks/analyze-vbs.md)

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

