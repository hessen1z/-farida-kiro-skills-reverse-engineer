---
title: SSDT Usage Pattern
skill: kernel
category: patterns
difficulty: intermediate
tags: [pe, windows, gui, kernel, debug]
updated: 2026-07-05
---
# SSDT Usage Pattern

## Pattern Name
SSDT Usage

## Problem
Recognize usage of the System Service Descriptor Table and its impact on system calls, hooks, and kernel security.

## Context
The SSDT maps system call indices to kernel service routines. On 64-bit Windows, the shadow SSDT extends this concept for WOW64 processes.

## Recognition
- references to `KeServiceDescriptorTable` or `KeServiceDescriptorTableShadow`
- system call stubs using `syscall` or `sysenter`
- checks for `SSDT` pointer tables in kernel memory
- common hooks that modify SSDT entries or shadow transitions

## Evidence
- `!kd` and `!ssdt` output showing service indexes and function addresses
- call stack entries that resolve to `Nt*` or `Zw*` services in the kernel
- system call dispatch logic captured in assembly or kernel exports

## Resolution / Action
- verify whether a suspected hook modifies SSDT entries and whether the original function pointers are preserved
- inspect system call entry and exit control flow for proper context switching
- confirm service dispatch via kernel symbol resolution

## Notes
- 64-bit Windows uses `syscall` for native calls and `sysenter` for WOW64 transitions; the shadow SSDT is specific to 32-bit guest compatibility.
- SSDT hooks are typically kernel-rootkit techniques and should be evaluated carefully in a security context.

## References
- Windows Internals: System Call chapter

## See Also
- `../recipes/analyze-ssdt.md`
- `../patterns/interrupt-handler.md`
- `../examples/kernel-debugging.md`

## Related Material

### Knowledge
- [handle-tables](../knowledge/handle-tables.md)
- [interrupts-system-calls](../knowledge/interrupts-system-calls.md)
- [irql-apc-dpc](../knowledge/irql-apc-dpc.md)

### Patterns
- [dispatcher-routines](dispatcher-routines.md)
- [kernel-objects](kernel-objects.md)
- [pool-allocations](pool-allocations.md)

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

### Checklists
- [checklist](../checklists/checklist.md)

