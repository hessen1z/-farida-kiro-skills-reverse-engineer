---
title: Kernel Checklist
skill: kernel
category: checklists
difficulty: intermediate
tags: [pe, gui, kernel, debug]
updated: 2026-07-05
---
# Kernel Checklist

## Preparation
- [ ] Identify kernel module versions and symbol paths.
- [ ] Determine whether analysis uses a dump or live debugging session.
- [ ] Locate relevant `EPROCESS`, `ETHREAD`, `KTHREAD`, and `IRP` structures.

## Analysis
- [ ] Inspect the bug check code and faulting address.
- [ ] Verify IRQL at the fault or wait site.
- [ ] Examine kernel objects and handle references.
- [ ] Inspect pool allocations and page table state.
- [ ] Review scheduler and DPC activity.
- [ ] Validate SSDT and system call dispatch path if relevant.

## Validation
- [ ] Confirm the root cause against kernel symbols and known system behavior.
- [ ] Verify whether memory corruption is primary or secondary.
- [ ] Document the kernel subsystem and recommended remediation.
- [ ] Cross-link findings to patterns, recipes, and examples.

## Notes
- [ ] Avoid changing live kernel state unless necessary.
- [ ] Respect IRQL and synchronization constraints during analysis.
- [ ] Use production-quality command sequences and structured evidence.

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
- [analyze-kernel-component](../recipes/analyze-kernel-component.md)
- [analyze-kernel-object](../recipes/analyze-kernel-object.md)
- [analyze-memory-manager](../recipes/analyze-memory-manager.md)

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

