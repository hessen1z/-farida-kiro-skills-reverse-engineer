---
title: Exception Pattern
skill: patterns
category: 
difficulty: intermediate
tags: [pe, windows, x64]
updated: 2026-07-05
---
# Exception Pattern

Goal:
Recognize exception handling constructs (SEH and C++ exceptions) and their code patterns.

Recognition signs:
- Presence of `.pdata`, `.xdata` and unwind info for x64; SEH chains for x86.
- Calls to `__CxxFrameHandler`, `__GSHandlerCheck`, `__RTDynamicCast`, and other EH helpers.

Assembly examples:
- x64 unwind table usage is in metadata; handler entry looks up exception tables rather than explicit chain.
- x86 SEH chain:
```
mov dword ptr [esp], handler
push dword ptr [esp] ; set up exception frame
```

Decompiled equivalent:
```
try { ... } catch(...) { ... }
```

Why compiler generates this pattern:
- Structured exception handling and C++ EH provide stack unwinding and cleanup semantics.

Variations across compilers:
- MSVC uses table-based unwinding on x64; GCC uses DWARF unwind tables.

Common mistakes:
- Mislabeling exception handlers as normal control flow targets; unwinding paths may not be visible via direct branches.

Reverse engineering tips:
- Use unwind metadata to reconstruct function boundaries and exception handlers in IDA/Ghidra.
- For x86, inspect FS:[0] chain to find SEH handlers.

Detection heuristics:
- Presence of `.pdata` and `.xdata` sections and references to C++ EH symbols.

Related patterns:
- `compiler-patterns.md`

Related knowledge pages:
- knowledge/windows/cpp/exceptions.md
- knowledge/assembly/common-instructions.md
