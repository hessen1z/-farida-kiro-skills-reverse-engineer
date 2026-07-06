---
title: Unity / Il2Cpp Notes
skill: reverse-engineering
category: knowledge
difficulty: advanced
tags: [pe, unity, gui]
updated: 2026-07-05
---
# Unity / Il2Cpp Notes

Practical guide for working with Unity games that use IL2CPP. Focuses on metadata extraction, type reconstruction, and generating usable SDKs for analysis and tooling.

## Workflow Summary

1. Locate `global-metadata.dat` in the game package or memory.
2. Use `Il2CppDumper`/`Il2CppInspector` to extract type tables and function pointers.
3. Generate headers or an SDK and validate against runtime function pointers.

## Tools

- Il2CppDumper — automated extraction and symbol mapping.
- Il2CppInspector — advanced reconstruction with type analysis.
- IDA/Ghidra scripts to apply recovered symbols to the disassembly.

## Common Problems

- Version mismatch between tools and IL2CPP runtime; check Unity version and tool compatibility.
- Obfuscation or stripped metadata requires additional heuristics and manual validation.

## Verification Checklist

- [ ] Metadata extracted successfully and matches runtime image.
- [ ] Generated SDK compiles or is usable by dynamic instrumentation.

## Related Material

- Knowledge: [il2cpp](../game/il2cpp.md)
