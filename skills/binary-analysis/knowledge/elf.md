---
title: Executable and Linkable Format (ELF)
skill: binary-analysis
category: knowledge
difficulty: intermediate
tags: [pe, loader, asm, gui, debug, elf]
updated: 2026-07-05
---
# Executable and Linkable Format (ELF)

## Overview

ELF is the standard binary format used by Linux, BSD, and UNIX-like systems. It defines sections, segments, symbol tables, dynamic linking metadata, and debug information.

## Internal Design

An ELF binary consists of:
- ELF header
- Program headers (segments)
- Section headers
- Optional sections: `.text`, `.data`, `.rodata`, `.bss`, `.symtab`, `.strtab`, `.rela`, `.debug`

The loader uses program headers to map memory and sections for linking and execution.

## Data Structures

### ELF Header
Contains metadata about machine architecture, entry point, and offsets to program and section headers.

### Program Header Table
Defines loadable segments and memory permissions.

### Section Header Table
Describes sections and their relationships with the binary.

### Symbol Table
Stores exported and local symbol names with corresponding addresses.

## Important APIs

### `dlopen` / `dlsym`
Dynamic loader APIs for runtime symbol resolution on Linux.

### `mmap`
Maps files into memory for manual loading and introspection.

## Assembly Examples

### ELF header validation
```asm
mov rax, [base]
cmp dword ptr [rax], 0x464C457F ; 0x7F 'ELF'
```

## C++ Examples

### Parse ELF header
```cpp
#include <elf.h>

Elf64_Ehdr* get_elf_header(uint8_t* base) {
    return reinterpret_cast<Elf64_Ehdr*>(base);
}
```

## Reverse Engineering Notes

- ELF uses relative addressing with PIC; symbol resolution and relocations are essential for analysis.
- `.plt` and `.got` are key structures for identifying imported functions.

## Debugging Notes

- Invalid PT_LOAD segments cause segmentation faults during mapping.
- Dynamic relocations are often applied lazily, which affects runtime analysis.

## Performance Notes

- Large symbol tables slow down linkers and debuggers.

## Common Mistakes

- Mixing section-based offsets with segment-based addresses.

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

## Practical Guidance

- Use `readelf -a` and `objdump -x` to inspect ELF headers, program headers, and relocations.
- Be careful with position-independent code (PIC) and lazy PLT/GOT bindings when analyzing runtime behavior.

## Tools & Commands

- `readelf`, `objdump`, `eu-readelf`, and `radare2` for ELF inspection.

## Validation Checklist

- Verify segment mappings and relocation application by loading the binary in a controlled environment.
- Confirm symbol visibility and PLT/GOT entries for imported functions.

