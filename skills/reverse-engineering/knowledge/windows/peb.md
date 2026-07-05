# PEB (Process Environment Block)

The Process Environment Block (PEB) is a user-mode structure that contains
process-wide information used by the Windows loader and runtime. The PEB is
useful in reverse engineering for finding loaded modules, process parameters,
and loader data structures.

Key fields (x64 offsets):
- `PointerToImageBaseAddress` (0x10 from PEB base): module base for the
	process executable.
- `Ldr` (0x18): pointer to `PEB_LDR_DATA` (loaded modules list: InLoadOrder,
	InMemoryOrder, InInitializationOrder).
- `ProcessParameters` (0x20): `RTL_USER_PROCESS_PARAMETERS` (command line,
	environment, current directory, image path).

Access patterns:
- In-process (C/C++): `__readgsqword(0x60)` returns PEB on x64; `__readfsdword(0x30)` on x86.
- From another process: parse the target's TEB/PEB via `NtQueryInformationProcess(ProcessBasicInformation)` or read Remote PEB using `ReadProcessMemory`.

Common usage in RE:
- Locate loaded modules via `PEB->Ldr->InMemoryOrderModuleList` and inspect
	`LDR_DATA_TABLE_ENTRY`'s `DllBase` and `FullDllName`.
- Find command-line and environment strings inside `RTL_USER_PROCESS_PARAMETERS`.
- Detect debuggers or sandboxing by inspecting unusual loader flags or entries.

Related:
- knowledge/windows/teb.md
- knowledge/windows/loader.md

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
