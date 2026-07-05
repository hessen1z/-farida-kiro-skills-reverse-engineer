---
name: Binary Analysis
version: 1.0
priority: critical
requires:
  - shared
  - analysis-engine
  - windows-internals
tags:
  - binary
  - pe
  - elf
  - mach-o
  - pdb
  - reverse-engineering
  - packers
  - debuggers
description: Core binary analysis skill covering executable formats, loader behavior, symbol recovery, relocation handling, anti-analysis protections, packers, disassemblers, and decompilers.
---

# Binary Analysis Skill

## Purpose
Deliver a production-grade reference and operational skill set for analyzing native binaries across Windows, Linux, and macOS. This skill encompasses executable file formats, loader behavior, debug metadata, symbol recovery, obfuscation, anti-analysis protections, and practical reverse engineering workflows.

## Scope
This skill covers:
- Binary format internals for PE, ELF, and Mach-O.
- Loader semantics, memory mapping, relocations, import/export resolution, TLS, and resources.
- Debug information formats including PDB, DWARF, and symbol recovery techniques.
- Packers, protectors, unpacking workflows, and anti-debug / anti-disassembly techniques.
- Static and dynamic binary analysis using disassembly, decompilation, and debugger-assisted inspection.
- Cross-platform differences and compiler artifacts relevant to native analysis.

## What this skill provides
- Deep executable format knowledge and file layout analysis.
- Practical workflows for identifying and recovering symbols, imports, exports, and runtime metadata.
- Guidance for reversing packed or protected binaries and reconstructing loader behavior.
- Best practices for combining static format analysis with dynamic debugger evidence.
- Templates for documenting findings, mapping runtime memory, and validating hypotheses.

## Knowledge areas
- Portable Executable (PE) structure and Windows loader behavior.
- Import Address Table (IAT), Export Directory, base relocations, TLS, resources, and debug directories.
- Program Database (PDB) recovery, public symbols, and private debug metadata reconstruction.
- Packed binaries, stub loaders, virtualized code, runtime unpacking, and common packer signatures.
- Disassembler-to-decompiler workflows for accurate function recovery and type reconstruction.

## Core capabilities
- Identify binary format and classify executable artifacts quickly.
- Map file layout to runtime memory layout and loader actions.
- Recover imports, exports, and symbol metadata from stripped binaries.
- Diagnose relocation failures, TLS initialization order issues, and loader exceptions.
- Detect and analyze packers, protectors, and anti-analysis techniques.
- Produce repeatable analysis reports with references to relevant patterns, recipes, and examples.

## Prerequisites
- `shared` — documentation, templates, and conventions.
- `analysis-engine` — evidence-driven reasoning and verification.
- `windows-internals` — operating system loader behavior and runtime constraints.

## Used by
- `reverse-engineering` — to recover functions, classes, and binary semantics.
- `examples` — to create runnable parsers, scanners, and loader verification code.
- `recipes` — to define repeatable recovery workflows for symbols, imports, and packed code.
- `playbooks` — to describe scenario-based analysis such as packed malware or crash investigation.

## Related Skills
- `reverse-engineering` — applies binary insights to concrete reconstruction tasks.
- `assembly` — interprets instruction streams after format parsing.
- `cpp` — maps runtime artifacts to source-level types and compiler-generated structures.
- `shared` — uses shared style and template rules for documentation.

## Entry Conditions
- A native binary, executable image, or dump requires format analysis.
- A crash, protection, or symbol-recovery task needs loader and metadata reconstruction.
- A packed, obfuscated, or stripped target requires structural reasoning beyond disassembly alone.

## Exit Conditions
- The binary format and loader behavior are fully documented.
- Imports, exports, relocations, resources, and debug metadata have been classified.
- Protection and packing mechanisms are identified and an unpacking or analysis plan exists.
- Core findings are linked to evidence, examples, and verification steps.

## Typical Workflow
1. Identify the file format using magic bytes and header fields.
2. Parse the high-level layout: headers, sections, data directories, and metadata regions.
3. Map file offsets to virtual addresses and loader-mapped memory.
4. Analyze import/export metadata, relocation tables, TLS, and debug directories.
5. Examine symbol and debug metadata to recover names and types.
6. Detect packers, stub loaders, and anti-analysis artifacts.
7. Validate assumptions with dynamic evidence from debuggers or runtime dumping.
8. Document the analysis, cross-link to patterns, and produce a repeatable recipe.

## Deliverables
- `knowledge/pe.md`, `knowledge/imports.md`, `knowledge/exports.md`, `knowledge/pdb.md`, `knowledge/packers.md`, and related knowledge documents.
- Pattern recognition files for import tables, export tables, packers, and anti-analysis techniques.
- Recipes for recovering imports, exports, PDB data, and unpacking protected binaries.
- Playbooks for analyzing packed executables, debugging loader failures, and reconstructing stripped modules.

## Notes
- Prioritize practical examples and code snippets that map directly to real-world reverse engineering tasks.
- Use cross-links liberally to connect format analysis with patterns, recipes, and debugger workflows.
- Keep theoretical explanations grounded in observable binary artifacts and loader effects.

## Related Material

- Knowledge: [decompilers](knowledge/decompilers.md)
- Patterns: [encrypted-string](patterns/encrypted-string.md)
- Recipes: [analyze-binary](recipes/analyze-binary.md)
- Playbooks: [analyze-elf](playbooks/analyze-elf.md)
- References: [elf](references/elf.md)
- Rules: [rule](rules/rule.md)
- Prompts: [analyze-binary](prompts/analyze-binary.md)
- Checklists: [checklist](checklists/checklist.md)

