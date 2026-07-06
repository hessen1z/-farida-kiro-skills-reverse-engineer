---
title: Recover Exports Recipe
skill: binary-analysis
category: recipes
difficulty: intermediate
tags: [pe, loader, pdb, dll, elf]
updated: 2026-07-05
---
# Recover Exports Recipe

## Goal

Recover and validate exported symbols from a binary, including forwarded exports and export table anomalies.

## Steps

1. Parse the export directory
   - confirm `IMAGE_DIRECTORY_ENTRY_EXPORT` exists
   - read the export table, name pointer table, ordinal table, and address table

2. Validate export addresses
   - resolve each export RVA to a section or forwarder string
   - detect invalid RVAs or exports pointing outside the image

3. Handle forwarded exports
   - parse forwarder strings like `DLL.Function` or `DLL.#ordinal`
   - classify forwarded exports as imports from another module

4. Recover unnamed exports
   - infer names from ordinals when applicable
   - match ordinal-only exports against known DLL export ordinals for system libraries

5. Document export layout
   - list exported functions and data entries
   - record the export base, number of functions, and number of names
   - identify suspicious exports, such as exported loader helpers or anti-tamper entry points

## Notes

- Some binaries intentionally obfuscate exports by using export forwarding or by exporting only ordinal numbers.
- In packed binaries, the export table may be a stub and the real exports are reconstructed at runtime.

## Cross-links

- `../knowledge/pe.md`
- `../knowledge/symbols.md`
- `../patterns/export-table.md`

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
- [recover-imports](recover-imports.md)
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

