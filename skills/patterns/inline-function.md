# Inline Function Pattern

Goal:
Recognize compiler-inlined functions where the call site contains the callee's body.

Recognition signs:
- Repeated code sequences across multiple call sites (copy of small function body).
- Absence of `call`/`ret` pair; operations performed inline.

Assembly examples:
- x64:
```
; instead of call small_helper
mov rax, [rbx]
add rax, rcx
; inline of helper
```

Decompiled equivalent:
```
int inlined(int a) { return a+5; }
// at call site: performs a+5 inline instead of calling
```

Why compiler generates this pattern:
- Performance: removes call overhead and enables further optimization.

Variations across compilers:
- Aggressive inlining differences: GCC/Clang may inline more aggressively at -O3; MSVC has different heuristics.

Common mistakes:
- Duplicate code across call sites can be mistaken for independent functions — correlate patterns to identify inlining.

Reverse engineering tips:
- Use signature detection to group similar code sequences and propose extracted helper function names.
- Look for identical instruction sequences with same register usage — candidate inlines.

Detection heuristics:
- Repeated short sequences that appear at multiple places; lack of a single call target.

Related patterns:
- `tail-call.md`
- `compiler-patterns.md`

Related knowledge pages:
- knowledge/assembly/common-instructions.md
