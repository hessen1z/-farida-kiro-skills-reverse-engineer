---
title: STL std::string Patterns
skill: patterns
category: 
difficulty: intermediate
tags: [pe, asm]
updated: 2026-07-05
---
# STL std::string Patterns

## Goal
Recognize the common layout and behavior of `std::string` implementations during reverse engineering.

## Recognition
- Small-string optimization where short strings are stored in an inline buffer.
- Heap allocation for long strings and a pointer/size/capacity layout.
- Constructor and destructor paths that branch based on string length.

## Internal Mechanism
`std::string` often uses an inline buffer for short values and switches to heap allocation for larger values, which changes the structure and code path used by methods.

## Assembly Examples
```asm
cmp r8d, 0x10
ja .alloc
mov [rcx+0x10], rax
```

## Decompiled Examples
```cpp
std::string s = "abc";
```

## Compiler Variations
- The inline buffer size and exact field ordering can vary between MSVC, libc++, and libstdc++.
- The high-level behavior remains similar across major implementations.

## Common Mistakes
- Assuming a `std::string` always uses heap storage.
- Failing to note the difference between a small-string fast path and a heap-backed representation.

## Reverse Engineering Tips
- Correlate constructor and destructor code paths to identify which storage strategy is active.
- Compare multiple instances to infer the inline buffer size and ownership semantics.

## Detection Heuristics
- Branches based on string length or capacity in constructors and assignments.
- Deallocation calls in destructors for heap-backed strings.

## Validation Checklist
- [ ] The inline buffer strategy is identified where applicable.
- [ ] Heap-backed paths and deallocation logic are confirmed.

## Related Knowledge
- [stl-vector](stl-vector.md)

## Related Recipes
- [Recover_Classes](../recipes/Recover_Classes.md)

## Related Playbooks
- [GameHacking](../playbooks/GameHacking.md)

## References
- STL implementation notes for MSVC and libc++
- ABI references for common C++ standard library layouts
