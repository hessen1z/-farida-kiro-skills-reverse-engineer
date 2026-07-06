---
title: Export Table Pattern
skill: binary-analysis
category: patterns
difficulty: intermediate
tags: [pe, loader, dll, elf]
updated: 2026-07-05
---
# Export Table Pattern

## Overview

The export table pattern identifies how a module exposes functions and data to external callers. Exported symbols are often the easiest externally observable behavior of a DLL or executable.

## Detection

Look for:
- a valid export directory in `IMAGE_DIRECTORY_ENTRY_EXPORT`
- nonzero `NumberOfFunctions` or `NumberOfNames`
- forwarder strings indicating exports redirected to other modules
- export names pointing to loader or initialization routines

## Analysis steps

1. parse the export directory
   - read the export address table, name pointer table, and ordinal table

2. resolve exported RVAs
   - verify each RVA points to a valid code or data region
   - classify forwarded exports separately

3. identify exported interface semantics
   - exports named `DllMain`, `DllRegisterServer`, or `CreateObject` often indicate COM or plugin interfaces
   - ordinal-only exports are common in low-level or protected binaries

4. document suspicious exports
   - exports with unusually low ordinals or no names may be stubbed by packing/protection logic
   - exports that target a stub section may indicate a loader is reconstructing the real payload

## Practical notes

- Some protected binaries export a small loader stub while hiding the real implementation behind a runtime unpacker.
- Forwarded exports are still valid exports but are implemented by another module.

## Cross-links

- `../knowledge/pe.md`
- `../knowledge/symbols.md`
- `../recipes/recover-exports.md`

## Related Material

### Knowledge
- [decompilers](../knowledge/decompilers.md)
- [demangling](../knowledge/demangling.md)
- [disassemblers](../knowledge/disassemblers.md)

### Patterns
- [encrypted-string](encrypted-string.md)
- [import-table](import-table.md)
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

