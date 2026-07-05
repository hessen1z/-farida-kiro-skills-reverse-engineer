---
name: Drivers
version: 1.0
priority: critical
requires:
  - shared
  - windows-internals
  - debugging
  - assembly
tags:
  - driver
  - kernel
  - device
description: Core drivers skill covering Windows kernel driver architecture, device dispatch, IRP handling, and driver debugging.
---

# Drivers Skill

## Purpose
Provide a reference skill for analyzing Windows kernel drivers, device objects, IRP flows, and driver lifecycle. This includes driver initialization, dispatch routines, and crash analysis.

## What this skill provides
- Windows driver model fundamentals and kernel interaction.
- Knowledge of driver entry, dispatch, and unload semantics.
- Patterns for IRP handling, device object management, and synchronization.
- Recipes for debugging drivers and analyzing crash dumps.
- References for driver development and reverse engineering.

## Prerequisites
- `shared` for documentation templates.
- `windows-internals` for kernel-mode behavior.
- `debugging` for driver and crash analysis.
- `assembly` for low-level code patterns.

## Used by
- `kernel`
- `anti-cheat`
- `game-security`

## Related Skills
- `windows-internals` — explains driver and kernel abstractions.
- `debugging` — traces driver crashes and kernel events.
- `anti-cheat` — analyzes driver-based enforcement.

## Entry Conditions
- A Windows kernel driver or device issue requires analysis.
- Driver crashes, hangs, or IRP failures are present.
- Device object and dispatch behavior need examination.

## Exit Conditions
- Driver initialization and dispatch semantics are mapped.
- IRP flows and device operations are understood.
- Kernel driver crash or misbehavior is diagnosed.

## Typical Workflow
1. Identify the driver's entry point and device objects.
2. Inspect driver dispatch table and IRP handlers.
3. Analyze synchronization and resource cleanup.
4. Debug crashes using kernel or post-mortem analysis.
5. Document driver lifecycle and failure modes.

## Notes
- Driver analysis often involves both static and live kernel debugging.
- Preserve system stability during driver troubleshooting.

## Related Material

- Knowledge: [driver-model](knowledge/driver-model.md)
- Patterns: [irp-flow](patterns/irp-flow.md)
- Recipes: [analyze-irp](recipes/analyze-irp.md)
- Playbooks: [DriverCrash](playbooks/DriverCrash.md)
- Examples: [driver-entry](examples/driver-entry.md)
- References: [references](references/references.md)
- Prompts: [driver-analysis](prompts/driver-analysis.md)
- Checklists: [checklist](checklists/checklist.md)

