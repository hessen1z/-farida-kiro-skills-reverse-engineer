---
title: Demangling
skill: binary-analysis
category: knowledge
difficulty: intermediate
tags: [pe, windows, pdb, gui, debug, elf]
updated: 2026-07-05
---
# Demangling

## Overview

Demangling is the process of converting compiler-generated symbol names back into human-readable declarations. C++ symbol mangling encodes namespaces, classes, function signatures, and calling conventions into a compact identifier.

## Internal Design

Different compilers use different mangling schemes:
- Microsoft Visual C++ uses the `?`-prefixed decorated name format.
- GCC/Clang follow the Itanium C++ ABI mangling syntax.

Demangling reverses this encoding to recover function prototypes, class templates, and member names.

## Data Structures

- Mangled symbol string
- Symbol components: namespaces, classes, function name, parameter types, qualifiers

## Important APIs

### `UnDecorateSymbolName`
Windows API for demangling MSVC symbol names.

### `c++filt`
GNU tool for demangling Itanium-style symbols.

## Assembly Examples

### MSVC decorated symbol
A symbol like `?func@MyClass@@QEAAHXZ` encodes a method `int __cdecl MyClass::func(int)`.

### Itanium mangled name
A symbol like `_ZN7MyClass4funcEi` demangles to `MyClass::func(int)`.

## C++ Examples

### Using `UnDecorateSymbolName`
```cpp
#include <windows.h>
#include <dbghelp.h>

std::string demangle(const char* symbol) {
    char buffer[1024];
    if (UnDecorateSymbolName(symbol, buffer, sizeof(buffer), UNDNAME_COMPLETE)) {
        return buffer;
    }
    return symbol;
}
```

## Reverse Engineering Notes

- Demangling is essential when PDBs are unavailable but symbol tables or import/export names are present.
- Packaged binaries may include mangled names in debug sections or export tables.

## Debugging Notes

- Reconstructed symbol names are heuristics and should be validated with type information when available.

## Performance Notes

- Demangling is a lightweight text-processing step and should be performed after symbol discovery.

## Common Mistakes

- Assuming demangled names are always correct; some symbols may be truncated or obfuscated.

## References

- Microsoft Debugging SDK
- Itanium C++ ABI documentation

## Related Material

### Knowledge
- [decompilers](decompilers.md)
- [disassemblers](disassemblers.md)
- [dwarf](dwarf.md)

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

- Use `UnDecorateSymbolName` on Windows and `c++filt` for Itanium-style symbols to quickly recover readable names.
- When demangled names conflict with inferred types, prefer runtime-observed signatures and adjust types accordingly.

## Tools & Commands

- `undname` / `dbghelp` on Windows for MSVC symbols.
- `c++filt` or `llvm-cxxfilt` for GCC/Clang (Itanium) mangled names.

## Validation Checklist

- Confirm demangled names against PDBs or symbol servers when available.
- Cross-check parameter types inferred from demangled signatures with calling convention and register usage.

