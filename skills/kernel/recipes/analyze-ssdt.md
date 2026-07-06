---
title: Analyze SSDT Recipe
skill: kernel
category: recipes
difficulty: intermediate
tags: [pe, windows, driver, gui, kernel, debug]
updated: 2026-07-05
---
# Analyze SSDT Recipe

## Purpose
Analyze System Service Descriptor Table usage, system call dispatch, and potential kernel-mode hooking.

## Prerequisites
- Kernel symbols and access to a kernel dump or live debugger.
- Knowledge of system call entry/exit semantics.
- Familiarity with `KeServiceDescriptorTable` and shadow SSDT.

## Inputs
- SSDT and shadow SSDT table addresses.
- system call index and handler pointers.
- service dispatch flow and call stacks.

## Steps
1. Locate `KeServiceDescriptorTable` and `KeServiceDescriptorTableShadow` in kernel memory.
2. Enumerate system call table entries and validate function addresses.
3. Compare current entries with expected kernel module exports.
4. Trace system call dispatch from user-mode stub to kernel service routine.
5. Identify any modifications, hooks, or redirections.

## Verification
- Confirm system call table entries point to valid kernel services.
- Verify shadow SSDT entries for WOW64 compatibility.
- Document any unexpected kernel hooks or altered service dispatch paths.

## Notes
- 64-bit Windows treats SSDT hooks as a security risk and may trigger driver signing enforcement if modified.
- Shadow SSDT is specific to 32-bit compatibility layers and is not used for native 64-bit system calls.

## References
- `../knowledge/kernel-architecture.md`
- `../patterns/ssdt-usage.md`
- `../examples/kernel-debugging.md`

## Related Material

### Knowledge
- [handle-tables](../knowledge/handle-tables.md)
- [interrupts-system-calls](../knowledge/interrupts-system-calls.md)
- [irql-apc-dpc](../knowledge/irql-apc-dpc.md)

### Patterns
- [dispatcher-routines](../patterns/dispatcher-routines.md)
- [kernel-objects](../patterns/kernel-objects.md)
- [pool-allocations](../patterns/pool-allocations.md)

### Recipes
- [analyze-kernel-component](analyze-kernel-component.md)
- [analyze-kernel-object](analyze-kernel-object.md)
- [analyze-memory-manager](analyze-memory-manager.md)

### Playbooks
- [analyze-executive-components](../playbooks/analyze-executive-components.md)
- [analyze-kernel-crash](../playbooks/analyze-kernel-crash.md)
- [analyze-kernel-memory](../playbooks/analyze-kernel-memory.md)

### Examples
- [kernel-apc-dpc-example](../examples/kernel-apc-dpc-example.md)
- [kernel-debugging](../examples/kernel-debugging.md)
- [kernel-handle-table-example](../examples/kernel-handle-table-example.md)

### References
- [references](../references/references.md)

### Rules
- [kernel-guidelines](../rules/kernel-guidelines.md)

### Prompts
- [kernel-analysis](../prompts/kernel-analysis.md)
- [kernel-debugging-prompt](../prompts/kernel-debugging-prompt.md)
- [kernel-memory-analysis](../prompts/kernel-memory-analysis.md)

### Checklists
- [checklist](../checklists/checklist.md)

