---
name: Hypervisor
version: 1.0
priority: critical
requires:
  - shared
  - windows-internals
  - assembly
tags:
  - virtualization
  - hypervisor
  - security
description: Core hypervisor skill covering virtualization fundamentals, VMX/NPT/EPT, Hyper-V architecture, VBS, and hypervisor debugging.
---

# Hypervisor Skill

## Purpose
Provide a production-grade reference for hypervisor architecture, virtualization internals, VMCS/VMCB semantics, and virtualization-based security. This skill bridges CPU and memory virtualization concepts with Hyper-V and VBS analysis.

## What this skill provides
- Knowledge of virtualization fundamentals, Intel VT-x, AMD-V, VM entry/exit, and nested virtualization.
- Patterns for VM exit handlers, VMCS/VMCB access, EPT/NPT management, and virtualization assembly idioms.
- Recipes for analyzing hypervisors, VM exit behavior, EPT mappings, VBS, and Hyper-V components.
- Playbooks for hypervisor analysis, Hyper-V evaluation, VBS validation, and secure kernel inspection.
- Examples for VMX assembly, hypervisor memory layouts, and virtualization debugging.

## Prerequisites
- `shared` for documentation conventions.
- `windows-internals` for OS and CPU architecture context.
- `assembly` for virtualization instruction-level patterns.

## Used by
- `kernel`
- `cryptography`
- `networking`
- `system-design`

## Related Skills
- `windows-internals` — CPU mode transitions and privilege boundaries.
- `assembly` — VMX instructions, MSRs, and virtualization registers.
- `kernel` — hypervisor interactions with kernel and memory subsystems.

## Entry Conditions
- A hypervisor or virtualization environment must be analyzed.
- VM exits, EPT/NPT issues, or secure kernel protection are present.
- Hyper-V, VBS, or nested virtualization behavior is relevant.

## Exit Conditions
- Virtualization state is mapped to VMCS/VMCB and EPT/NPT structures.
- VM entry/exit behavior and hypervisor security controls are documented.
- Practical hypervisor debugging workflows are defined.

## Typical Workflow
1. Identify the hypervisor type and virtualization extensions in use.
2. Map VMCS or VMCB structures and translation tables.
3. Analyze VM exit reasons and hypervisor dispatch paths.
4. Verify EPT/NPT, APIC virtualization, and memory isolation boundaries.
5. Document findings and cross-link to secure kernel and VBS patterns.

## Notes
- Virtualization analysis requires both CPU and memory model knowledge.
- Hypervisor security is layered: hardware, firmware, and software controls combine to isolate guests.

## Related Material

- Knowledge: [hyper-v-vbs](knowledge/hyper-v-vbs.md)
- Patterns: [ept-management](patterns/ept-management.md)
- Recipes: [analyze-ept](recipes/analyze-ept.md)
- Playbooks: [analyze-hyper-v](playbooks/analyze-hyper-v.md)
- Examples: [ept-layout](examples/ept-layout.md)
- References: [references](references/references.md)
- Rules: [hypervisor-guidelines](rules/hypervisor-guidelines.md)
- Prompts: [hypervisor-analysis](prompts/hypervisor-analysis.md)
- Checklists: [checklist](checklists/checklist.md)

