---
title: DWARF
skill: binary-analysis
category: knowledge
difficulty: intermediate
tags: [pe, gui, debug, elf]
updated: 2026-07-05
---
# DWARF

## Overview

DWARF is a standardized debugging data format used on UNIX-like systems and many compilers. It describes types, variables, stack frames, and source mappings to support symbolic debugging and reverse engineering.

## Internal Design

DWARF data is organized into sections such as:
- `.debug_info`
- `.debug_abbrev`
- `.debug_line`
- `.debug_str`
- `.debug_frame`

Entries in `.debug_info` form a tree of DIEs (Debugging Information Entries) describing compilation units, types, and symbols.

## Data Structures

### DIEs
A DIE has a tag (e.g., `DW_TAG_subprogram`) and attributes such as name, type, and location.

### Line Number Table
Maps instruction addresses to source file lines.

### Frame Information
Enables stack unwinding through `.debug_frame` or `.eh_frame`.

## Important APIs

### `libdwarf` / `libelf`
Libraries commonly used to parse DWARF data.

## Reverse Engineering Notes

- DWARF enables reconstruction of high-level structure when available.
- Stripped binaries may still carry `.eh_frame` for unwind information without full DWARF.

## Debugging Notes

- Incorrect DWARF can cause debuggers to show wrong variables or call stacks.

## Performance Notes

- DWARF processing can be slow due to variable-length encodings and nested trees.

## Common Mistakes

- Assuming the presence of DWARF in release builds.
- Confusing section offsets with runtime addresses.

## References

- DWARF Debugging Standard
- `readelf` and `objdump` documentation

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

- Use `readelf --debug-dump=info` or `llvm-dwarfdump` to inspect DWARF sections and DIEs.
- When DWARF is present, prefer using it to seed type information and function boundaries in the disassembler.

## Tools & Commands

- `readelf`, `objdump`, `llvm-dwarfdump`, and `libdwarf` for parsing and extracting DWARF info.

## Validation Checklist

- Confirm address-to-line mappings with runtime traces to ensure correct source correlation.
- Validate frame information by performing controlled stack unwinds in a debugger.

