---
title: Switch / Jump Table Patterns
skill: patterns
category: 
difficulty: intermediate
tags: [windows, loader, x64]
updated: 2026-07-05
---
# Switch / Jump Table Patterns

Goal:
Recognize compiler-generated switch/case dispatch implemented with jump tables.

Recognition signs:
- A bounds check on an integer index followed by an indirect jump through a table of addresses.
- Patterns: compare/index against constant, conditional branch to default, scale and add to table base, indirect jump.

Assembly examples:
- x86 (MSVC, 32-bit):
```
cmp eax, 5
ja  default
mov edx, [eax*4 + offset table]
jmp edx
```
- x64 (MSVC, 64-bit):
```
cmp ecx, 0x10
ja  default
mov rax, qword ptr [rip + jump_table]
mov rdx, qword ptr [rax + rcx*8]
jmp rdx
```

Decompiled equivalent:
```
switch (v) {
  case 0: ...; break;
  case 1: ...; break;
  default: ...;
}
```

Why compiler generates this pattern:
- Jump tables provide O(1) dispatch for dense switch ranges and reduce branch misprediction.

Variations across compilers (MSVC / Clang / GCC):
- MSVC: often uses a table of absolute addresses in read-only data and `jmp` via register. Uses `jmp qword ptr [table + idx*8]` on x64.
- GCC/Clang (Itanium): may use `jmp` through `pc-relative` table or use `lea` + `jmp` with different section placement (.rodata vs .rdata).
- Some compilers emit a binary search/tree for sparse switch ranges instead of a table.

Common mistakes:
- Mistaking a table-of-constants load for a jump table (ensure the target is executed address and not data lookup).
- Missing the initial bounds check; some compilers emit masked indexes instead of explicit compare.

Reverse engineering tips:
- In IDA: look for `jmp` targets that are in `.text` and a nearby data block aligning to pointer-size — right-click the data and use "Create Jump Table".
- In Ghidra: select the data array, use "Convert to Table" then mark references; Ghidra often recognizes jump tables when data points to valid code.
- In x64dbg: set a code breakpoint at the computed `jmp` and run to see the target; log the pointer table addresses.

Detection heuristics:
- Data-aligned array in .rdata/.rodata with values pointing into .text.
- Sequence: compare/index → conditional branch to default → scale+add → indirect jmp.

Related patterns:
- `jump-table.md` (explicit discussion of tables and relocations)
- `compiler-patterns.md` (why compilers choose table vs tree)

Related knowledge pages:
- knowledge/assembly/common-instructions.md
- knowledge/windows/loader.md

References:
- Compiler documentation and ABI notes (MSVC optimization manuals)
- Practical RE examples (various public writeups)
