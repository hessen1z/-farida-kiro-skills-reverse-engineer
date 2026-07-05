# Memory Manager and Virtual Memory

Windows virtual memory model is central to both static and dynamic RE. Key concepts:

- Virtual address space per-process; regions with `VirtualQuery` described by `MEMORY_BASIC_INFORMATION`.
- Allocation APIs: `VirtualAlloc`, `VirtualAllocEx`, `HeapAlloc`, `HeapCreate`.
- Protection flags: `PAGE_READONLY`, `PAGE_EXECUTE_READ`, `PAGE_GUARD` (guard pages used for stack overflow detection).
- Working set, commit vs reserve: `MEM_COMMIT` vs `MEM_RESERVE`.

In RE:
- Scan only executable, committed regions when searching code patterns (avoid guarded pages).
- Use `VirtualQuery` to enumerate candidate pages for pattern scanning.
- Identify writable/executable regions as potential code injection points.

Related:
- examples/cpp/pattern-scan.cpp
- knowledge/windows/peb.md

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
