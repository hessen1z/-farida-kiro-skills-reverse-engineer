---
title: Unpack Binary Recipe
skill: binary-analysis
category: recipes
difficulty: intermediate
tags: [pe, loader, debug, elf]
updated: 2026-07-05
---
# Unpack Binary Recipe

## Goal

Recover the original payload of a packed or protected binary by identifying unpacking logic and capturing the reconstructed image.

## Steps

1. Identify packing/protection artifacts
   - verify stub code and packed sections
   - detect high entropy regions and known packer signatures
   - locate TLS callbacks, loader stubs, or import resolution code

2. Determine the unpacking entry point
   - identify where control transfers from the packer stub to the real payload
   - follow jumps, API resolution, and memory write loops

3. Use dynamic tracing or breakpoints
   - run the binary in a controlled environment
   - break on `VirtualAlloc`, `VirtualProtect`, and key memory-write loops
   - capture the image once the payload is reconstructed

4. Dump the unpacked image
   - use debugger or instrumentation to dump memory after unpacking
   - restore section headers and imports if necessary

5. Validate the recovered image
   - verify the dumped image has correct export/import metadata
   - check the entry point and function boundaries
   - compare against original static binary to confirm original payload content

## Notes

- Some protectors reconstruct code lazily or in small chunks. A single dump may need additional analysis to recover the full payload.
- Keep a record of the unpacking runtime state and any integrity checks that were bypassed.

## Cross-links

- `../knowledge/packers.md`
- `../knowledge/protectors.md`
- `../recipes/recover-imports.md`

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

