# Decompilers

## Overview

Decompilers attempt to reconstruct high-level code from compiled binaries. They are a vital complement to disassembly, providing readable control flow, types, and program structure.

## Internal Design

Decompilers typically perform:
- Control flow graph reconstruction
- Type inference
- Data flow analysis
- Expression simplification
- Program reconstruction

## Reverse Engineering Notes

- Decompiler output is an approximation of source code.
- Always validate decompiled results against the original assembly.

## Debugging Notes

- Decompiled code may omit compiler optimizations and inline expansions.

## Common Mistakes

- Treating decompiled output as exact source code.

## References

- Ghidra, IDA, Hex-Rays architecture

## Related Material

### Knowledge
- [demangling](demangling.md)
- [disassemblers](disassemblers.md)
- [dwarf](dwarf.md)

### Patterns
- [encrypted-string](../patterns/encrypted-string.md)
- [export-table](../patterns/export-table.md)
- [import-table](../patterns/import-table.md)

### Recipes
- [analyze-binary](../recipes/analyze-binary.md)
- [recover-exports](../recipes/recover-exports.md)
- [recover-imports](../recipes/recover-imports.md)

### Playbooks
- [analyze-elf](../playbooks/analyze-elf.md)
- [analyze-packed-binary](../playbooks/analyze-packed-binary.md)
- [analyze-pe](../playbooks/analyze-pe.md)

### References
- [elf](../references/elf.md)
- [intel](../references/intel.md)
- [microsoft](../references/microsoft.md)

### Rules
- [rule](../rules/rule.md)

### Prompts
- [analyze-binary](../prompts/analyze-binary.md)

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
