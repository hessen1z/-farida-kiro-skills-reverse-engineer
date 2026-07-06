---
title: Common Instruction Idioms (x86/x64)
skill: reverse-engineering
category: knowledge
difficulty: intermediate
tags: [pe, windows, x64, pdb]
updated: 2026-07-05
---
# Common Instruction Idioms (x86/x64)

This reference collects common assembly idioms and small patterns that frequently appear during reverse engineering of x86 and x64 binaries. Use these patterns to speed identification of constructs such as vtables, thunks, calling convention boundaries, and compiler-generated helpers.

## Common Idioms

- Virtual call (vtable dispatch):
	- mov rax, [rcx]
	- call qword ptr [rax + <slot*8>]
	- Interpretation: `rcx` is `this`; load vtable pointer then call slot. Look for nearby RTTI or type descriptors.
- 'This' pointer loads:
	- `mov rcx, [rbp+0x8]` (stack-based, non-leaf) or `mov rcx, rdi` (parameter passed in register for Microsoft x64)
- Relative (direct) call:
	- `call <rel32>` — static call into code section. Often followed by a standard prologue (`push rbp; mov rbp, rsp`) or omitted under optimizations.
- Import thunk / IAT jump:
	- `jmp qword ptr [rip + <iat_offset>]` (x64) or `jmp dword ptr [rel32]` (x86) — indicates an imported API call.
- Tail call / tail jump:
	- `jmp <target>` at function epilog indicates a tail-call optimization or thunk.
- Stack-adjusting leaf functions:
	- `sub rsp, imm; ...; add rsp, imm; ret` — common in leaf optimized functions.

## Idioms to watch for (analysis heuristics)

- Small constant-lookups or switch tables: `lea rax, [rip + .Lswitch]; mov rax, [rax + rdx*8] ; jmp rax` — indicates jump table/switch.
- Exception unwind and frame setup: patterns referencing `.pdata` and `.xdata` (Windows) hint at structured exception handling.
- Import resolver thunks and delay-load stubs: these are useful anchors when reconstructing IAT and import tables.

## Usage Tips

- When creating pattern signatures, prefer function-level anchors (prologue/epilog) combined with unique instruction sequences rather than single-instruction matches.
- Cross-check suspected vtable slots against RTTI structures or string references to confirm type semantics.
- Use sample binaries with known symbols to validate your pattern detection and adjust heuristics for compiler variance.

## Examples

- Vtable detection: look for consecutive memory loads and indirect calls in constructor/destructor clusters.
- Thunk detection: single-instruction `jmp` or short `mov; jmp` sequences near imported symbols.

## Tools

- IDA Pro / Ghidra: graph view and cross-references make identifying calls and thunks practical.
- objdump / r2 / radare2: lightweight inspection and batch analysis of instruction sequences.

## Verification Checklist

- Confirm pattern reliability against multiple compiler optimization levels.
- Ensure patterns do not trigger false positives on common library prologues.

## Tools & Commands

- Use `grep`/`rabin2`/`radare2` to locate instruction sequences in bulk across a codebase.
- Use IDA/Ghidra scripting to automatically tag vtable-like patterns and generate candidate lists.

## Practical Validation

- Test patterns against multiple compilers and optimization levels; maintain a small corpus of labeled samples for regression testing.
- When in doubt, validate suspected matches using runtime evidence (breakpoints, memory inspection).

## Related Material

- Knowledge: [compiler-patterns](compiler-patterns.md), [pdb](../cpp/pdb.md)
- Prompts: [analyze_binary](../../prompts/analyze_binary.md), [analyze_crash](../../prompts/analyze_crash.md)
