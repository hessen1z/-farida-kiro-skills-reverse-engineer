---
title: GetPEB
skill: snippets
category: 
difficulty: intermediate
tags: [pe, windows, x64, gui]
updated: 2026-07-05
---
# GetPEB

## Purpose
This snippet shows how to retrieve the Process Environment Block for the current process on Windows x64.

```cpp
PPEB GetPeb() {
	#ifdef _M_X64
	return (PPEB)__readgsqword(0x60);
	#else
	return (PPEB)__readfsdword(0x30);
	#endif
}
```

## Practical Guidance
- Use this only with a clear understanding of the target environment and the risk of relying on undocumented internals.
- Validate the returned pointer before dereferencing any fields.
- For analysis work, treat this as a low-level helper rather than a general-purpose production API.

## Related Material
- See [GetModule.md](GetModule.md) for module discovery helpers.
- See [ReadMemory.md](ReadMemory.md) for safe memory access patterns.
