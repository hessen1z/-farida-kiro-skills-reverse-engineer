---
title: Decompilers
skill: binary-analysis
category: knowledge
difficulty: intermediate
tags: [pe, pdb, gui, debug, elf]
updated: 2026-07-05
---
# Decompilers

## Overview

Decompilers attempt to reconstruct high-level code from compiled binaries. They are a vital complement to disassembly, providing readable control flow, types, and program structure.

## Internal Design

Decompilers typically perform:
- Control flow graph reconstruction
- Type inference
- Data flow analysis
- Expression simplification
- Program reconstruction

## Reverse Engineering Notes

- Decompiler output is an approximation of source code.
- Always validate decompiled results against the original assembly.

## Debugging Notes

- Decompiled code may omit compiler optimizations and inline expansions.

## Common Mistakes

- Treating decompiled output as exact source code.

## References

- Ghidra, IDA, Hex-Rays architecture

## Related Material

### Knowledge
- [demangling](demangling.md)
- [disassemblers](disassemblers.md)
- [dwarf](dwarf.md)

### Patterns
- [encrypted-string](../patterns/encrypted-string.md)
- [export-table](../patterns/export-table.md)
- [import-table](../patterns/import-table.md)

### Recipes
- [analyze-binary](../recipes/analyze-binary.md)
- [recover-exports](../recipes/recover-exports.md)
- [recover-imports](../recipes/recover-imports.md)

### Playbooks
- [analyze-elf](../playbooks/analyze-elf.md)
- [analyze-packed-binary](../playbooks/analyze-packed-binary.md)
- [analyze-pe](../playbooks/analyze-pe.md)

### References
- [elf](../references/elf.md)
- [intel](../references/intel.md)
- [microsoft](../references/microsoft.md)

### Rules
- [rule](../rules/rule.md)

### Prompts
- [analyze-binary](../prompts/analyze-binary.md)

### Checklists
- [checklist](../checklists/checklist.md)
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

## Choosing and Using a Decompiler

- Pick a decompiler that integrates with your disassembler (Hex-Rays with IDA, Ghidra Decompiler, Snowman, RetDec) and matches the target architecture.
- Use decompiler output to guide type recovery and function signatures, but cross-check with raw disassembly for correctness.
- Annotate and iteratively improve types: small type fixes (pointer-sizes, structs) can dramatically improve subsequent output.

## Common Pitfalls and Mitigations

- Incorrect types: prefer conservative types and incrementally refine them.
- Optimized code artifacts: expect inlined functions and missing stack frames; annotate manually when needed.
- Compiler intrinsics and platform-specific ABI quirks: validate calling conventions and special registers.

## Tooling Tips

- Use symbol servers and PDBs when available to seed decompilation with correct symbols.
- Export decompiler output for diffing across versions to identify patched or obfuscated regions.

## Example Workflow

1. Load binary into disassembler and run the decompiler.
2. Identify key functions and apply conservative prototypes.
3. Correct types and re-run decompilation iteratively.
4. Validate behavioral expectations against known-good samples or runtime traces.

## Verification Checklist (extended)

- Confirm decompiler output aligns with disassembly for critical control-flow and API calls.
- Validate inferred types against runtime memory observations when possible.
- Document any decompiler-specific workarounds applied during analysis.
