# String Pattern

Goal:
Recognize common string handling idioms and small-string-optimization patterns.

Recognition signs:
- Calls to `strlen`, `strcmp`, `memcpy`, `memmove`, `strcpy`, and `wcslen`.
- Small String Optimization (SSO): inline buffer comparisons and moves within object.

Assembly examples:
- strcmp-like pattern:
```
.Lcmp:
mov al, [rdi]
cmp al, [rsi]
je .Lnext
; loop
```

Decompiled equivalent:
```
int strcmp(const char* a, const char* b) { while (*a && *a==*b) { ++a; ++b; } return *a - *b; }
```

Why compiler generates this pattern:
- Common library functions for performance and correctness.
- SSO avoids heap allocation for short strings.

Variations across compilers:
- Implementation differences in SSO buffer size and layout.

Common mistakes:
- Mistaking SSO inline buffer moves for custom copy routines — check object layout.

Reverse engineering tips:
- Identify SSO by locating fixed-size inline buffers in `std::string` objects (MSVC SSO typically 15 bytes + null on x64).
- Use data cross-references to find usages of string functions and constants.

Detection heuristics:
- Repeated sequences of byte-wise compare and branch; calls to libc string functions.

Related patterns:
- `stl-string.md`

Related knowledge pages:
- knowledge/cpp/stl.md
