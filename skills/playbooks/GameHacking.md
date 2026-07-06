---
title: Playbook: Game Hacking
skill: playbooks
category: 
difficulty: intermediate
tags: [pe, unity]
updated: 2026-07-05
---
# Playbook: Game Hacking

Objective: Provide a reliable sequence to analyze a game binary, discover runtime structures, and generate an SDK for tooling or modding.

## Steps

1. Recon: collect version, build ID, and platform-specific packaging info.
2. Strings and exports: locate meaningful strings, `CreateInterface`-like factories, and exported helpers.
3. Memory maps: enumerate runtime memory regions and locate global pointers.
4. Find offsets: identify vtables, objects, and common global pointers with pattern-scan.
5. Recover types: reconstruct classes, enums, and data structures.
6. Generate SDK: produce headers and minimal stubs for instrumentation.
7. Validate: run small test harness to ensure offsets and function prototypes match runtime.

## Tools

- IDA/Ghidra, Il2CppDumper (Unity), ReClass, pattern-scan utilities

## Verification Checklist

- [ ] Global pointers and vtables discovered.
- [ ] Generated SDK validated against runtime.

