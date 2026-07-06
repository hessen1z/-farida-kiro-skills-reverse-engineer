---
title: Kernel References
skill: kernel
category: references
difficulty: intermediate
tags: [pe, windows, driver, gui, kernel, debug]
updated: 2026-07-05
---
# Kernel References

- Microsoft Windows Internals by Mark Russinovich, David Solomon, and Alex Ionescu
- Microsoft Windows Driver Kit (WDK) documentation
- Microsoft Windows Kernel-Mode Driver Architecture (KMDF) documentation
- Microsoft Debugging Tools for Windows documentation
- Intel 64 and IA-32 Architectures Software Developer’s Manual
- AMD64 Architecture Programmer’s Manual
- NT Insider and OSR Online articles on kernel debugging and kernel-mode programming

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
