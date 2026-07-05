# Disassemblers

## Overview

Disassemblers convert machine code back into assembly instructions. They are foundational tools for binary analysis, enabling analysts to inspect program behavior, locate functions, and identify patterns.

## Internal Design

Disassemblers parse binary data into instruction mnemonic, operands, and addressing modes. Advanced disassemblers also perform:
- Function boundary detection
- Control flow graph construction
- Data flow analysis
- Signature matching

## Data Structures

- Instruction metadata tables
- Address-to-instruction mapping
- Control flow graphs

## Important APIs

### `Capstone`, `Zydis`, `BeaEngine`
Libraries commonly used for disassembly tasks in analysis tools.

## Reverse Engineering Notes

- Correct disassembly depends on the correct architecture, mode, and code section boundaries.
- Mixed code/data regions require manual analysis and pattern recognition.

## Debugging Notes

- Disassemblers are used to translate instruction pointers and memory dumps into human-readable form.

## Performance Notes

- Fast disassembly is critical for interactive analysis, but accuracy is paramount.

## Common Mistakes

- Disassembling data as code and misinterpreting instructions.

## References

- Capstone Engine
- Intel/AMD instruction set references

## Related Material

### Knowledge
- [decompilers](decompilers.md)
- [demangling](demangling.md)
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

