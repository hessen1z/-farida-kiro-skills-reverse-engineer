# Source Engine Notes

Quick notes for reversing games built on Valve's Source engine.

Key artifacts:
- Interface discovery: `CreateInterface("VEngineClient"...)` and similar exports — search for `CreateInterface` strings.
- VTables and virtual functions are used extensively for engine hooks.

Recovery tips:
- Find `VTable` names via RTTI or exported symbols in linked modules.
- Use pattern-scan to find global interface pointers (e.g., `g_pEngine`).

Related:
- recipes/Find_Offsets.md

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

- Start from the core objective and define the expected outcome before applying the workflow.
- Use the related examples, recipes, and playbooks as the first implementation reference.
- Keep the advice grounded in the surrounding skill context and verify the result against the available evidence.
- Favor practical, maintainable steps over abstract theory when this document is used in real work.
## Verification Checklist

- Confirm that the main objective is clear and the workflow is actionable.
- Ensure the document points to the most relevant examples, recipes, or playbooks.
- Validate that the terminology is consistent with the rest of the skill.
- Check that the practical guidance is specific enough to be used without further interpretation.
