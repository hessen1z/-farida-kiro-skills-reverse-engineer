# Recover Imports Recipe

## Goal

Recover imported APIs and resolve import tables in binaries with missing or obfuscated import metadata.

## Steps

1. Parse the import directory
   - confirm `IMAGE_DIRECTORY_ENTRY_IMPORT` exists
   - enumerate import descriptors for each DLL
   - read thunk arrays or import name tables

2. Resolve imported names and ordinals
   - map each thunk to an import name or ordinal
   - detect hint/name table entries and ordinal-only imports

3. Identify import table anomalies
   - detect import table redirection, import hashing, or delayed load stubs
   - locate fake imports or stub entries used by protectors

4. Recover imports from memory or dumped images
   - if the static import table is missing, inspect the runtime import address table (IAT)
   - compare loaded image memory against file contents to identify restored IAT entries

5. Augment missing imports
   - use call site and API usage patterns to infer likely imported functions
   - search for `LoadLibrary` / `GetProcAddress` strings and hash resolution routines

## Notes

- A packed or protected binary may rebuild the import table at runtime. Static analysis should look for import reconstruction code.
- Delayed import tables and import thunks are legitimate structures and should be distinguished from obfuscation.

## Cross-links

- `../knowledge/pe.md`
- `../knowledge/symbols.md`
- `../patterns/import-table.md`

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
- [recover-pdb](recover-pdb.md)

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

