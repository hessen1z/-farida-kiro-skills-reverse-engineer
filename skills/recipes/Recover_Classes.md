---
title: Recover Classes
skill: recipes
category: 
difficulty: intermediate
tags: [pe, pdb, debug]
updated: 2026-07-05
---
# Recover Classes

## Goal
Reconstruct C++ class definitions, vtables, and inheritance relationships from a binary so they can be used in tooling or documentation.

## Prerequisites
- A binary with RTTI, vtables, or recognizable class-like structures.
- Experience with disassembly and data structure recovery.

## Required Knowledge
- C++ object layout and vtable concepts.
- RTTI and constructor/destructor analysis.

## Required Tools
- IDA/Ghidra with RTTI support.
- ReClass or another structure editor.
- Optional: a debugger for runtime validation.

## Inputs
- The target binary or module.
- Optional symbols, PDBs, or a known class hierarchy from a related build.

## Workflow
1. Locate RTTI structures and `_RTTICompleteObjectLocator` entries.
2. Find vtable objects in read-only data and enumerate their function pointers.
3. Collect call sites and cross-references to group methods into candidate classes.
4. Infer inheritance using RTTI and constructor/destructor chains.
5. Create struct definitions with field offsets observed from member accesses.
6. Rename functions and export the recovered layout for further use.

## Expected Output
- A reconstructed class layout or set of candidate class definitions.
- A set of mapped vtable entries and inheritance observations.

## Validation
- [ ] Vtables and functions are assigned consistently.
- [ ] Inheritance chains are supported by constructor or RTTI evidence.
- [ ] Recovered layouts fit observed runtime behavior.

## Troubleshooting
- If RTTI is missing, rely on vtable layout, constructor chains, and object access patterns.
- If field offsets are ambiguous, validate them with dynamic instrumentation or runtime inspection.

## Related Patterns
- [constructor](../patterns/constructor.md)
- [virtual-call](../patterns/virtual-call.md)

## Related Playbooks
- [GameHacking](../playbooks/GameHacking.md)

## References
- Microsoft C++ ABI documentation
- ReClass and RTTI analysis references
