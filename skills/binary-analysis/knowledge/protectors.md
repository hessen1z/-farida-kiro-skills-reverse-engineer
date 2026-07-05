# Protectors

## Overview

Protectors are advanced wrappers that combine packing with integrity checks, anti-debugging, anti-tampering, and virtualized code paths. They increase the difficulty of reverse engineering and often serve as DRM or malware obfuscation.

## Internal Design

Protectors usually incorporate:
- Encrypted and obfuscated payloads
- Anti-debug and anti-VM checks
- Integrity verification (checksum, hash, signature)
- Control-flow flattening or virtualization

## Data Structures

- Encrypted data segments
- Integrity metadata
- Virtual machine handlers

## Important APIs

### `IsDebuggerPresent`
Common API used by protectors to detect debuggers.

### `RtlGetVersion`
Used to detect environment and OS version for compatibility checks.

## Reverse Engineering Notes

- Protector stubs may execute before the main payload; identifying the transition point is critical.
- Tools like dynamic instrumentation and snapshots are often required to bypass or analyze protectors.

## Debugging Notes

- Some protectors detect debugger breakpoints in code pages and alter behavior; hardware breakpoints or tracing may be required.

## Performance Notes

- Protectors may intentionally degrade performance under analysis conditions to evade detection.

## Common Mistakes

- Treating protector stubs as the actual program logic instead of initialization and guard logic.

## References

- Research on virtualization-based protectors and anti-debugging techniques

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

