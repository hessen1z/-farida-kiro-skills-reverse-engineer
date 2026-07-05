# VM Entry/Exit Example

## Scenario
Inspect VM entry and exit behavior in an Intel VT-x hypervisor implementation.

## Steps
1. Capture the VM exit reason and qualification fields.
2. Disassemble the guest instruction stream at the exit RIP.
3. Examine the VMCS guest-state and host-state fields.
4. Validate the hypervisor’s VM exit handler logic.

## Example
The hypervisor handles a VM exit due to `CPUID` as follows:
```asm
vmexit_handler:
    pushfq
    push rax
    push rcx
    push rdx
    ; decode exit reason
    mov eax, [vmcs + EXIT_REASON]
    cmp eax, EXIT_REASON_CPUID
    jne other_exit
    ; emulate CPUID for guest
    ; restore registers and resume
    vmresume
```

## Outcome
- identified the VM exit source
- validated the guest state preservation and resume path
- recorded the hypervisor control fields responsible for trapping the instruction

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
- [ept-layout](ept-layout.md)

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

