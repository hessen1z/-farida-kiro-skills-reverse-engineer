---
title: Pool Allocations Pattern
skill: kernel
category: patterns
difficulty: intermediate
tags: [pe, windows, driver, gui, kernel, debug]
updated: 2026-07-05
---
# Pool Allocations Pattern

## Pattern Name
Pool Allocations

## Problem
Detect and analyze kernel pool allocation patterns, tagging, and memory lifetime.

## Context
Kernel-mode components allocate paged and nonpaged pool for objects, buffers, and metadata. Pool tagging and lookaside lists are essential for diagnosing leaks and lifecycle issues.

## Recognition
- calls to `ExAllocatePoolWithTag`, `ExAllocatePoolWithTagPriority`, `ExFreePoolWithTag`
- pool tags visible in memory and debugger output
- paged vs nonpaged pool usage depending on IRQL and paging constraints
- lookaside allocation patterns for small or fixed-size objects

## Evidence
- `!pool` or `!poolused` output showing tags, allocation sizes, and pool types
- memory corruption signatures near pool headers or free list entries
- object lifetimes tied to handle closure and reference count release

## Resolution / Action
- classify allocations by tag and IRQL suitability
- check whether nonpaged pool is used for data accessible at `DISPATCH_LEVEL`
- identify pool leaks through repeated tag allocation without matching frees

## Notes
- Paged pool cannot be accessed at `DISPATCH_LEVEL`; nonpaged pool must be used for interrupt-time data.
- Pool tag conventions are critical for debugging production drivers and kernel components.

## References
- Windows Internals: Memory Manager and Pool chapter

## See Also
- `../recipes/analyze-memory-manager.md`
- `../examples/kernel-memory-inspection.md`

## Related Material

### Knowledge
- [handle-tables](../knowledge/handle-tables.md)
- [interrupts-system-calls](../knowledge/interrupts-system-calls.md)
- [irql-apc-dpc](../knowledge/irql-apc-dpc.md)

### Patterns
- [dispatcher-routines](dispatcher-routines.md)
- [kernel-objects](kernel-objects.md)
- [ssdt-usage](ssdt-usage.md)

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

