---
title: WriteMemory
skill: snippets
category: 
difficulty: intermediate
tags: [pe, gui]
updated: 2026-07-05
---
# WriteMemory

## Purpose
This snippet shows a straightforward helper for writing into another process with `WriteProcessMemory`.

```cpp
bool WriteRemote(HANDLE hProcess, LPVOID dst, LPCVOID src, SIZE_T size) {
	SIZE_T written = 0;
	return !!WriteProcessMemory(hProcess, dst, src, size, &written);
}
```

## Practical Guidance
- Ensure that the target process is accessible and that the destination region is writable.
- Use this only when you have the necessary privileges and a clear analysis or instrumentation need.
- For in-process modifications, consider using `VirtualProtect` to change protections safely before writing.

## Related Material
- See [ReadMemory.md](ReadMemory.md) for the corresponding read helper.
- See [GetModule.md](GetModule.md) for resolving target module bases.
