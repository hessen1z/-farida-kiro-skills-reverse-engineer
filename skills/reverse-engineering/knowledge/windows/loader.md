---
title: Windows Loader
skill: reverse-engineering
category: knowledge
difficulty: intermediate
tags: [pe, windows, loader, gui, debug, dll]
updated: 2026-07-05
---
# Windows Loader

The Windows loader is responsible for preparing a PE image to execute: mapping
sections, resolving imports, applying relocations, initializing TLS and
running static constructors. Understanding the loader is essential when
recovering runtime behavior or performing in-memory analysis.

Phases of load:
1. Map image headers and sections into virtual memory at `ImageBase`.
2. Apply base relocations if the chosen base conflicts with mapped memory.
3. Resolve imports: build IAT entries by loading dependent modules and
	calling `GetProcAddress` for each imported symbol.
4. Initialize TLS: run callbacks listed in TLS directory.
5. Run `DllMain` (`PROCESS_ATTACH`) for all loaded modules.

Key data structures:
- `PEB->Ldr` (`PEB_LDR_DATA`) — module linked lists (`InLoadOrderModuleList`, ...).
- `IMAGE_IMPORT_DESCRIPTOR` and Import Address Table (IAT) — runtime symbol mapping.
- `IMAGE_BASE_RELOCATION` blocks — used to rebase images.
- TLS Directory — callback list and TLS index.

Common loader-related heuristics in RE:
- If IAT is missing or imports are resolved manually (LoadLibrary/GetProcAddress), suspect packing or manual import resolution.
- TLS callbacks often hide unpacking stubs or early loaders — search `.rdata`/`.tls` for non-empty callbacks.
- Delay-loaded imports leave small stubs that call `__delayLoadHelper` — useful signature to spot delayed resolution.

Examples and related files:
- examples/cpp/pe-parser.cpp
- knowledge/windows/peb.md
- patterns/constructor.md
- recipes/Recover_Classes.md

## Practical Guidance

- When analyzing loaders, instrument the import resolution and relocation steps to see how modules are mapped.
- Identify loader-stage decryption or integrity checks that may hide real code until runtime.

## Tools & Commands

- Use a debugger to set breakpoints on `LdrLoadDll`/`LoadLibrary` and observe parameters and return paths.
- Inspect relocation and import thunks in memory dumps to confirm correct mapping.

## Validation Checklist

- Confirm that loaded modules' sections have expected protections and content after relocation.
- Verify that any lazy binding or delay-load behavior completes as expected during startup.

## Related Material

### Knowledge
- [common-instructions](../assembly/common-instructions.md)
- [compiler-patterns](../assembly/compiler-patterns.md)
- [exceptions](../cpp/exceptions.md)

### Prompts
- [analyze_binary](../../prompts/analyze_binary.md)
- [analyze_crash](../../prompts/analyze_crash.md)
- [analyze_memory](../../prompts/analyze_memory.md)

