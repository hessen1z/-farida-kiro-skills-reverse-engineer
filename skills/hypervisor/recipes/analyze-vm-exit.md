# Analyze VM Exit Recipe

## Purpose
Analyze a VM exit to determine why guest execution transferred to the hypervisor and how the exit should be handled.

## Prerequisites
- knowledge of VM exit reasons and VMCS/VMCB layout.
- access to exit logs or hypervisor debugging output.
- familiarity with guest execution semantics.

## Inputs
- exit reason and qualification fields.
- guest instruction pointer and control register state.
- relevant VMCS/VMCB fields.

## Steps
1. Read the VM exit reason and interpret it against the hypervisor configuration.
2. Examine the exit qualification and guest state.
3. Determine whether the exit was caused by instruction emulation, access violation, or interrupt delivery.
4. Validate the hypervisor’s response path and whether the guest state is preserved.

## Verification
- Confirm the exit reason matches the observed guest action.
- Verify the guest can resume correctly after the hypervisor handles the exit.
- Identify any unexpected or frequent exits that indicate performance or correctness issues.

## Notes
- some exits are expected and inexpensive, while others signal serious performance or security concerns.
- nested virtualization can produce additional VM exit layers.

## References
- `../patterns/hypervisor-patterns.md`
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

