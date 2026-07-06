---
title: Switch Table Pattern
skill: binary-analysis
category: patterns
difficulty: intermediate
tags: [pe, elf]
updated: 2026-07-05
---
# Switch Table Pattern

## Overview

Switch tables implement multi-way branching using jump tables. They appear in compiler-generated code for `switch` statements and are often reused by obfuscation techniques.

## Detection

Look for:
- indirect jumps whose target is computed from a base address plus an index
- a table of contiguous addresses or offsets in a nearby data section
- blocks that normalize a value and bounds-check it before the jump

## Analysis steps

1. locate the jump table base
   - follow the instruction that computes the target address
   - verify the candidate table contains valid RVAs or pointers

2. recover case targets
   - extract table entries into a list of target addresses
   - annotate the switch’s range, default target, and case values

3. map source values to destinations
   - reverse the index computation and bounds checks
   - name cases based on target function semantics or string references

4. use the switch structure in decompilation
   - leverage recovered targets to express the branch as a high-level `switch`
   - simplify flattened or obfuscated control flow that uses dispatcher tables

## Practical notes

- Compilers may encode jump tables as signed or unsigned offsets; verify the instruction mode and sign extension.
- Some obfuscators insert dummy entries or extra bounds checks to confuse static analysis.

## Cross-links

- `../knowledge/decompilers.md`
- `../patterns/obfuscated-jump.md`
- `../recipes/analyze-binary.md`

## Related Material

### Knowledge
- [decompilers](../knowledge/decompilers.md)
- [demangling](../knowledge/demangling.md)
- [disassemblers](../knowledge/disassemblers.md)

### Patterns
- [encrypted-string](encrypted-string.md)
- [export-table](export-table.md)
- [import-table](import-table.md)

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

