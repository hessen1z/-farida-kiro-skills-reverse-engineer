# Recover PDB Recipe

## Goal

Recover or locate the matching PDB for a Windows binary, verify its signature, and use it to restore symbol and source information.

## Steps

1. Extract debug metadata from the binary
   - inspect `IMAGE_DIRECTORY_ENTRY_DEBUG`
   - locate `CodeView` records and read the GUID, age, and PDB filename

2. Search symbol sources
   - use the binary’s PDB signature to search local symbol caches
   - query public symbol servers or internal symbol repositories
   - look for private symbols when available

3. Verify the PDB match
   - confirm the PDB GUID and age match the binary
   - verify the PDB file checksum if available

4. Load the PDB
   - use `SymInitialize`, `SymLoadModuleEx`, or DIA to load the matching PDB
   - validate that symbols, source files, and line numbers are available

5. Use the PDB data
   - recover function names and public symbols
   - retrieve type and class information
   - map addresses back to source files and line numbers

## Notes

- A mismatched PDB is a common failure mode. Always verify GUID and age before trusting symbols.
- If the original PDB is unavailable, use public symbols or heuristics instead.

## Cross-links

- `../knowledge/pdb.md`
- `../knowledge/symbols.md`
- `../recipes/recover-symbols.md`

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

