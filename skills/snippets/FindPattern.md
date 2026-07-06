---
title: FindPattern
skill: snippets
category: 
difficulty: intermediate
tags: [pe, gui]
updated: 2026-07-05
---
# FindPattern

## Purpose
Use this snippet when you need a simple, reusable way to locate a byte signature within a memory buffer or mapped module.

## API
The helper accepts a base pointer, a buffer size, a pattern string, and a mask that marks which bytes must match exactly.

## Parameters
- `base`: pointer to the memory region to scan.
- `size`: number of bytes to inspect.
- `pattern`: byte sequence to search for.
- `mask`: wildcard mask where `?` or `x` denotes a byte that should be ignored or matched respectively.

## Return Value
Returns a pointer to the first match, or `nullptr` if no match is found.

## Usage
Use it when you need to identify a known byte sequence in a module, a buffer, or an in-memory structure.

## Error Handling
Check for null buffers, empty sizes, and malformed patterns before scanning.

## Practical Guidance
- Respect page protections and avoid scanning arbitrary memory without validation.
- Treat the helper as a starting point and verify each result with disassembly, runtime evidence, or surrounding context.
- Keep the pattern and mask simple and explicit so the scan is easy to audit later.

## Related Examples
- [pattern-scan.cpp](../examples/cpp/pattern-scan.cpp)

## Related Knowledge
- [pointer-chain](../patterns/pointer-chain.md)
- [GetModule.md](GetModule.md) for module-resolution helpers.
