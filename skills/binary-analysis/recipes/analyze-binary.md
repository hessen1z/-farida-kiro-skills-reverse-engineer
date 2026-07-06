---
title: Analyze Binary Recipe
skill: binary-analysis
category: recipes
difficulty: intermediate
tags: [pe, loader, pdb, debug, elf, mach-o]
updated: 2026-07-05
---
# Analyze Binary Recipe

## Goal

Provide a structured workflow to classify a native binary, recover runtime metadata, and identify protection or packing artifacts.

## Steps

1. Identify the binary format
   - confirm magic bytes and header type (PE, ELF, Mach-O)
   - determine architecture, bitness, and subsystem

2. Parse file layout
   - parse headers, section/segment tables, and entry point
   - map file offsets to runtime addresses
   - record section permissions and metadata directories

3. Analyze imports and exports
   - extract import descriptors and export directory
   - identify runtime dependencies and interface points
   - detect ordinal-only imports or import hashing

4. Inspect loader metadata
   - parse relocations, TLS directory, resources, and debug directories
   - identify missing or suspicious entries

5. Classify protections and packers
   - look for packed stub indicators, high entropy sections, and known signatures
   - check for TLS callbacks, anti-debug imports, and runtime loader stubs

6. Validate with dynamic evidence
   - if possible, run the binary in a controlled environment, break on early initialization, and dump memory
   - compare static structure against runtime-mapped image

7. Document findings
   - record format classification, symbol recovery status, protection/packer classification, and recommended next steps
   - link findings to evidence, examples, and related patterns

## Output

- format classification and runtime mapping
- import/export inventory
- loader and debug metadata summary
- protection/packer assessment
- recommended follow-up recipe (unpack, recover symbols, analyze crash, etc.)

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
- [recover-exports](recover-exports.md)
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

