# Hypervisor Patterns

## Pattern Name
Hypervisor Patterns

## Problem
Recognize virtualization-related execution behavior and hardware-managed state transitions.

## Context
Hypervisors rely on VM exit and VM entry semantics, control structures, and memory translation to implement isolation and virtualization.

## Recognition
- `VMXON`, `VMLAUNCH`, `VMRESUME`, `VMREAD`, `VMWRITE`
- VM exit reason fields and `VMCS`/`VMCB` control bits
- EPT/NPT violations and second-level page table lookups
- synthetic interrupts and VMBus message handler routines

## Evidence
- guest exits captured in hypervisor logs or debug output
- VMCS/VMCB values in memory dumps
- EPT page table entries with execute-only or read/write restrictions

## Resolution / Action
- map exit reasons to guest actions and hypervisor handling
- verify that EPT/NPT entries enforce the intended memory isolation
- inspect VMCS control settings for correct trapping and guest state preservation

## Notes
- not all privileged instructions cause VM exits; some are handled in hardware transparently.
- nested virtualization introduces additional levels of guest/host state and shadow translation.

## References
- Intel SDM: VMX exit information
- AMD SVM documentation

## See Also
- `../knowledge/vmcs-ept.md`
- `../recipes/analyze-vm-exit.md`

## Related Material

### Knowledge
- [hyper-v-vbs](../knowledge/hyper-v-vbs.md)
- [hypervisor-architecture](../knowledge/hypervisor-architecture.md)
- [virtualization-fundamentals](../knowledge/virtualization-fundamentals.md)

### Patterns
- [ept-management](ept-management.md)

### Recipes
- [analyze-ept](../recipes/analyze-ept.md)
- [analyze-hypervisor](../recipes/analyze-hypervisor.md)
- [analyze-vbs](../recipes/analyze-vbs.md)

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

