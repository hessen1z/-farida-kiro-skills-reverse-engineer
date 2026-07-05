# Obfuscated Jump Pattern

## Overview

Obfuscated jumps disrupt normal control flow by using indirect branches, opaque predicates, and dispatcher loops. This pattern is common in binary protectors, virtualized code, and obfuscated logic.

## Detection

Look for:
- a high density of indirect jumps or calls
- computed branch targets based on register values or memory loads
- small dispatcher blocks that route control to many destinations
- repetitive basic blocks with only a single conditional or indirect transfer

## Analysis steps

1. identify the dispatcher or jump table
   - trace how the branch target is computed
   - locate the table or state variable used to select the target

2. recover the dispatch map
   - if a table is used, extract entries
   - if a state machine is used, model the transitions

3. normalize control flow
   - annotate indirect branches with their resolved targets
   - collapse dispatcher loops into higher-level switch or branch semantics

4. validate with execution traces
   - use dynamic tracing to confirm which targets are taken at runtime
   - distinguish real control flow from dead or anti-analysis branches

## Practical notes

- Obfuscated jump patterns are often layered on top of other protections like encrypted code or opaque predicates.
- Tools may misidentify dispatcher blocks as data; manual analysis of the branch computation is essential.

## Cross-links

- `../knowledge/obfuscation.md`
- `../knowledge/decompilers.md`
- `../generators/memory-analysis`

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

