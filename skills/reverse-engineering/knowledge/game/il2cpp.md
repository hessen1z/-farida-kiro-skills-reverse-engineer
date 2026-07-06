---
title: Il2Cpp / Unity Notes
skill: reverse-engineering
category: knowledge
difficulty: advanced
tags: [pe, unity, gui]
updated: 2026-07-05
---
# Il2Cpp / Unity Notes

This document explains practical steps for reversing Unity games that use IL2CPP (C# -> C++ conversion) and provides guidance for extracting metadata, recovering method bindings, and generating usable SDKs.

## Overview

- IL2CPP transforms managed assemblies into native code and stores metadata in `global-metadata.dat` alongside native images.
- Recovering types and method tables is often the fastest route to a high-quality SDK for analysis and tooling.

## Typical Workflow

1. Extract `global-metadata.dat` from the game package or memory dump.
2. Use tools such as `Il2CppDumper`, `Il2CppInspector`, or `Il2CppReverse` to parse metadata and locate method pointers.
3. Reconstruct method signatures and generate header files or a C++ SDK for easier dynamic analysis.
4. Cross-validate with runtime data (e.g., function pointers discovered via pattern scans) to ensure correct mapping.

## Tools and Tips

- Il2CppDumper: automated metadata parsing and initial symbol generation.
- Il2CppInspector: more advanced type and method analysis with GUI support.
- IDA/Ghidra scripts: align metadata with the disassembly to apply function names and structures.

## Common Pitfalls

- Mismatched Unity/IL2CPP versions: metadata format varies; use a matching tool version.
- Obfuscated assemblies: additional preprocessing may be required to map metadata to runtime structures.

## Verification Checklist

- [ ] Extracted `global-metadata.dat` matches binary version.
- [ ] Generated SDK compiles against test harness or loads in runtime analysis tools.
- [ ] Function pointers reconciled with dynamic symbol discovery.

## Practical Tools & Commands

- `Il2CppDumper` / `Il2CppInspector` for automated metadata parsing and SDK generation.
- Use IDA/Ghidra scripts to apply generated names and structs to the native image.

## Practical Validation

- Build the generated SDK or compile a small test plugin to ensure type layouts and function signatures are correct.
- Cross-check metadata-derived pointers with runtime function pointers discovered via pattern scanning.

## Related Material

- Playbook: [Unity.md](../playbooks/Unity.md)
- Knowledge: [common-instructions](../assembly/common-instructions.md)
