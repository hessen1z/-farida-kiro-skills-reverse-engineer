---
title: C++ Exceptions and SEH
skill: reverse-engineering
category: knowledge
difficulty: intermediate
tags: [pe, windows, x64, pdb, gui, dll]
updated: 2026-07-05
---
# C++ Exceptions and SEH

C++ exceptions (language-level) and Structured Exception Handling (SEH) are distinct but interoperable on Windows. Understanding unwind metadata and exception handling is important for control-flow recovery.

Topics:
- SEH: frame-based chained exception handlers (older) and table-based EH for x64.
- C++ EH (MSVC) uses unwind info and exception tables to locate handlers and perform stack unwinding.

Practical:
- Examine `.pdata` and `.xdata` for unwind info on x64 — useful to recover function prologues and epilogues.
- Exceptions may be used by packers or obfuscators to hide control flow; inspect handlers for hooks.

Related:
- knowledge/windows/ntdll.md
- patterns/exception.md

## Related Material

### Knowledge
- [common-instructions](../assembly/common-instructions.md)
- [compiler-patterns](../assembly/compiler-patterns.md)
- [pdb](pdb.md)

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

- Inspect `.pdata`/`.xdata` with IDA/Ghidra or `llvm-objdump` to enumerate unwind entries.
- Use WinDbg's `!exchain` and `!analyze -v` to explore exception contexts in crashes.

## Practical Validation

- Verify unwind and handler discovery by triggering controlled exceptions in a test harness and confirming stack traces.
- Document any manual adjustments made to exception tables during reconstruction.
