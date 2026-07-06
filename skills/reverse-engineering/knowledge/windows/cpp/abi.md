---
title: C++ ABI (MSVC)
skill: reverse-engineering
category: knowledge
difficulty: intermediate
tags: [pe, windows, x64, pdb, debug]
updated: 2026-07-05
---
# C++ ABI (MSVC)

Overview of Microsoft C++ ABI details relevant to reverse engineering and type reconstruction on Windows targets.

## Key Points

- Microsoft x64 calling convention: integer and pointer arguments in `rcx, rdx, r8, r9`; shadow space reserved by caller (32 bytes).
- `this` pointer: passed in `rcx` for non-static member functions.
- RTTI layout: MSVC places `_RTTICompleteObjectLocator` and related structures referenced by vtable entries; vtable[-1] commonly points to type information.
- Name mangling: MSVC uses `?`-prefixed decorated names; demangle with `undname` or debugger helpers.

## Practical Tips for RE

- Use RTTI structures to recover class names and inheritance when present; vtable pointers are reliable anchors for class methods.
- When PDBs or debug info is missing, reconstruct class layouts by analyzing vtable usage and constructor/destructor patterns.

## Pitfalls

- Different compilers or older MSVC versions may use different layout details; verify against known binaries when possible.

## Verification Checklist

- [ ] Confirm `this` usage in candidate methods.
- [ ] Cross-reference vtable[-1] with RTTI when available.

## Tools & Commands

- Use PDBs and symbol servers when available to validate RTTI and decorated names.
- Use small test programs to observe layout and vtable behavior for the target compiler version.

## Practical Validation

- Reconstruct a minimal class header from discovered vtable and test by compiling a small program linking against it to confirm ABI assumptions.

## Related Material

- Knowledge: [common-instructions](../../assembly/common-instructions.md)
