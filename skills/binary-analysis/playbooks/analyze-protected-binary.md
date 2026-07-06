---
title: Analyze Protected Binary Playbook
skill: binary-analysis
category: playbooks
difficulty: intermediate
tags: [pe, loader, gui, debug, elf]
updated: 2026-07-05
---
# Analyze Protected Binary Playbook

## Goal

Document a methodical approach for analyzing binaries protected by packers, obfuscators, and anti-debug techniques.

## Scenario

A target binary appears protected: it has a minimal entry stub, runtime unpacker code, anti-debug checks, or disguised imports.

## Workflow

1. Confirm protection signals
   - inspect imports, sections, and entry point complexity
   - identify anti-debug APIs, high entropy sections, and irregular metadata directories

2. Map the protection boundary
   - determine where the protector stub ends and the real payload begins
   - trace control flow through loader routines and callback vectors

3. Analyze anti-analysis measures
   - locate debugger detection, VM detection, checksum validation, and exception-based control flow
   - document how the runtime environment influences behavior

4. Use dynamic analysis carefully
   - employ a controlled sandbox or instrumented debugger
   - set breakpoints on key APIs and memory-modifying loops

5. Recover the protected payload
   - dump or reconstruct the image after the protector has unpacked or decrypted it
   - restore imports, exports, and section metadata as needed

6. Validate and document
   - verify the recovered payload’s structure and runtime compatibility
   - summarize protection techniques, bypass points, and recommended analysis paths

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
- [analyze-pe](analyze-pe.md)

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

