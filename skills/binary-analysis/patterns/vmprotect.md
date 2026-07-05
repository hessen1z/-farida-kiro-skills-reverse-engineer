# VMProtect Pattern

## Overview

VMProtect is a protector that virtualizes code paths and combines packing with anti-debugging. It is commonly used to protect sensitive algorithms and DRM logic.

## Detection

Look for:
- section names like `.vmp0`, `.vmp1`, `.vmp2`, `.vmp3`
- large blocks of opaque or virtualized code
- calls into a VM dispatcher loop with switch-like semantics
- anti-debug and anti-VM checks in proximity to the protected code

## Analysis steps

1. identify the virtual machine boundary
   - locate the entry point to VM-protected regions
   - inspect how the dispatcher selects virtualized instructions

2. analyze the VM environment
   - identify register and memory state used by the VM
   - recover the opcode decoding logic and operand formats

3. decrypt or emulate virtualized code
   - if feasible, emulate the VM instructions to recover semantics
   - otherwise, document the VM handler and its protected payload

4. bypass anti-debug guards
   - identify and disable or patch debugger detection checks before analyzing the VM

## Practical notes

- VMProtect may combine virtualization with packing and TLS callbacks.
- Fully recovering VM-protected code may require a dedicated VM analysis tool or custom emulator.

## Cross-links

- `../knowledge/protectors.md`
- `../knowledge/obfuscation.md`
- `../patterns/tls-callback.md`

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

