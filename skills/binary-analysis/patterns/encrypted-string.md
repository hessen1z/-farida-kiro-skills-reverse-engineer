---
title: Encrypted String Pattern
skill: binary-analysis
category: patterns
difficulty: intermediate
tags: [pe, malware, elf]
updated: 2026-07-05
---
# Encrypted String Pattern

## Overview

Encrypted string patterns describe code that stores plaintext strings in encoded or encrypted form and reconstructs them at runtime. This is common in protectors and malware to hide command-and-control URLs, error messages, and API names.

## Detection

Look for:
- high-entropy data blocks in `.rdata`, `.data`, or custom sections
- loops that read bytes, apply arithmetic/xor operations, and store results to memory
- string reconstruction before API calls like `CreateFile`, `LoadLibrary`, or `GetProcAddress`
- unusual use of `VirtualAlloc`, `VirtualProtect`, or memory writes in non-data sections

## Analysis steps

1. identify the decryption routine
   - locate the decoder entry and the memory range it reads from

2. recover the decoding algorithm
   - track the operations: XOR, add/subtract, rotate, table lookup

3. apply the algorithm statically or dynamically
   - dump decrypted strings from memory when the routine executes
   - or implement the decoder in a script for bulk recovery

4. correlate strings with code paths
   - use recovered strings to label functions, APIs, and protocol behavior

## Practical notes

- Some binaries use polymorphic or per-instance keys; dynamic execution may be required.
- Strings may be reconstructed for a short time and then erased; use memory snapshots at the right moment.
- Decoding routines may themselves be obfuscated with opaque predicates or instruction mixing.

## Cross-links

- `../knowledge/pe.md`
- `../knowledge/obfuscation.md`
- `../patterns/obfuscated-jump.md`
- `../recipes/unpack-binary.md`

## Related Material

### Knowledge
- [decompilers](../knowledge/decompilers.md)
- [demangling](../knowledge/demangling.md)
- [disassemblers](../knowledge/disassemblers.md)

### Patterns
- [export-table](export-table.md)
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

