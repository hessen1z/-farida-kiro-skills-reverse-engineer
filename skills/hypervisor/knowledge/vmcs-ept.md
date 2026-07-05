# VMCS and EPT Knowledge

## Overview
VMCS and EPT are the core hardware structures used by Intel VT-x to manage guest execution and memory virtualization. The VMCS contains guest and host state, while EPT maps guest physical pages to host physical memory.

## VMCS Structure
The VMCS includes:
- guest-state area
- host-state area
- execution control fields
- VM-exit and VM-entry control fields
- VM-exit information fields

### Guest-State Area
Contains registers, segment descriptors, control registers, and system state required to resume guest execution.

### Host-State Area
Contains register values and segment selectors used when the hypervisor regains control.

## VM Execution Controls
Controls determine what events cause VM exits. Important fields include:
- pin-based controls
- processor-based controls
- VM-exit controls
- VM-entry controls

## Extended Page Tables (EPT)
EPT provides hardware-assisted second-level translation from guest physical addresses to host physical addresses. It also enforces memory permissions and page types.

### EPT Structures
- PML4 table
- PDPT
- PD
- PT

EPT entry fields control read/write/execute permissions and memory type attributes.

## Practical Workflows
- inspect VMCS fields to understand why a guest exit occurred
- validate EPT permissions for guest memory access violations
- match guest physical addresses to host physical page frames

## Common Mistakes
- using guest physical addresses directly for host memory analysis
- treating EPT pages as regular guest page tables

## References
- Intel SDM: VMX page 3-xx

## Cross-links
- `../knowledge/virtualization-fundamentals.md`
- `../patterns/ept-management.md`

## Related Material

### Knowledge
- [hyper-v-vbs](hyper-v-vbs.md)
- [hypervisor-architecture](hypervisor-architecture.md)
- [virtualization-fundamentals](virtualization-fundamentals.md)

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

