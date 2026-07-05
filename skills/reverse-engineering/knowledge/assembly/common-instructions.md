# Common Instruction Idioms (x86/x64)

Quick reference for assembly idioms encountered during RE.

- Virtual call: `mov rax, [rcx] ; call qword ptr [rax+<slot*8>]` — vtable dispatch.
- Load this pointer: `mov rcx, [rbp+0x8]` or `mov rcx, rdi` depending on calling convention.
- Relative call (static): `call <rel32>` — typical function call; prologue often follows `push rbp ; mov rbp, rsp`.
- Import thunk: small jump to an imported function pointer via IAT slot.

Use these idioms when creating patterns and for quick identification in disassembly.

## Related Material

### Knowledge
- [compiler-patterns](compiler-patterns.md)
- [exceptions](../cpp/exceptions.md)
- [pdb](../cpp/pdb.md)

### Prompts
- [analyze_binary](../../prompts/analyze_binary.md)
- [analyze_crash](../../prompts/analyze_crash.md)
- [analyze_memory](../../prompts/analyze_memory.md)
## Practical Guidance

- Start from the core objective and define the expected outcome before applying the workflow.
- Use the related examples, recipes, and playbooks as the first implementation reference.
- Keep the advice grounded in the surrounding skill context and verify the result against the available evidence.
- Favor practical, maintainable steps over abstract theory when this document is used in real work.
## Verification Checklist

- Confirm that the main objective is clear and the workflow is actionable.
- Ensure the document points to the most relevant examples, recipes, or playbooks.
- Validate that the terminology is consistent with the rest of the skill.
- Check that the practical guidance is specific enough to be used without further interpretation.
