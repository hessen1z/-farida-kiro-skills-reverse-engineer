# Object Manager (Handles and Kernel Objects)

The Object Manager is a kernel component that manages named kernel objects and handle tables. In user-mode RE you will mostly interact via handles returned by Win32 API, but understanding object types and semantics helps with behavioral analysis.

Key concepts:
- Handles: opaque values referencing kernel objects (events, mutexes, files, sections).
- Object types: `File`, `Event`, `Section`, `Device`, `Thread`, etc.
- Named objects: visible under `\BaseNamedObjects` or `\Sessions` namespace — useful for IPC detection.

Use in RE:
- Search for CreateFile/CreateEvent/CreateMutex calls and look for named objects indicating IPC or persistence.
- Device objects (`CreateFile("\\.\\DeviceName")`) indicate kernel-mode drivers or special interfaces.

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
