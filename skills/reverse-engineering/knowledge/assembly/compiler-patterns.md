# Compiler and Optimization Patterns

Recognize compiler-generated patterns and optimization artifacts.

Common patterns:
- Thunks for multiple inheritance: small adjustment then jump (`sub rcx, imm ; jmp addr`).
- Tail calls: `jmp` instead of `call` in epilog — used for inlining or tail-call optimizations.
- Prologue/epilogue variability under optimization: functions may omit frame pointer and use stack pointer arithmetic directly.

Recognition helps avoid mislabeling compiler-generated code as hand-written logic.

## Related Material

### Knowledge
- [common-instructions](common-instructions.md)
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
