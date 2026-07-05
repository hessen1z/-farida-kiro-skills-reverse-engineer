# Packers

## Overview

Packers compress or encrypt executable code and data, then wrap it in a small loader stub. At runtime, the stub decompresses or decrypts the original payload in memory before transferring control.

## Internal Design

A packer typically includes:
- Compressed/encrypted payload section
- Bootstrap loader code
- Relocation and import fixing logic
- Optional integrity checks and anti-debug measures

Popular packers include UPX, Themida, VMProtect, and custom packers used by malware.

## Data Structures

- Packed header and stub
- Encrypted payload blocks
- Checksum or signature data

## Important APIs

### `VirtualAlloc`
Used by loaders to allocate memory for unpacked code.

### `GetProcAddress`
Used to resolve imports after unpacking.

## Reverse Engineering Notes

- Identifying a packer is the first step; common signatures and section names reveal known packers.
- Unpacking can be done statically using known algorithms, or dynamically by dumping the process after the stub has reconstructed the payload.

## Debugging Notes

- Packed binaries may trigger anti-debug code during unpacking.
- Breakpoints on `VirtualAlloc` or import resolver helpers can capture unpacked memory.

## Performance Notes

- Packing improves disk size and load-time locality at the cost of runtime unpacking overhead.
- For malware, runtime unpacking also delays analysis.

## Common Mistakes

- Failing to recognize a custom packer because it uses nonstandard stubs.
- Assuming the original entry point is the binary’s first executed instruction.

## References

- UPX documentation
- Research papers on code packing and unpacking

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

