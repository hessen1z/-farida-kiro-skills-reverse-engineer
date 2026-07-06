---
title: PDB (Program Database)
skill: reverse-engineering
category: knowledge
difficulty: intermediate
tags: [pe, pdb, gui, debug]
updated: 2026-07-05
---
# PDB (Program Database)

PDB files store debug symbols, type information, and source-file mappings. They are invaluable for recovering names, function prototypes, and class layouts when available.

Key points:
- CodeView RSDS record in PE points to PDB filename, GUID and age. Use this to locate matching PDBs on symbol servers.
- DIA SDK can be used to programmatically read PDBs and extract type information.

Practical:
- When a PDB is available, use it to rename functions and recover class/type layouts.
- If PDB is missing, attempt to match RSDS GUID against symbol servers or ask for a matching build.

Related:
- reverse-engineering/skill.md

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

- Start from the concrete objective and define the expected outcome before applying the workflow.
- Use the related examples, recipes, playbooks, and references as the first implementation reference.
- Keep the guidance grounded in the surrounding skill context and verify the result with available evidence.
- Favor practical, maintainable steps over abstract theory when the document is used in real work.
## Verification Checklist

- Confirm that the main objective is clear and the workflow is actionable.
- Ensure the document points to the most relevant examples, recipes, or playbooks.
- Validate that the terminology is consistent with the rest of the skill.
- Check that the practical guidance is specific enough to be used without further interpretation.

## Further Reading

- DIA SDK documentation and examples for programmatic PDB access
- Microsoft Symbol Server usage notes and best practices
