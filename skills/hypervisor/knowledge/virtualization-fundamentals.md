# Virtualization Fundamentals

## Overview
Virtualization creates an abstraction layer between physical hardware and guest software. It enables multiple guest operating systems to run concurrently on the same hardware while enforcing isolation and managing shared resources.

## Core Concepts
- **Host**: the physical machine running the hypervisor.
- **Guest**: a virtual machine instance running an operating system.
- **Hypervisor**: the software or firmware that controls guest execution.
- **Root mode**: the hypervisor execution environment with full control.
- **Non-root mode**: guest execution environment restricted by the hypervisor.

## Virtual CPU and Memory
Virtualization exposes a virtual CPU to each guest, with trap-and-emulate semantics for privileged instructions. Memory virtualization maps guest physical addresses to host physical addresses using second-level translation.

## VM Entry and VM Exit
- **VM entry**: transitioning from host to guest execution.
- **VM exit**: transferring control from guest to hypervisor in response to traps or events.
- VM exits parameterize reasons such as I/O, interrupts, or control register access.

## Internal Architecture
The hypervisor maintains state for each virtual processor and guest partition. It manages:
- processor state save/restore
- VM control structures (VMCS or VMCB)
- nested page tables (EPT/NPT)
- virtual devices and interrupt routing

## Practical Workflows
- identify whether hardware virtualization is enabled by checking VMXON or SVM enablement
- inspect VM entry/exit controls to understand guest trapping policy
- map guest physical memory through EPT/NPT translations

## Common Mistakes
- confusing guest physical addresses with host physical addresses
- assuming every privileged instruction triggers a VM exit
- ignoring the cost of VM exits when evaluating performance

## References
- Intel SDM Vol. 3C: VMX operation
- AMD AMD64 Architecture Programmer’s Manual Volume 2

## Cross-links
- `../knowledge/vmcs-ept.md`
- `../knowledge/hyper-v-vbs.md`
- `../patterns/hypervisor-patterns.md`

## Related Material

### Knowledge
- [hyper-v-vbs](hyper-v-vbs.md)
- [hypervisor-architecture](hypervisor-architecture.md)
- [vmcs-ept](vmcs-ept.md)

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

### Rules
- [hypervisor-guidelines](../rules/hypervisor-guidelines.md)

### Prompts
- [hypervisor-analysis](../prompts/hypervisor-analysis.md)
- [vbs-analysis](../prompts/vbs-analysis.md)
- [vmcs-analysis](../prompts/vmcs-analysis.md)

### Checklists
- [checklist](../checklists/checklist.md)

