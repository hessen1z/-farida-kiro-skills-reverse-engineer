---
name: Kernel
version: 1.0
priority: critical
requires:
  - shared
  - windows-internals
  - debugging
tags:
  - kernel
  - windows
  - architecture
description: Core Windows kernel skill covering kernel architecture, execution, memory, synchronization, I/O, and kernel debugging.
---

# Kernel Skill

## Purpose
Provide a production-quality reference for Windows kernel architecture, core subsystems, synchronization primitives, and kernel debugging. This skill focuses on the internal structure of the executive, scheduler, memory manager, and I/O stack while mapping theory to practical workflows and code-level inspection.

## What this skill provides
- Knowledge of Windows kernel architecture, dispatcher behavior, IRQL, APC/DPC, system calls, and executive subsystems.
- Patterns for kernel objects, dispatcher routines, synchronization primitives, SSDT usage, pool allocation, interrupt handling, and scheduler behavior.
- Recipes for analyzing kernel components, memory management, scheduler decisions, SSDT hooks, and kernel objects.
- Playbooks for Windows kernel analysis, crash investigation, memory review, and executive component inspection.
- Examples for kernel debugging, WinDbg workflows, and C++ kernel-mode artifacts.

## Prerequisites
- `shared` for documentation conventions.
- `windows-internals` for low-level OS behavior.
- `debugging` for kernel crash and live analysis.

## Used by
- `drivers`
- `anti-cheat`
- `hypervisor`
- `game-security`

## Related Skills
- `windows-internals` — kernel abstractions and memory management.
- `debugging` — crash analysis and live kernel inspection.
- `drivers` — driver interaction with kernel subsystems.

## Entry Conditions
- A Windows kernel component or driver requires analysis.
- A system crash or kernel memory issue is present.
- Kernel-level synchronization, IRQL, or dispatch path behavior is relevant.

## Exit Conditions
- Kernel subsystems are mapped to their internal data structures.
- Dispatch, scheduling, and memory behavior are documented.
- Kernel debugging workflows and expected failure modes are understood.

## Typical Workflow
1. Identify the kernel subsystem or driver entry point under analysis.
2. Map the relevant object types and IRQL boundaries.
3. Inspect dispatcher and scheduler state in kernel memory or crash dumps.
4. Verify memory management and pool allocation behavior.
5. Document the kernel evidence and cross-link to patterns and recipes.

## Notes
- The Windows kernel is not monolithic; analysis requires subsystem-aware inspection.
- Always respect IRQL and synchronization rules when reasoning about kernel behavior.

## Related Material

- Knowledge: [handle-tables](knowledge/handle-tables.md)
- Patterns: [dispatcher-routines](patterns/dispatcher-routines.md)
- Recipes: [analyze-kernel-component](recipes/analyze-kernel-component.md)
- Playbooks: [analyze-executive-components](playbooks/analyze-executive-components.md)
- Examples: [kernel-apc-dpc-example](examples/kernel-apc-dpc-example.md)
- References: [references](references/references.md)
- Rules: [kernel-guidelines](rules/kernel-guidelines.md)
- Prompts: [kernel-analysis](prompts/kernel-analysis.md)
- Checklists: [checklist](checklists/checklist.md)

