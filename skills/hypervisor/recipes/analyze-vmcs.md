# Analyze VMCS Recipe

## Purpose
Analyze the Virtual Machine Control Structure (VMCS) to understand guest/host state, exit controls, and virtualization policy.

## Prerequisites
- knowledge of Intel VT-x VMCS fields.
- access to hypervisor memory and VMCS pointers.
- ability to decode control and state fields.

## Inputs
- VMCS pointer and guest/host state block data.
- VM-execution controls and VM-exit control fields.
- VM-entry controls and exit information fields.

## Steps
1. Locate the current VMCS and verify its revision identifier.
2. Inspect the guest-state area for control registers, segment descriptors, and RIP/RSP.
3. Review host-state fields for the hypervisor context.
4. Check VM-execution controls and identify all configured exit conditions.
5. Validate the VM-entry controls for correct guest load behavior.

## Verification
- Confirm the VMCS fields reflect the intended guest execution environment.
- Ensure host-state fields are correctly preserved for hypervisor resumption.
- Identify mismatched or unsupported control bits that can cause unexpected exits.

## Notes
- VMCS revisions may differ across CPU models and must match the hypervisor’s memory layout.
- Some fields are read-only, and their values depend on both hardware and hypervisor configuration.

## References
- `../knowledge/vmcs-ept.md`
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
- [analyze-hypervisor](analyze-hypervisor.md)
- [analyze-vbs](analyze-vbs.md)

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

