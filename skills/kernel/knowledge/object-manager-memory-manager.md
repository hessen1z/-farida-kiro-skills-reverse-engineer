# Object Manager and Memory Manager Knowledge

## Overview
The Object Manager and Memory Manager are foundational Windows executive services. This document explains object namespace handling, security and handle tables, virtual memory management, and the page fault lifecycle.

## Object Manager

### Namespaces and Object Types
The Object Manager organizes kernel objects into named directories. Each object has an `OBJECT_HEADER`, type descriptor, and optional name information. Important object types include `Process`, `Thread`, `Event`, `Mutant`, `Semaphore`, `File`, `Device`, and `Section`.

### Handle Tables
Each process has a handle table containing `HANDLE_TABLE_ENTRY` structures. Handles are translated to object pointers by `ObReferenceObjectByHandle`, and closing a handle decrements the associated reference count.

### Security and Access Control
Access to objects is mediated by security descriptors and ACLs. The Object Manager checks requested access against the object's type-specific access mask and the caller's security context.

## Memory Manager

### Virtual Address Space
The Memory Manager tracks committed ranges with `MMVAD` structures and enforces page protections through `MMPTE` entries. It also manages working sets and page faults.

### Paging and Page Frame Database
Physical memory is tracked in the PFN database (`MMPFN` entries). Page tables map virtual addresses to physical pages and store access, dirty, and cache type information.

### Pool Allocation
Kernel components use paged and nonpaged pool via `ExAllocatePoolWithTag`. The pool allocator maintains free lists, lookaside lists, and allocation headers to support efficient memory usage.

## Practical Workflows

### Analyze an Object
1. Determine the object address through handle or symbol information.
2. Read the object header and type metadata.
3. Walk the handle table to find references.
4. Inspect the object's lifetime and security descriptors.

### Analyze Virtual Memory
1. Inspect a process’ VAD tree for committed and reserved regions.
2. Examine the corresponding page tables for PTE state.
3. Validate the page fault handler and fault resolution path.

## Common Mistakes
- assuming handle values are stable across reboot or process restart
- ignoring name information blocks in `OBJECT_HEADER`
- treating paged pool as safe at `DISPATCH_LEVEL`
- underestimating the effect of guard pages and copy-on-write semantics

## References
- Windows Internals: Object Manager chapter
- Windows Internals: Memory Manager chapter

## Cross-links
- `../patterns/kernel-objects.md`
- `../patterns/pool-allocations.md`
- `../recipes/analyze-kernel-object.md`
- `../recipes/analyze-memory-manager.md`

## Related Material

### Knowledge
- [handle-tables](handle-tables.md)
- [interrupts-system-calls](interrupts-system-calls.md)
- [irql-apc-dpc](irql-apc-dpc.md)

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

### Checklists
- [checklist](../checklists/checklist.md)

