---
title: Memory Manager and Virtual Memory
skill: reverse-engineering
category: knowledge
difficulty: intermediate
tags: [pe, windows, gui, kernel, debug, dll]
updated: 2026-07-05
---
# Memory Manager and Virtual Memory

Windows virtual memory is a foundational topic for both static and dynamic reverse engineering. This page summarizes essential concepts, practical diagnostics, and common pitfalls when working with process memory.

## Key Concepts

- Virtual address space: each process has a private address space that can be queried with `VirtualQuery` to obtain `MEMORY_BASIC_INFORMATION` structures.
- Allocation APIs: `VirtualAlloc/VirtualAllocEx`, heap APIs (`HeapAlloc`), and file-mapping APIs (`CreateFileMapping`/`MapViewOfFile`).
- Protection flags: `PAGE_READONLY`, `PAGE_READWRITE`, `PAGE_EXECUTE_READ`, `PAGE_GUARD`.
- Commit vs Reserve: `MEM_COMMIT` allocates physical backing, `MEM_RESERVE` reserves address space without commitment.

## Practical Diagnostics

- Enumerate memory regions using `VirtualQueryEx` to locate executable regions for pattern scanning.
- Use tools like Process Hacker, VMMap, or WinDbg to inspect memory maps and protection flags.
- For live analysis, be careful with guarded or inaccessible pages that may trigger exceptions when read.

## Practical Guidance

- Use page-protection checks and guard-page heuristics when inspecting process memory.
- For forensic dumps, map virtual addresses to their backing files and scan mapped sections for code/data.

## Tools & Commands

- Use WinDbg commands (`!address`, `!vad`) to inspect memory layout and protections.
- Use `vmmap`-style tools to enumerate virtual memory regions and backing files.

## Validation Checklist

- Confirm that suspicious code regions are actually executable and not stale data.
- Validate that relocations and imported thunks reside in expected sections.

## For Reverse Engineering

- When scanning for code patterns, prefer committed, executable regions and skip guard pages.
- Identify RWX regions which are suspicious and often indicate code injection or JIT-generated code.
- Map DLL sections (code vs data) using PE headers to focus static analysis on likely code areas.

## Tools

- WinDbg (kernel and user-mode debugging)
- Process Hacker / VMMap for memory inspection
- Custom pattern-scan tools that respect page protections

## Common Mistakes

- Touching guard pages or guarded stacks during automated scanning — handle exceptions gracefully.
- Assuming read access to all regions; use safe reads and handle access violations.

## Verification Checklist

- [ ] Enumerated memory regions and identified executable, committed pages.
- [ ] Confirmed no guard/access violation occurred during scanning.
- [ ] Validated suspicious RWX regions with runtime evidence.

## Related Material

- Examples: examples/cpp/pattern-scan.cpp
- Knowledge: [peb](../peb.md)
