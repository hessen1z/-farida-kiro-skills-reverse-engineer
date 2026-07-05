# STL Containers (Layouts and Common Patterns)

Common STL containers encountered in binaries: `std::vector`, `std::string`, `std::list`, `std::map`.

Notes:
- `std::vector<T>` (MSVC): typically three pointers (begin, end, capacity_end) or two pointers with size in implementation-dependent variants.
- `std::string` uses Small String Optimization (SSO) — short strings stored inline, longer strings on heap.

Recognition in assembly:
- `push`/`call` sequences that allocate (`operator new`) followed by construction patterns indicate container creation.
- Reallocation or growth patterns call `reserve`/`realloc` sequences (copy/move loops).

Related:
- patterns/stl-vector.md
- patterns/stl-string.md

## Related Material

### Knowledge
- [common-instructions](../assembly/common-instructions.md)
- [compiler-patterns](../assembly/compiler-patterns.md)
- [exceptions](exceptions.md)

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
