---
title: GetModule
skill: snippets
category: 
difficulty: intermediate
tags: [pe, windows, gui]
updated: 2026-07-05
---
# GetModule

## Purpose
This snippet shows a simple way to resolve the base address of a loaded module in the current process.

```cpp
HMODULE GetModuleBase(const wchar_t* name) {
	return GetModuleHandleW(name);
}
```

## Practical Guidance
- Use this helper when you already know the module name and want a quick way to resolve its base address.
- For remote processes, enumerate modules with `EnumProcessModulesEx` or a toolhelp snapshot instead of assuming local-process access.
- Validate the returned handle before using it in subsequent memory operations.

## Related Material
- See [GetPEB.md](GetPEB.md) for a related Windows process-structure helper.
- See [ReadMemory.md](ReadMemory.md) for how to follow up with memory access.
