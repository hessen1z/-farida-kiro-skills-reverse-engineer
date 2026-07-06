---
title: Packer Pattern
skill: binary-analysis
category: patterns
difficulty: intermediate
tags: [pe, loader, elf]
updated: 2026-07-05
---
# Packer Pattern

## Pattern

Packer patterns identify binaries that use runtime compression, encryption, and loader stubs. Key indicators include:
- unusually large code section containing a small loader stub
- anonymous or padded sections like `.UPX`, `.aspack`, `.themida`
- relocated import tables or import name hashing
- a minimal entry point that resolves imports and then jumps to a second stage
- presence of TLS callbacks used to start unpacking

## Analysis steps

1. Identify the entry stub and map the binary’s actual execution flow.
2. Inspect section names, entropy, and section characteristics for packed payloads.
3. Locate dynamic import resolution or API hashing routines.
4. Search for memory allocation, decryption loops, and `VirtualAlloc` / `VirtualProtect` calls.
5. Extract or dump the unpacked image after the loader has reconstructed it in memory.

## Common packer indicators

- section names like `.UPX`, `.aspack`, `.vmp0`, `.vmp1`
- high entropy in code or data sections
- imported API functions limited to `LoadLibrary`, `GetProcAddress`, `VirtualAlloc`, `VirtualProtect`, `RtlMoveMemory`
- TLS callbacks or unusual loader callbacks
- broken or absent import tables

## Tools and techniques

- signature-based packer scanners (e.g. PEiD)
- dynamic execution and memory dumping
- reconstructing the import table from an unpacked image
- emulating stub behavior when static unpacking is impractical

## Cross-links

- `../knowledge/packers.md`
- `../knowledge/pe.md`
- `../knowledge/tls.md`
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

