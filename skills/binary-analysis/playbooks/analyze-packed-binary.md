# Analyze Packed Binary Playbook

## Goal

Guide the analyst through identifying, classifying, and recovering the payload from a packed or protected binary.

## Scenario

A binary exhibits packer-like behavior: a small loader stub, high entropy sections, sparse imports, or TLS callbacks used for initialization.

## Workflow

1. Confirm packing indicators
   - inspect section names and entropy
   - check for known packer signatures and stub patterns
   - identify a minimal entry point and import-heavy unpacker code

2. Determine unpacking runtime
   - locate the transition from stub to unpacked payload
   - trace calls to `VirtualAlloc`, `VirtualProtect`, `LoadLibrary`, `GetProcAddress`
   - identify any TLS callbacks or initialization hooks

3. Capture the unpacked image
   - use dynamic instrumentation or debugger breakpoints on memory allocation and write loops
   - dump the reconstructed image after unpacking
   - reconstruct the import table if needed

4. Verify the recovered image
   - validate section headers, imports, and exports
   - map entry point to the payload’s actual code
   - compare against the static binary and dynamic memory image

5. Report findings
   - classify the packer or protector
   - document the unpacking entry point, payload layout, and any runtime checks
   - recommend follow-up analysis such as symbol recovery or exception table inspection

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
- [analyze-pe](analyze-pe.md)
- [analyze-protected-binary](analyze-protected-binary.md)

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

