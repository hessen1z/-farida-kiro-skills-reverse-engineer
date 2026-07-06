---
title: Import Table Pattern
skill: binary-analysis
category: patterns
difficulty: intermediate
tags: [pe, loader, kernel, dll, elf]
updated: 2026-07-05
---
# Import Table Pattern

## Overview

The import table pattern identifies how a PE binary depends on external libraries and APIs. The import table is also a common target for packers and protectors, which may obfuscate or reconstruct imports at runtime.

## Detection

Look for:
- a valid import directory in `IMAGE_DIRECTORY_ENTRY_IMPORT`
- import descriptors referencing DLL names
- thunk arrays containing `IMAGE_THUNK_DATA` entries
- delayed import directories or import name hashing routines

## Analysis steps

1. enumerate import descriptors
   - read imported DLL names and corresponding thunk arrays

2. resolve imported function names or ordinals
   - inspect `IMAGE_IMPORT_BY_NAME` entries and ordinal-only imports
   - classify imported APIs by category: loader, kernel, network, graphics, etc.

3. identify obfuscation or runtime import rebuilding
   - look for calls to `LoadLibrary` and `GetProcAddress`
   - detect import hashing loops and manual import fixups

4. keep an eye on delay-load imports
   - delayed imports are valid and loaded on demand, but they can also be abused to hide dependencies

## Practical notes

- A missing or broken import table is a strong indicator of packing or protection.
- Runtime-rebuilt imports often coexist with a minimal static import directory.

## Cross-links

- `../knowledge/pe.md`
- `../knowledge/symbols.md`
- `../recipes/recover-imports.md`

## Related Material

### Knowledge
- [decompilers](../knowledge/decompilers.md)
- [demangling](../knowledge/demangling.md)
- [disassemblers](../knowledge/disassemblers.md)

### Patterns
- [encrypted-string](encrypted-string.md)
- [export-table](export-table.md)
- [obfuscated-jump](obfuscated-jump.md)

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

