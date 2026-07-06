---
title: Jump Table (explicit) Pattern
skill: patterns
category: 
difficulty: intermediate
tags: [pe, x64]
updated: 2026-07-05
---
# Jump Table (explicit) Pattern

Goal:
Identify tables of code pointers used for indirect branching and recover table structure.

Recognition signs:
- A contiguous data area containing pointers that reference `.text` entries.
- Code reading table base and performing scaled index addressing before an indirect call/jmp.

Assembly examples:
- x64:
```
lea rax, [rip + jump_table]
mov rdx, [rax + rbx*8]
jmp rdx
```
- x86:
```
mov eax, [ebp+index]
mov edx, [table + eax*4]
jmp dword ptr [edx]
```

Decompiled equivalent:
```
void (*tbl[])(void) = { f0, f1, f2 };
if (idx < n) tbl[idx](); else default();
```

Why the compiler generates this pattern:
- Fast dense dispatch for switch statements.
- Reduces branch misprediction and improves instruction cache locality.

Variations across compilers:
- Table might be absolute addresses (MSVC/x64) or relative offsets (GCC/Clang depending on PIC).
- Some compilers place the table in a separate read-only section; others inline it near the switch.

Common mistakes:
- Treating data table as static integer table rather than code pointers. Verify pointers point into executable segments.

Reverse engineering tips:
- Use IDA's "Create jump table" or Ghidra's table conversion; confirm entries are code addresses.
- Annotate the base and size; many tools can auto-create switch constructs once table is defined.

Detection heuristics:
- Presence of many pointers in data that resolve to `text` section addresses.
- Prior comparators that constrain index range.

Related patterns:
- `switch.md`
- `compiler-patterns.md`

Related knowledge pages:
- knowledge/assembly/common-instructions.md

References: Compiler IR and emitted assembly patterns. 
