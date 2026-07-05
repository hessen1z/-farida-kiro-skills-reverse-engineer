# Tail Call Pattern

Goal:
Identify tail-call optimizations where a function ends with a `jmp` to another function instead of `call`+`ret`.

Recognition signs:
- Function epilog followed by `jmp` to another function address instead of `call`.
- No stack growth between the caller and callee; return address is effectively forwarded.

Assembly examples:
- x64:
```
; epilogue omitted
jmp qword ptr [rip + target]
```
- x86:
```
jmp dword ptr [target_table+eax*4]
```

Decompiled equivalent:
```
int wrapper(int a) { return inner(a); } // compiled as tail call
```

Why compiler generates this pattern:
- Saves a stack frame and reduces call overhead when a function returns the result of another function.

Variations across compilers:
- Some compilers emit `jmp` after cleaning up stack manually; others preserve frame pointer semantics.

Common mistakes:
- Treating the callee as unreachable from caller via normal call graph; tail-call still represents control flow.

Reverse engineering tips:
- In IDA/Ghidra, mark as tail-call and propagate types/params manually into the target function.
- When renaming, annotate that the call was tail-optimized to avoid losing semantic meaning.

Detection heuristics:
- A `jmp` instruction at the end of a function with arguments preserved suggests a tail-call.

Related patterns:
- `inline-function.md` (opposite: inlining removes call entirely)

Related knowledge pages:
- knowledge/assembly/compiler-patterns.md
