# Mach-O

## Overview

Mach-O is the native binary format for macOS and iOS. It supports fat binaries, dynamic linking, code signing, segments, sections, and symbol tables.

## Internal Design

A Mach-O binary contains:
- Mach header
- Load commands
- Segments and sections
- Symbol table and string table
- Dynamic linker information

The loader uses load commands to map segments and resolve dependencies.

## Data Structures

### Mach Header
Includes magic value, CPU type, file type, and number of load commands.

### Load Commands
Control how the file is loaded, including segment mapping, dynamic libraries, and code signing.

## Important APIs

### `dyld` / `dlopen`
Used for runtime linkage and introspection on macOS.

## Reverse Engineering Notes

- Fat binaries can contain multiple architectures in a single file.
- The `__TEXT` segment contains executable code; the `__DATA` segment contains writable data.

## Debugging Notes

- Code signing faults often appear when code pages are modified after load.

## Common Mistakes

- Confusing virtual addresses with file offsets across fat binary slices.

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

