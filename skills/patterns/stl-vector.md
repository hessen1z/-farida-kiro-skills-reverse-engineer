---
title: STL std::vector Patterns
skill: patterns
category: 
difficulty: intermediate
tags: [pe, asm]
updated: 2026-07-05
---
# STL std::vector Patterns

## Goal
Recognize the common structure and growth behavior of `std::vector` in disassembly or decompiled code.

## Recognition
- Three core pointers or references for begin, end, and capacity.
- A `push_back` or `emplace_back` path that either appends inline or reallocates.
- Copy or move operations that transfer the existing buffer to a larger allocation.

## Internal Mechanism
`std::vector` uses a contiguous buffer, tracking logical size and capacity separately. Growth often triggers reallocation and element copying.

## Assembly Examples
```asm
cmp rdx, [rcx+0x18]
ja .grow
mov [rcx+0x10], rax
```

## Decompiled Examples
```cpp
if (size < capacity) {
    data[size++] = value;
} else {
    grow();
}
```

## Compiler Variations
- The exact field ordering can differ between library implementations.
- The high-level behavior — size/capacity tracking plus growth — is consistent.

## Common Mistakes
- Assuming `std::vector` stores only size and data pointer.
- Missing the distinction between capacity growth and element insertion.

## Reverse Engineering Tips
- Trace `push_back` and `reserve` paths to infer buffer layout.
- Compare several vector instances to identify the size and capacity fields.

## Detection Heuristics
- Pointer arithmetic around a base object that tracks size and capacity.
- Calls to allocator helpers or copy routines during growth.

## Validation Checklist
- [ ] Begin/end/capacity fields are located and named consistently.
- [ ] Fast-path and reallocation paths are observed.

## Related Knowledge
- [pointer-chain](pointer-chain.md)
- [stl-string](stl-string.md)

## Related Recipes
- [Recover_Classes](../recipes/Recover_Classes.md)

## Related Playbooks
- [GameHacking](../playbooks/GameHacking.md)

## References
- STL container ABI notes
- C++ standard library implementation references
