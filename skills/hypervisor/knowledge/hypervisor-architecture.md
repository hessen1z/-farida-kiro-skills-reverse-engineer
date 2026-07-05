# Hypervisor Knowledge

## Overview
A hypervisor provides a virtualization layer that abstracts CPU, memory, and I/O resources for guest operating systems. In Windows, Hyper-V and Virtualization-Based Security (VBS) leverage processor virtualization extensions to isolate guests and protect sensitive kernel subsystems.

This document explains virtualization fundamentals, Intel VT-x and AMD-V, VMCS/VMCB structures, extended page tables, nested virtualization, and Hyper-V architecture.

## Virtualization Fundamentals

### Basic Concepts
Virtualization separates the guest execution environment from the host. The hypervisor enforces isolation by controlling sensitive instructions, privileged resources, and physical memory access.

Key concepts include:
- **Root mode**: hypervisor control domain
- **Non-root mode**: guest execution domain
- **VM entry/exit**: transitions between guest and host
- **Guest state**: CPU registers, control registers, and virtual memory state

### CPU Virtualization
The CPU presents virtual registers and state to the guest while the hypervisor retains control of actual hardware. Sensitive instructions and events generate VM exits, allowing the hypervisor to emulate or manage the behavior.

### Memory Virtualization
Memory virtualization uses nested mappings to translate guest virtual addresses to host physical addresses. This includes:
- Guest virtual address -> guest physical address
- Guest physical address -> host physical address

Modern processors support second-level address translation through EPT or NPT.

## Intel VT-x

### VMX Operation
Intel VT-x introduces VMX operation and root/non-root modes. A processor enters VMX root mode when a hypervisor executes `VMXON`, and guest execution occurs in VMX non-root mode using `VMLAUNCH` or `VMRESUME`.

### VMCS
The Virtual Machine Control Structure (VMCS) stores guest state, host state, control fields, and VM-exit information. The VMCS includes:
- Guest-state area
- Host-state area
- VM-execution controls
- VM-exit controls
- VM-entry controls
- VM-exit information fields

### VM Entry and VM Exit
- **VM entry** loads guest state from VMCS and begins guest execution.
- **VM exit** saves guest state to the VMCS and loads host state for hypervisor handling.

### EPT
Extended Page Tables map guest physical addresses to host physical addresses. EPT controls memory permissions and can trap guest page table access or execute operations.

## AMD-V

### SVM Operation
AMD-V provides secure virtual machine (SVM) support, including guest/host mode separation and the Virtual Machine Control Block (VMCB). A hypervisor uses `VMSAVE` and `VMLOAD` to manage guest state.

### VMCB Structure
The VMCB contains guest control registers, segment registers, and intercept masks. It also includes exit information and next RIP state.

### NPT
Nested Page Tables provide the second-level translation from guest-physical to host-physical memory. AMD's NPT is the counterpart to Intel EPT.

## VMCS and VMCB Internals

### Guest and Host State
The VMCS/VMCB persists the processor state required for guest operation and the host state needed to resume hypervisor execution. It includes register state, control registers, segment descriptors, descriptor tables, and floating point context flags.

### Control Fields
Control fields determine the conditions that cause VM exits, how interrupts are delivered, and whether certain instructions are trapped. Examples include:
- `pin-based controls`
- `processor-based controls`
- `VM-exit controls`
- `VM-entry controls`

### VM Exit Reasons
Exits occur for events such as:
- CPUID and privileged instructions
- MSR and CR access
- I/O port access
- page faults and EPT violations
- external interrupts and exceptions

## EPT and NPT

### Second-Level Address Translation
EPT/NPT provide hardware-assisted two-level translation. The guest page tables map guest linear addresses to guest physical addresses, while EPT/NPT map those to host physical addresses.

### Page Tables and Permissions
EPT entries include read, write, execute permissions, and page-level memory types. Violations generate EPT misconfigurations or page-walk failures.

### Memory Isolation
Hypervisor memory isolation depends on EPT/NPT to prevent guests from accessing host or other guest memory. This isolation is central to VBS and Secure Kernel protection.

## Nested Virtualization
Nested virtualization allows a guest hypervisor to run its own guests. It requires the host hypervisor to expose virtualization extensions to the guest and to correctly trap nested VMX/SVM instructions.

### Nested VMCS and VMCB
Nested virtualization uses shadow structures or proxy VMCS/VMCB to manage guest state. The hypervisor must emulate nested VM entry and exit behavior while preserving host control.

## Hyper-V Architecture

### Hyper-V Components
Hyper-V includes:
- Partition Manager (`vmwp.exe` and kernel partition manager)
- Virtual Machine Bus (VMBus)
- Hypervisor scheduler
- Secure world/secure kernel domains for VBS

### Partition Model
Hyper-V partitions guest environments and manages communication across VMBus. Each partition maintains security and resource isolation through partition-specific structures and message channels.

### Hypervisor Scheduling
The hypervisor scheduler dispatches virtual processors onto physical CPUs, handling co-scheduling, interrupt injection, and synthetic timer events.

## Virtualization-Based Security (VBS)

### Secure Kernel
VBS hosts the secure kernel in an isolated environment. It protects credentials, platform secrets, and sensitive OS components from compromised kernel or user-mode code.

### Credential Guard
Credential Guard uses VBS to protect secrets such as NTLM hashes and Kerberos tickets. It isolates the Local Security Authority (LSA) and credential material within the secure kernel.

### Memory Isolation
VBS enforces memory isolation between the normal kernel and secure kernel through EPT-based restrictions and guarded memory regions.

## Interrupt Virtualization

### APIC Virtualization
Virtual APICs and interrupt remapping allow the hypervisor to deliver virtual interrupts to guests while retaining control over physical interrupt routing.

### Synthetic Interrupts
Hyper-V provides synthetic interrupt mechanisms to handle virtual device signals without exposing hardware interrupt semantics directly to guests.

## I/O Virtualization

### Device Emulation and Pass-Through
Hypervisors emulate devices or pass through physical hardware. I/O virtualization includes synthetic device channels, virtio-like interfaces, and direct memory access (DMA) management.

### VMBus and Virtual Device Stacks
Virtual devices communicate through VMBus and channel-based message protocols. The hypervisor routes I/O requests between guests and host partitions.

## Timing Virtualization

### Hypervisor Timers
Virtual time is maintained by hypervisor timer facilities. Guests receive timer interrupts and synthetic clocks that must be synchronized with host time.

### Timing Attacks and Countermeasures
Hypervisors must handle timing virtualization carefully to avoid exposing host timing sources or enabling side channel attacks.

## Hypervisor Debugging

### Debugging Models
Debugging a hypervisor involves inspecting VMCS/VMCB state, VM exits, and guest contexts. Tools include hardware-assisted debugging facilities, hypervisor-aware debuggers, and trace logs.

### State Inspection
A hypervisor analyst focuses on VM exit records, guest register state, EPT/NPT mappings, and interrupt virtualization state.

## Performance

### Hypervisor Overhead
Performance depends on VM exit frequency, memory translation overhead, and I/O emulation cost. Reducing unnecessary exits and optimizing EPT/NPT walks is critical.

### Best Practices
- batch I/O operations when possible
- avoid traps on common instructions
- tune EPT permissions for minimal virtualization overhead

## Security

### Hypervisor Attack Surface
Hypervisors must protect management interfaces, VMCS/VMCB structures, and memory isolation. Vulnerabilities often arise from improper VM exit handling or emulation bugs.

### Secure Kernel Isolation
VBS and Secure Kernel provide a strong security boundary by isolating sensitive components from the normal OS. This isolation relies on correct EPT enforcement and hypervisor control of memory mappings.

## Practical Workflows

### Hypervisor Analysis
1. Identify whether the system uses Intel VT-x or AMD-V.
2. Locate VMXON or SVM enablement code paths.
3. Examine VMCS/VMCB structures and control field settings.
4. Analyze VM-exit reasons and memory translation failures.

### VBS and Hyper-V Review
1. Inspect secure kernel load and partition configuration.
2. Verify EPT/NPT policies and guarded memory regions.
3. Correlate guest-visible behavior with hypervisor control decisions.

## Common Mistakes
- Treating guest physical address as host physical address.
- Assuming VMCS contents are static across VM entries.
- Ignoring the distinction between guest state and host state.
- Failing to account for synthetic interrupt paths in Hyper-V.

## References
- Intel 64 and IA-32 Architectures Software Developer’s Manual
- AMD64 Architecture Programmer’s Manual
- Microsoft Hyper-V Architecture Documentation
- Windows Internals by Russinovich, Solomon, and Ionescu

## Cross-links
- `../patterns/hypervisor-patterns.md`
- `../recipes/analyze-hypervisor.md`
- `../playbooks/analyze-hypervisor.md`

## Related Material

### Knowledge
- [hyper-v-vbs](hyper-v-vbs.md)
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

