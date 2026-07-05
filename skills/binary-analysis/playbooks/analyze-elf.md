# Analyze ELF Playbook

## Goal

Provide a practical process for analyzing ELF binaries, locating dynamic symbols, and understanding loader behavior on UNIX-like systems.

## Scenario

An ELF executable or shared object requires analysis for runtime dependencies, symbol resolution, and potential obfuscation.

## Workflow

1. Validate the ELF header
   - confirm magic bytes and class (32-bit vs 64-bit)
   - record machine type, entry point, and section/segment offsets

2. Parse program headers
   - identify loadable segments and memory permissions
   - map file offsets to runtime addresses

3. Inspect sections and symbol tables
   - enumerate `.dynsym`, `.symtab`, `.strtab`, `.rela`, and `.plt/.got`
   - locate imported and exported symbols

4. Analyze dynamic linking metadata
   - inspect dynamic entries like `DT_NEEDED`, `DT_STRTAB`, and `DT_PLTGOT`
   - identify relocation types and lazy binding stubs

5. Detect protections and anomalies
   - look for packed segments, high entropy, bogus section names, or custom loader code
   - identify `PT_NOTE` or `.note` sections with build information or sandbox detection

6. Cross-check with runtime behavior
   - use `ldd`, `readelf`, `objdump`, or a debugger to validate symbol resolution and relocation behavior

7. Document findings
   - capture format details, symbol availability, and loader metadata
   - note whether the binary is suitable for static analysis or requires dynamic tracing

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
- [analyze-packed-binary](analyze-packed-binary.md)
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

