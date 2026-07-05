# Hyper-V and VBS Knowledge

## Overview
Hyper-V is Microsoft’s hardware-assisted hypervisor for Windows. Virtualization-Based Security (VBS) leverages Hyper-V to isolate sensitive OS components, enforce secure kernel boundaries, and protect credentials.

## Hyper-V Architecture
Hyper-V organizes execution into partitions and virtual processors. Key components include:
- Partition Manager
- Hypervisor scheduler
- VMBus communication layer
- Synthetic device stack

### Partition Model
Each guest runs in a partition with isolated memory, CPU scheduling, and device namespaces.

### VMBus
VMBus provides a high-performance channel for guest-host communication and synthetic devices.

## Virtualization-Based Security

### Secure Kernel
Secure Kernel runs inside a VBS-protected environment and isolates critical OS components from the main kernel.

### Credential Guard
Credential Guard stores secrets in the secure kernel and isolates them from compromised code.

### Memory Isolation
VBS uses EPT to separate normal kernel memory from secure kernel memory.

## Practical Workflows
- identify whether VBS is enabled through registry and system configuration
- inspect secure kernel status and partition state
- verify guarded memory regions and partition isolation

## Common Mistakes
- confusing Hyper-V partitions with Windows user-mode containers
- assuming normal kernel memory protections extend to secure kernel memory

## References
- Microsoft Hyper-V architecture guides
- Microsoft VBS and Credential Guard documentation

## Cross-links
- `../knowledge/virtualization-fundamentals.md`
- `../patterns/vbs-patterns.md`

## Related Material

### Knowledge
- [hypervisor-architecture](hypervisor-architecture.md)
- [virtualization-fundamentals](virtualization-fundamentals.md)
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

