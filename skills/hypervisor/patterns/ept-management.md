# EPT Management Pattern

## Pattern Name
EPT Management

## Problem
Identify and analyze EPT page table structures and memory access violations in a virtualized environment.

## Context
EPT provides second-level address translation for guest physical memory. It enforces page permissions and isolates guest memory from the host.

## Recognition
- EPT violation VM exits
- EPT page table entries with R/W/X bits and memory type fields
- `EPTP` values in VMCS and related control structures
- guest physical address to host physical address translation errors

## Evidence
- VM exit reason for EPT violation or misconfiguration
- page walk faults in second-level translation
- invalid guest memory accesses trapped by the hypervisor

## Resolution / Action
- validate EPT entries for the accessed guest physical page
- verify that host physical mappings are consistent and not stale
- confirm the guest and host memory types match intended isolation policies

## Notes
- EPT violations may occur even when the guest page tables appear valid.
- Nested virtualization adds complexity by requiring guest second-level translation to be emulated or shadowed.

## References
- Intel SDM: EPT and virtualization memory management

## See Also
- `../recipes/analyze-ept.md`

## Related Material

### Knowledge
- [hyper-v-vbs](../knowledge/hyper-v-vbs.md)
- [hypervisor-architecture](../knowledge/hypervisor-architecture.md)
- [virtualization-fundamentals](../knowledge/virtualization-fundamentals.md)

### Patterns
- [hypervisor-patterns](hypervisor-patterns.md)

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

