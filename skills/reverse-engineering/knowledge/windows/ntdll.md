---
title: ntdll internals
skill: reverse-engineering
category: knowledge
difficulty: intermediate
tags: [pe, windows, loader, malware, gui, kernel, dll]
updated: 2026-07-05
---
# ntdll internals

`ntdll.dll` is the primary user-mode interface for Native API (Nt* calls) and
contains syscall stubs, runtime helpers, and structures used across Windows.

Key topics:
- Syscall stubs: `ntdll` provides small wrappers that issue `syscall`/`int 0x2e` and jump into kernel.
- Exported helpers: `Rtl*` functions (heap, string, memory, RTL data structures).
- Exception handling helpers and unwind metadata live in `ntdll`.

Why it's useful in RE:
- Many malware/packers call syscalls directly; recognizing syscall stubs helps identify kernel interaction.
- `Rtl` helpers often show consistent patterns for memory and string operations; reuse across binaries.

Related:
- knowledge/windows/syscalls.md
- knowledge/windows/loader.md
# ntdll internals

Notes about ntdll exports, syscalls, and common assembly patterns.

## Related Material

### Knowledge
- [common-instructions](../assembly/common-instructions.md)
- [compiler-patterns](../assembly/compiler-patterns.md)
- [exceptions](../cpp/exceptions.md)

### Prompts
- [analyze_binary](../../prompts/analyze_binary.md)
- [analyze_crash](../../prompts/analyze_crash.md)
- [analyze_memory](../../prompts/analyze_memory.md)
## Practical Guidance

- Start from the concrete objective and define the expected outcome before applying the workflow.
- Use the related examples, recipes, playbooks, and references as the first implementation reference.
- Keep the guidance grounded in the surrounding skill context and verify the result with available evidence.
- Favor practical, maintainable steps over abstract theory when the document is used in real work.
## Verification Checklist

- Confirm that the main objective is clear and the workflow is actionable.
- Ensure the document points to the most relevant examples, recipes, or playbooks.
- Validate that the terminology is consistent with the rest of the skill.
- Check that the practical guidance is specific enough to be used without further interpretation.

## Tools & Commands

- Use `dumpbin /EXPORTS`, `r2`, or IDA/Ghidra export viewers to enumerate `ntdll` exports for the target OS.
- Use symbol servers and OS-matching `ntdll` to map syscall numbers to named APIs.

## Practical Tips

- When you see short syscall stubs, correlate the immediate syscall number with the correct OS build before assuming identity.
- Use `Rtl` family function patterns to infer memory and string handling strategies used by a binary.
