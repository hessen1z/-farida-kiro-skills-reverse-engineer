# Loop Pattern

Goal:
Detect common loop constructs and identify loop boundaries for analysis and pattern matching.

Recognition signs:
- Backward conditional or unconditional jumps in code (e.g., `jmp` to an earlier address).
- Typical prologue: initialization of counter/index; loop body; increment; condition and branch back.

Assembly examples:
- Simple for-loop (x64):
```
mov ecx, 0
.Ltop:
cmp ecx, esi
jge .Lend
; body
inc ecx
jmp .Ltop
.Lend:
```

Decompiled equivalent:
```
for (int i=0;i<n;i++) { ... }
```

Why compiler generates this pattern:
- Direct translation of loop constructs; compilers may unroll loops or transform into vectorized code.

Variations across compilers:
- Unrolling, loop fusion, or transforming loops into `rep` prefixed string operations for memcpy-like bodies.

Common mistakes:
- Mistaking exception-driven backward jumps for loops; verify index/register usage.

Reverse engineering tips:
- Identify loop invariant code vs. variant code; hoist invariants to understand body effects.
- Use IDA/Ghidra's loop recognition/decompilation to reconstruct high-level loops.

Detection heuristics:
- Backward jumps and a small distance between jump target and source.

Related patterns:
- `inline-function.md` (inlining may remove small loop calls)

Related knowledge pages:
- knowledge/assembly/common-instructions.md
