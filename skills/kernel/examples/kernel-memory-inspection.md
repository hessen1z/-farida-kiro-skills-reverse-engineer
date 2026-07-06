---
title: Kernel Memory Inspection Example
skill: kernel
category: examples
difficulty: intermediate
tags: [pe, driver, gui, kernel, debug]
updated: 2026-07-05
---
# Kernel Memory Inspection Example

## Scenario
Inspect kernel memory allocation and page table state to diagnose corruption and invalid mappings.

## Steps
1. In WinDbg, examine the page table state for the faulting address:
```text
!pte <Address>
```
2. Review the pool tag and allocation site:
```text
!poolfind <Address>
!pool 2 <Tag>
```
3. Inspect the owning driver and object state:
```text
!object 
!for_each_module ".foreach (obj { .shell -ci \"!object \" }) { .echo ${obj} }"
```
4. Trace the memory allocation lifetime and identify invalid frees.

## Outcome
- Mapped the offending memory to a kernel allocation.
- Verified whether the allocation belonged to paged or nonpaged pool.
- Identified the allocation tag and potential driver owner.

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
- [kernel-apc-dpc-example](kernel-apc-dpc-example.md)
- [kernel-debugging](kernel-debugging.md)
- [kernel-handle-table-example](kernel-handle-table-example.md)

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

