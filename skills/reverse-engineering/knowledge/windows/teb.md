# TEB (Thread Environment Block)

The Thread Environment Block (TEB) stores thread-local information such as
exception lists, thread-local storage (TLS), stack limits, and a pointer to
the owning thread's PEB. The TEB is useful for locating per-thread data and
thread-specific state during dynamic analysis.

Key fields (x64 offsets):
- `EnvironmentPointer` / `ProcessEnvironmentBlock` (PEB pointer) at offset 0x60.
- `ThreadLocalStoragePointer` / `TlsSlots` — locate TLS entries for modules.
- `ExceptionList` — head of SEH chain (when applicable).
- `StackBase` / `StackLimit` — helpful for scanning stack frames and saved registers.

Access:
- On x64, the TEB is reachable via the GS segment: `__readgsqword(0x30)`.
- On x86, use FS: `__readfsdword(0x18)`.

Uses in RE:
- Inspect TLS entries to find module-specific data or function pointers.
- Walk the SEH chain for exception-driven control flow or exploit analysis.
- Read `StackBase`/`StackLimit` to bound stack dumps and avoid scanning beyond valid memory.

Related:
- knowledge/windows/peb.md
- patterns/pointer-chain.md

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
