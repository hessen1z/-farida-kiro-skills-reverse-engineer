---
title: UPX Pattern
skill: binary-analysis
category: patterns
difficulty: intermediate
tags: [pe, loader, malware, elf]
updated: 2026-07-05
---
# UPX Pattern

## Overview

UPX is a popular packer that compresses executables and wraps them with a small decompression stub. UPX-packed binaries are widely encountered in malware and legitimate software.

## Detection

Look for:
- section names like `.UPX0`, `.UPX1`, `.UPX2`
- string patterns such as `UPX!` or `UPX!`, `UPX0`, `UPX1`
- small entry point stubs that call a decompressor and then transfer control to the unpacked payload
- relocated imports or a restored import table after decompression

## Analysis steps

1. verify UPX headers
   - locate the UPX magic and section names
   - confirm the expected layout of UPX compress and decompression sections

2. identify the decompression stub
   - trace the entry point through the UPX loader code

3. dump the unpacked image
   - allow the binary to execute until decompression completes
   - dump the reconstructed image from memory

4. recover restored metadata
   - verify import table, section headers, and entry point in the dumped image

## Practical notes

- UPX has well-known static and dynamic unpacking tools, but variants may require custom handling.
- Be aware of multiple compression layers or custom modifications to the UPX stub.

## Cross-links

- `../knowledge/packers.md`
- `../recipes/unpack-binary.md`

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

