---
title: Analyze Kernel Object Recipe
skill: kernel
category: recipes
difficulty: intermediate
tags: [pe, windows, gui, kernel, debug]
updated: 2026-07-05
---
# Analyze Kernel Object Recipe

## Purpose
Analyze a Windows kernel object to understand its type, handle relationships, security, and lifetime.

## Prerequisites
- Access to kernel debugging symbols.
- Familiarity with `OBJECT_HEADER`, handle tables, and object types.
- Ability to inspect kernel memory and handle counts.

## Inputs
- object address or handle value.
- object type and associated metadata.
- reference counts and access masks.

## Steps
1. Locate the object header and determine the object type.
2. Inspect the `OBJECT_HEADER_NAME_INFO` and security descriptor if present.
3. Walk handle tables in the owning process to find references.
4. Examine the object's body for type-specific state.
5. Check reference count and deletion state.

## Verification
- Confirm the object's type and whether it is still valid.
- Verify there are no leaked handles or stale references.
- Document access control and ownership boundaries.

## Notes
- Object headers may include optional info blocks that shift the object body.
- Handle table entries can remain even after object deletion if the handle has not been closed.

## References
- `../knowledge/kernel-architecture.md`
- `../patterns/kernel-objects.md`
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
- [analyze-memory-manager](analyze-memory-manager.md)
- [analyze-scheduler](analyze-scheduler.md)

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

