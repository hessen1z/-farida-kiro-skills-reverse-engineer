# Binary Analysis Checklist

## PE/ELF/Mach-O validation
- [ ] Confirm magic header and file type
- [ ] Verify architecture and bitness
- [ ] Record entry point and subsystem/type
- [ ] Map file offsets to runtime addresses

## Header and layout analysis
- [ ] Parse section or segment tables
- [ ] Confirm section/segment permissions and sizes
- [ ] Identify code, data, resource, TLS, and debug sections
- [ ] Inspect metadata directories for imports, exports, relocations, resources, debug info

## Imports and exports
- [ ] Extract import DLLs and imported functions/ordinals
- [ ] Parse export directory and resolve forwarders
- [ ] Detect missing or reconstructed import tables
- [ ] Identify API categories relevant to functionality

## Runtime metadata
- [ ] Locate relocation tables and verify applicability
- [ ] Parse TLS directory and callback arrays
- [ ] Extract resource strings, manifests, and version info
- [ ] Inspect debug metadata for PDB, DWARF, or symbol streams

## Protection and obfuscation
- [ ] Check for high-entropy sections or stub loaders
- [ ] Detect packer/protector signatures (UPX, Themida, VMProtect, custom)
- [ ] Identify anti-debug/anti-VM APIs and callbacks
- [ ] Look for exception-based or indirect control-flow obfuscation

## Symbol and debug recovery
- [ ] Determine symbol availability and whether the binary is stripped
- [ ] Search for PDB signatures and public symbol metadata
- [ ] Recover symbols from RTTI, vtables, and debug records
- [ ] Validate name mappings against runtime evidence

## Dynamic and runtime validation
- [ ] If safe, run in a controlled environment
- [ ] Capture early initialization and unpacking behavior
- [ ] Dump reconstructed images when applicable
- [ ] Compare static layout with runtime mappings

## Reporting
- [ ] Summarize key findings and evidence
- [ ] Classify format, protection, and recovery status
- [ ] Recommend next steps: unpack, recover symbols, analyze crash, etc.

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

