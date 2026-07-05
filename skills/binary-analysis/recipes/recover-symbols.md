# Recover Symbols Recipe

## Goal

Recover symbol names and metadata for a binary that is missing debug symbols or has been stripped.

## Steps

1. Collect available metadata
   - parse export and import tables
   - inspect debug directories for PDB or CodeView information
   - check for RTTI, typeinfo, and vtable data

2. Use PDB or external symbol sources
   - if a matching PDB exists, load it using DbgHelp or DIA
   - retrieve public symbols and, when available, private symbols

3. Recover symbols heuristically
   - use RTTI names and type information to reconstruct C++ class methods
   - identify known library functions by signature and prolog patterns
   - annotate entry points and call targets based on string references and API usage

4. Populate a symbol map
   - annotate functions, data structures, and imported APIs
   - attach confidence levels for recovered names
   - preserve original addresses and add recovered names as metadata

5. Validate recovered symbols
   - compare against runtime call stacks or crash dumps to verify name accuracy
   - review demangled names for correctness

## Notes

- Full symbol recovery is often impossible in release builds, but partial recovery is still extremely valuable.
- Prioritize public exports and known API names before attempting complex heuristics.

## Cross-links

- `../knowledge/symbols.md`
- `../knowledge/demangling.md`
- `../recipes/recover-pdb.md`

## Related Material

### Knowledge
- [decompilers](../knowledge/decompilers.md)
- [demangling](../knowledge/demangling.md)
- [disassemblers](../knowledge/disassemblers.md)

### Patterns
- [encrypted-string](../patterns/encrypted-string.md)
- [export-table](../patterns/export-table.md)
- [import-table](../patterns/import-table.md)

### Recipes
- [analyze-binary](analyze-binary.md)
- [recover-exports](recover-exports.md)
- [recover-imports](recover-imports.md)

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

