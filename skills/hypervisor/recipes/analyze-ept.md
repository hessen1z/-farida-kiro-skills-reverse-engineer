# Analyze EPT Recipe

## Purpose
Analyze Extended Page Tables (EPT) to verify guest memory virtualization, access permissions, and isolation boundaries.

## Prerequisites
- knowledge of EPT structures and permission bits.
- access to hypervisor or monitor-level memory state.
- understanding of guest memory layout and page table mappings.

## Inputs
- EPT pointer and page-table hierarchy.
- guest physical address causing the violation.
- host physical address translations.

## Steps
1. Locate the EPTP in the VMCS and decode its components.
2. Walk the EPT page table levels for the guest physical address.
3. Inspect permission bits and memory type fields.
4. Compare the EPT mapping to guest page table mappings.
5. Determine whether the violation results from invalid permissions, stale mappings, or nested translation errors.

## Verification
- Confirm the guest physical address resolves to the correct host physical page.
- Verify read/write/execute permissions reflect the intended isolation policy.
- Identify any EPT entries that allow unauthorized guest access.

## Notes
- EPT page restrictions are separate from guest page protections and can generate independent violations.
- Large page mappings should be handled carefully when walking EPT tables.

## References
- `../patterns/ept-management.md`
- `../knowledge/vmcs-ept.md`

## Related Material

### Knowledge
- [hyper-v-vbs](../knowledge/hyper-v-vbs.md)
- [hypervisor-architecture](../knowledge/hypervisor-architecture.md)
- [virtualization-fundamentals](../knowledge/virtualization-fundamentals.md)

### Patterns
- [ept-management](../patterns/ept-management.md)
- [hypervisor-patterns](../patterns/hypervisor-patterns.md)

### Recipes
- [analyze-hypervisor](analyze-hypervisor.md)
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

