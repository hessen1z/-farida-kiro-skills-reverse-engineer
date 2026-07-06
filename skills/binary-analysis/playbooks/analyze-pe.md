---
title: Analyze PE Playbook
skill: binary-analysis
category: playbooks
difficulty: intermediate
tags: [pe, windows, loader, pdb, debug, dll, elf]
updated: 2026-07-05
---
# Analyze PE Playbook

## Goal

Provide a repeatable process for inspecting PE binaries, understanding loader metadata, and identifying symbols, imports, exports, and protections.

## Scenario

A Windows executable or DLL needs structural analysis to determine functionality, load-time behavior, and symbol recovery potential.

## Workflow

1. Identify PE file properties
   - validate DOS header and PE signature
   - record architecture, subsystem, and optional header flags

2. Parse the section table
   - enumerate sections, sizes, characteristics, and raw offsets
   - identify code, data, resource, and TLS sections

3. Inspect metadata directories
   - analyze import, export, relocation, TLS, resource, and debug directories
   - confirm values and locate referenced data structures

4. Recover symbols and debug metadata
   - parse PDB information from the debug directory
   - extract available export and import names
   - assess whether the binary is stripped or symbolized

5. Detect protections and packers
   - review section entropy, stub code, and anti-analysis imports
   - locate suspicious TLS callbacks, dynamic import resolution, or bogus section headers

6. Validate with dynamic evidence
   - where possible, compare static metadata with runtime image mappings
   - inspect actual memory permissions and loader-applied relocations

7. Document analysis
   - summarize format classification, metadata inventory, and potential protection mechanisms
   - capture key offsets, RVAs, and any recovered symbol names

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
- [analyze-binary](../recipes/analyze-binary.md)
- [recover-exports](../recipes/recover-exports.md)
- [recover-imports](../recipes/recover-imports.md)

### Playbooks
- [analyze-elf](analyze-elf.md)
- [analyze-packed-binary](analyze-packed-binary.md)
- [analyze-protected-binary](analyze-protected-binary.md)

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

