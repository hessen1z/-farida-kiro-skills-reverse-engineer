# Symbols

## Overview

Symbols connect addresses to human-readable identifiers. They are critical for debuggers, reverse engineering tools, and symbol recovery workflows. Symbols may represent:
- exported functions and data
- imported APIs
- local functions, labels, and variables
- type metadata and debug information

## Symbol sources

### PE

PE uses export and import metadata. The export directory provides names, ordinals, and RVAs. The import directory lists DLL names and imported function names or ordinals.

### ELF

ELF binaries use symbol tables such as `.symtab` for full symbols and `.dynsym` for dynamic linker-visible symbols. The string table stores symbol names.

### Mach-O

Mach-O stores symbols in the symbol table with a parallel string table. `nlist` entries encode symbol type, section, and name index.

## Recovering symbols

### Known symbol sources

- exports and imports
- PDB / DWARF / dSYM debug data
- public symbol servers and symbol store indexes

### Heuristic symbol recovery

When symbols are stripped, analysts recover names by using:
- RTTI structures and typeinfo names
- imported API usage patterns
- function prolog/epilog signatures
- string references and vtable layout

## Important APIs and tools

- `SymFromAddr`, `SymLoadModuleEx`, `SymInitialize` (DbgHelp)
- `dladdr` on POSIX systems
- `c++filt` and `undname` for demangling
- `objdump`, `nm`, `readelf`, `llvm-symbolizer`

## Analysis workflow

### 1. Classify symbol availability

Determine whether the binary is:
- fully symbolized
- partially symbolized (exports/imports only)
- stripped

### 2. Extract available names

Parse export tables, import descriptors, debug directories, and external symbol servers.

### 3. Map addresses to symbol names

Use runtime symbol resolution APIs or static symbol tables to annotate disassembly and call stacks.

### 4. Augment missing symbol data

Recover function names using type info, RTTI, and pattern matching. For C++ binaries, demangle available names to restore signatures.

## Reverse engineering notes

- Export names are usually the most reliable indicator of functionality in stripped binaries.
- Import tables show which system and library APIs the binary depends on.
- Symbol recovery from RTTI and vtables can yield class and method names even when debug data is absent.

## Debugging notes

- Missing symbols significantly degrade stack trace quality.
- Symbol mismatches often occur when the PDB does not match the binary’s timestamp or signature.
- Load the correct public or private symbols for accurate source mapping.

## Common mistakes

- Assuming missing symbol names means the binary is useless; many binaries can still be analyzed using imports and structural heuristics.
- Confusing imported names with internal function names.
- Treating ordinal-only imports as opaque without searching for common DLL export layouts.

## Cross-links

- `../knowledge/pdb.md`
- `../knowledge/demangling.md`
- `../knowledge/pe.md`
- `../recipes/recover-symbols.md`

## References

- Microsoft DbgHelp API documentation
- ELF and Mach-O symbol table specifications

## Related Material

### Knowledge
- [decompilers](decompilers.md)
- [demangling](demangling.md)
- [disassemblers](disassemblers.md)

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

