---
title: Calling Conventions (Windows x86/x64)
skill: reverse-engineering
category: knowledge
difficulty: intermediate
tags: [pe, windows, x64, gui]
updated: 2026-07-05
---
# Calling Conventions (Windows x86/x64)

This document summarizes common calling conventions encountered on Windows and provides practical notes for recognizing argument passing, callee/caller-saved registers, and differences between architectures.

## Microsoft x64 (Windows x64)

- Argument registers: `rcx`, `rdx`, `r8`, `r9` (first four integer/pointer args).
- Floating-point arguments: passed in XMM registers (xmm0..xmm3) as appropriate.
- Shadow space: caller reserves 32 bytes of stack space (shadow space) before calling; callee may use this space for home locations.
- Return value: `rax` (integer) or `xmm0` (floating point).
- Volatile (caller-saved): `rax`, `rcx`, `rdx`, `r8`, `r9`, `r10`, `r11`.
- Nonvolatile (callee-saved): `rbx`, `rbp`, `rdi`, `rsi`, `r12-r15`.

## Microsoft x86 (stdcall / cdecl /fastcall)

- `cdecl`: caller cleans the stack; arguments pushed right-to-left.
- `stdcall`: callee cleans the stack; used by many Windows APIs.
- `fastcall`: first two arguments in registers (`ecx`, `edx` in MS fastcall), others on stack.

## Calling Convention Detection Tips

- Inspect function prologues/epilogues and register usage at call sites to infer conventions.
- For member functions, `this` is typically a register argument (`ecx` on x86 fastcall, `rcx` on x64).

## Practical Guidance

- Use consistent assumptions about calling conventions when naming function parameters during analysis, update when evidence contradicts.
- Annotate likely calling conventions in your disassembly to make future work easier.

## Verification Checklist

- [ ] Identified calling convention for core functions used in analysis.
- [ ] Annotated `this` and common register-based arguments where present.

## Tools & Commands

- Use small instrumented test programs compiled with target compiler to validate calling conventions and register assignments.
- Use WinDbg to inspect stack frames and register values at function entry to confirm conventions in binaries.

## Practical Validation

- Validate calling convention assumptions by observing real call sites and adjusting prototypes in the disassembler when needed.

## Related Material

- Knowledge: [common-instructions](../../assembly/common-instructions.md)
