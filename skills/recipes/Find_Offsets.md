---
title: Find Offsets
skill: recipes
category: 
difficulty: intermediate
tags: [pe, debug, elf, mach-o]
updated: 2026-07-05
---
# Find Offsets

## Goal
Locate stable offsets for functions, global pointers, or vtable addresses across multiple builds or versions of a target.

## Prerequisites
- A binary or module with enough structure to identify a reliable anchor.
- Basic familiarity with disassembly, cross-references, and pattern scanning.

## Required Knowledge
- Static analysis of PE/ELF/Mach-O layout.
- Basic control-flow and data-reference analysis.

## Required Tools
- IDA/Ghidra or another disassembler.
- A pattern scanner or scripting helper.
- Optional: a debugger for runtime validation.

## Inputs
- One or more binaries or modules.
- A known anchor such as a string, function export, or unique instruction sequence.

## Workflow
1. Identify a reliable anchor and collect its references.
2. Pattern-scan the target binary or module for the anchor.
3. Follow cross-references to the target symbol or data object.
4. Record the offset and verify it against another build or runtime instance.
5. Generate a resilient signature that tolerates minor shifts in surrounding code.

## Expected Output
- A stable offset or signature for the target object.
- Notes on how the offset was validated and under what conditions it remains reliable.

## Validation
- [ ] The anchor is found consistently.
- [ ] The target offset remains stable across the tested builds.
- [ ] The signature is documented with caveats when it is not fully robust.

## Troubleshooting
- If the anchor is unstable, use a more unique instruction sequence or a nearby export.
- If the offset shifts between versions, check for inlining, relocation, or changed layout.

## Related Patterns
- [pointer-chain](../patterns/pointer-chain.md)
- [virtual-call](../patterns/virtual-call.md)

## Related Playbooks
- [GameHacking](../playbooks/GameHacking.md)

## References
- IDA/Ghidra pattern scanning documentation
- Binary analysis references for robust anchor selection
