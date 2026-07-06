---
title: Registers
skill: reverse-engineering
category: knowledge
difficulty: intermediate
tags: [pe, windows, x64, debug]
updated: 2026-07-05
---
# Registers

Reference for common register roles and practical tips for Windows analysis (x86/x64).

## x64 General Register Roles

- `rax`: return value / volatile
- `rcx`, `rdx`, `r8`, `r9`: argument registers (MS x64)
- `rbx`, `rbp`, `r12-r15`: callee-saved (nonvolatile)
- `rsp`: stack pointer (must be preserved across calls)

## x86 Common Registers

- `eax`, `edx`, `ecx`: volatile / common return and argument registers depending on convention
- `ebx`, `ebp`, `esi`, `edi`: nonvolatile on many calling conventions

## Register Usage Tips

- When reconstructing function signatures, track which registers hold values at call sites and which are preserved across calls.
- Use the register usage patterns to identify `this` pointers, return buffers, and hidden parameters (e.g., _StructRet_). 

## Examples

- Detect `this` parameter: look for `mov rcx, <value>` directly before calls in member function contexts.
- Return buffer pattern (C++): pointer passed in `rcx`/`rdi` depending on ABI—look for writes to the buffer at function end.

## Verification Checklist

- [ ] Annotated key registers for analyzed functions.
- [ ] Verified register assumptions against runtime traces or symbol data.

## Tools & Commands

- Use dynamic tracing (Intel PT, ETW) and debuggers (WinDbg) to observe register state across calls.
- Use disassembler emulation or Capstone-based test harnesses to validate register flow across candidate functions.

## Practical Validation

- Confirm inferred register roles by instrumenting function calls in a test harness and logging register values at entry/exit.

## Related Material

- Knowledge: [calling-conventions](calling-conventions.md)
