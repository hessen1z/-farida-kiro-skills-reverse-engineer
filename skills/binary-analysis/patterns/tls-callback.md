# TLS Callback Pattern

## Overview

TLS callbacks are functions registered in the PE TLS directory and executed by the loader before the normal entry point. They are a common technique in packers and protectors to run initialization and unpacking logic early.

## Detection

Look for:
- a TLS directory present in the binary’s data directories
- callback arrays referenced by `AddressOfCallBacks`
- callback functions executed before the entry point
- significant code in the TLS callback targets, especially if the main entry point is small

## Analysis steps

1. enumerate TLS callbacks
   - parse the callback array and resolve each target address

2. inspect callback semantics
   - determine whether callbacks initialize runtime structures, decrypt payloads, or perform anti-analysis checks

3. trace callback execution
   - if possible, dynamically break on TLS callbacks or instrument the loader early

4. classify callback use
   - loader initialization
   - runtime unpacking
   - anti-debug/anti-VM checks

## Practical notes

- TLS callbacks may execute multiple times: once at process startup and once per thread creation.
- A small or plain entry point with heavy TLS callbacks is a strong sign that the real startup logic is hidden in TLS.

## Cross-links

- `../knowledge/tls.md`
- `../knowledge/pe.md`
- `../recipes/unpack-binary.md`

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

