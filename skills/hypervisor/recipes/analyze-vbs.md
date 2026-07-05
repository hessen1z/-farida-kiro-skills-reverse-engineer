# Analyze VBS Recipe

## Purpose
Analyze Virtualization-Based Security (VBS) to understand secure kernel isolation, credential protection, and hypervisor-enforced memory boundaries.

## Prerequisites
- knowledge of Hyper-V and VBS architecture.
- access to system configuration and secure kernel status.
- familiarity with EPT and memory isolation concepts.

## Inputs
- VBS policy state and secure kernel activation records.
- guarded memory layout and partition configuration.
- credential or secret storage components.

## Steps
1. Inspect the system policy for VBS and Secure Kernel enablement.
2. Verify secure kernel initialization and partition state.
3. Examine EPT policies protecting secure kernel memory.
4. Analyze credential protection components such as LSA isolations.
5. Validate whether guest or normal kernel code can access guarded memory.

## Verification
- Confirm VBS is active and secure kernel memory is isolated.
- Verify credential protection boundaries and denials of normal kernel access.
- Document any security policy misconfigurations.

## Notes
- VBS depends on both hardware virtualization and Windows security policy.
- Secure Kernel memory is not directly accessible to standard kernel-mode debugging.

## References
- `../knowledge/hyper-v-vbs.md`
- `../patterns/vbs-patterns.md`

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
- [analyze-hypervisor](analyze-hypervisor.md)
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

