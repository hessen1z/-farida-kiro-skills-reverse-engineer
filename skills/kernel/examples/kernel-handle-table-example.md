---
title: Kernel Handle Table Example
skill: kernel
category: examples
difficulty: intermediate
tags: [pe, gui, kernel, debug]
updated: 2026-07-05
---
# Kernel Handle Table Example

## Scenario
Trace a process handle table entry and verify object ownership in a memory dump.

## Steps
1. Identify the process from its `EPROCESS` structure.
2. Inspect the process handle table using debugger extensions.
3. Translate a handle value to an `OBJECT_HEADER` and object pointer.
4. Verify the access mask and reference count.

## Example
WinDbg commands:
```text
!process 0 0
!handle <HandleValue> 1
!object <ObjectAddress>
```

## Outcome
- Mapped the handle to the underlying object and process ownership
- Confirmed whether the handle was inherited or created in the current process
- Identified any stale handles or lingering references affecting cleanup

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
- [kernel-memory-inspection](kernel-memory-inspection.md)

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
## Practical Guidance

- Start from the concrete objective and define the expected outcome before applying the workflow.
- Use the related examples, recipes, playbooks, and references as the first implementation reference.
- Keep the guidance grounded in the surrounding skill context and verify the result with available evidence.
- Favor practical, maintainable steps over abstract theory when the document is used in real work.
## Verification Checklist

- Confirm that the main objective is clear and the workflow is actionable.
- Ensure the document points to the most relevant examples, recipes, or playbooks.
- Validate that the terminology is consistent with the rest of the skill.
- Check that the practical guidance is specific enough to be used without further interpretation.
