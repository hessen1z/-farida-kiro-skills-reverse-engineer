---
title: Syscalls and Native API
skill: reverse-engineering
category: knowledge
difficulty: intermediate
tags: [pe, windows, asm, x64, unity, gui, kernel, dll]
updated: 2026-07-05
---
# Syscalls and Native API

Syscalls are the boundary into kernel mode. On x64 Windows, user-mode `ntdll` stubs typically use the `syscall` instruction with a syscall number in `rax`.

Notes:
- Syscall numbers vary by Windows version; do not assume fixed values — consult matching OS tables when using direct syscall patterns.
- Direct syscalls bypass user-mode hooks that monitor `kernel32`/`ntdll` wrappers.

Recognition:
- Short stubs that move an immediate into `eax/rax` and `syscall`/`int 0x2e`.
- Patterns: `mov r10, rcx ; mov eax, <sysno> ; syscall ; ret` is common on x64.

Practical:
- When you find a syscall stub, map the syscall number to an OS version if possible (use symbol servers or known tables).

## Mapping and Instrumentation

- To map syscall numbers: collect `ntdll` exports from the same OS build or consult published syscall tables for the target Windows version.
- Use runtime tracing (ETW, Sysmon) or kernel tracing to observe syscall use in context to validate behavior.

## Detection and Analysis Tips

- Detect direct syscalls by searching for the `syscall` instruction sequences in `ntdll` or inline stubs.
- Correlate found syscall numbers with function names using symbol servers or by referencing authoritative syscall tables.

## Example: extract syscall number (pseudo)

```asm
mov r10, rcx
mov eax, 0x3A   ; syscall number
syscall
ret
```

If inline numbers are used, confirm against OS-specific tables before drawing conclusions.

## Tools

- `ntdll` export analysis tools, `sc.exe`, `windbg` with symbol servers, and community syscall tables.


Related:
- knowledge/windows/ntdll.md

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
