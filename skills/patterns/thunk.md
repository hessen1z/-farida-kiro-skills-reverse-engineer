---
title: Thunk Pattern
skill: patterns
category: 
difficulty: intermediate
tags: [pe, windows, x64]
updated: 2026-07-05
---
# Thunk Pattern

Goal:
Recognize short glue functions (thunks) that adjust arguments or jump to another function.

Recognition signs:
- Very short function (few instructions) that adjusts `rcx`/`this` or performs a small arithmetic, then `jmp` to a different address.
- Thunks often used for multiple inheritance, virtual-to-nonvirtual bridges, or import thunks.

Assembly examples:
- Multiple inheritance thunk (x64):
```
sub rcx, 0x10
jmp MyClass::Method
```
- Import thunk (x86):
```
jmp dword ptr [IAT+4]
```

Decompiled equivalent:
```
void thunk(SomeClass* this) { return ((Derived*)((char*)this - 0x10))->Method(); }
```

Why compiler generates this pattern:
- Adjust `this` pointer for secondary vtables or to match calling convention requirements.
- Support method forwarding between compatible functions.

Variations (MSVC / Clang / GCC):
- MSVC: explicit `sub`/`add` before `jmp` for multiple inheritance thunks.
- GCC/Clang: similar but may use `lea` adjustments or different calling convention shims.

Common mistakes:
- Misinterpreting thunks as standalone functions with meaningful logic. They are usually transparent wrappers.

Reverse engineering tips:
- In IDA, mark the thunk as a tail/jump to the real function using `MakeCode` and `Create Function` then set comments about `this` adjustment.
- Search for short cross-module jumps to detect import thunks.

Detection heuristics:
- Function size < 8 bytes and ends in `jmp` or `ret` after a single small adjustment.

Related patterns:
- `virtual-call.md`
- `compiler-patterns.md`

Related knowledge pages:
- knowledge/assembly/compiler-patterns.md
- knowledge/windows/cpp/vtables.md

References: ABI docs and multiple-inheritance notes.
