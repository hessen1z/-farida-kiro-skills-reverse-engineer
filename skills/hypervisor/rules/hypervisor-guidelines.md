# Hypervisor Rules

## Rule: Respect Hardware Controls
- Always interpret VMCS and VMCB fields against the CPU vendor documentation.
- Do not assume control bits behave identically between Intel and AMD.

## Rule: Separate Security and Performance
- Analyze VM exit frequency independently from correctness.
- Avoid optimizing away security checks in favor of lower exit rates.

## Rule: Preserve Guest State
- Hypervisor analysis must ensure guest state is restored accurately after handling exits.
- Document any state changes introduced by emulation.

## Rule: Verify Memory Isolation
- Confirm that EPT/NPT mappings enforce the intended access restrictions.
- Treat any guest visibility into host memory as a severe issue.

## Rule: Avoid Nested Virtualization Assumptions
- Do not assume nested virtualization uses the same VMCS semantics as a base-level guest.
- Evaluate shadow paging and nested control structures separately.

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
- [analyze-hyper-v](../playbooks/analyze-hyper-v.md)
- [analyze-hypervisor](../playbooks/analyze-hypervisor.md)
- [analyze-vbs](../playbooks/analyze-vbs.md)

### Examples
- [ept-layout](../examples/ept-layout.md)
- [vm-entry-exit](../examples/vm-entry-exit.md)

### References
- [references](../references/references.md)

### Prompts
- [hypervisor-analysis](../prompts/hypervisor-analysis.md)
- [vbs-analysis](../prompts/vbs-analysis.md)
- [vmcs-analysis](../prompts/vmcs-analysis.md)

### Checklists
- [checklist](../checklists/checklist.md)

