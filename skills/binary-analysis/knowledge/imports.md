---
title: Imports
skill: binary-analysis
category: knowledge
difficulty: intermediate
tags: [pe, windows, loader, asm, x64, anti-cheat, driver, cryptography, networking, gui, kernel, debug, dll, elf, mach-o]
updated: 2026-07-05
---
# Imports

## Overview

In Windows PE binaries, imports define the external functions and data objects that a module requires from other DLLs. The import system is the loader’s contract for dependency resolution and it is a foundational artifact for reverse engineering, vulnerability analysis, and runtime behavior mapping.

This chapter focuses on PE imports in depth, with practical reverse-engineering guidance, loader behavior, dynamic resolution patterns, and examples relevant to game security and anti-cheat analysis.

## Why imports matter

The import table is often the first place a reverse engineer looks. It tells you:
- which runtime APIs the binary depends on
- whether the binary uses kernel, user-mode, networking, graphics, or filesystem subsystems
- whether the binary uses delay-loaded or dynamic imports
- potential anti-analysis or loader-control APIs

For game and anti-cheat analysts, imports can reveal injection points, communication channels, and suspicious loader behavior.

## PE import architecture

The PE import system consists of several linked structures:
- `IMAGE_IMPORT_DESCRIPTOR`
- Import Lookup Table (ILT)
- Import Address Table (IAT)
- `IMAGE_IMPORT_BY_NAME`
- DLL name strings

All import-related data is normally located in the `.rdata` or `.idata` section.

### IMAGE_IMPORT_DESCRIPTOR

Each imported module is represented by an `IMAGE_IMPORT_DESCRIPTOR`.

Fields:
- `OriginalFirstThunk` — RVA to the ILT
- `TimeDateStamp` — build or bound import timestamp
- `ForwarderChain` — rarely used
- `Name` — RVA to DLL name string
- `FirstThunk` — RVA to the IAT

The descriptor array is terminated by an entry with all zeros.

### Import Lookup Table (ILT)

The ILT is an array of `IMAGE_THUNK_DATA` entries used by the loader to determine which imports to resolve.

Each entry is either:
- an RVA to an `IMAGE_IMPORT_BY_NAME` structure, or
- an ordinal encoded with `IMAGE_ORDINAL_FLAG32` / `IMAGE_ORDINAL_FLAG64`.

### Import Address Table (IAT)

The IAT is the runtime table that receives function pointers after the loader resolves imports.
The binary’s code typically references imported functions through the IAT.

At load time, the loader overwrites IAT entries with actual addresses of imported functions.

### IMAGE_IMPORT_BY_NAME

This structure contains:
- `Hint` — optional index into the export table of the DLL
- `Name` — ASCII function name

### Delayed import descriptors

Delay-loaded imports are represented by a separate delay-load import directory. They are not resolved during initial load. Instead, the runtime resolves them on demand when the importing code executes.

Common compiler-generated helpers for delayed imports are linked into the binary and can be identified by names such as `__delayLoadHelper2`.

## Loader import resolution flow

1. The loader parses the import directory.
2. For each descriptor, the loader loads the referenced DLL.
3. It enumerates the DLL’s export table.
4. For each ILT entry, it resolves the imported function by name or ordinal.
5. It writes the resolved address into the IAT.
6. If any import fails, the process may fail to start or the module may use runtime error handling.

### Successful vs failed import resolution

Successful resolution produces a populated IAT.
Failure commonly results in:
- `ERROR_MOD_NOT_FOUND`
- `ERROR_PROC_NOT_FOUND`
- `STATUS_DLL_NOT_FOUND`

In some cases the binary catches load failures and falls back to manual `LoadLibrary` / `GetProcAddress` resolution.

## Import analysis workflow

### Step 1: validate import directory

Confirm that:
- `IMAGE_DIRECTORY_ENTRY_IMPORT` exists and points to a valid section
- the descriptor array terminates cleanly
- DLL names are readable ASCII strings
- `OriginalFirstThunk` and `FirstThunk` RVAs map to valid data

### Step 2: enumerate imported modules

Record every imported module and imported symbol. Common system DLLs include:
- `kernel32.dll`
- `user32.dll`
- `ntdll.dll`
- `advapi32.dll`
- `ws2_32.dll`
- `d3d11.dll`

Custom DLL imports in games may reveal plugin frameworks, injected hooks, or anti-cheat helper libraries.

### Step 3: categorize imports

Classify imports by subsystem:
- OS services (file, process, memory)
- graphics and rendering
- networking
- input
- cryptography
- debugging and instrumentation
- anti-cheat / tamper detection

### Step 4: identify dynamic resolution patterns

Look for import-related code that resolves symbols dynamically with:
- `LoadLibraryA` / `LoadLibraryW`
- `GetProcAddress`
- `GetModuleHandleA` / `GetModuleHandleW`
- `LdrLoadDll`
- `LdrGetProcedureAddress`

These patterns often indicate:
- manual module loading
- late binding
- obfuscation or packing
- import table manipulation

### Step 5: inspect delayed imports

Delayed imports are a common tactic in game binaries and protection layers. They allow the module to start without resolving every dependency.

Check for:
- delay import descriptor directory
- bound import tables
- helper thunks generated by the compiler

## Practical import recovery

### C++ example: parse the import table

```cpp
#include <windows.h>
#include <string>
#include <vector>

struct ImportEntry {
    std::string module;
    std::string function;
    uint16_t ordinal;
    bool byOrdinal;
};

std::vector<ImportEntry> parse_imports(uint8_t* image) {
    std::vector<ImportEntry> imports;
    auto dos = reinterpret_cast<PIMAGE_DOS_HEADER>(image);
    auto nt = reinterpret_cast<PIMAGE_NT_HEADERS>(image + dos->e_lfanew);
    auto importDir = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    if (!importDir.VirtualAddress) return imports;

    auto descriptors = reinterpret_cast<PIMAGE_IMPORT_DESCRIPTOR>(image + importDir.VirtualAddress);
    for (; descriptors->Name; ++descriptors) {
        auto moduleName = reinterpret_cast<char*>(image + descriptors->Name);
        auto thunk = reinterpret_cast<PIMAGE_THUNK_DATA>(image + descriptors->OriginalFirstThunk);
        if (!descriptors->OriginalFirstThunk)
            thunk = reinterpret_cast<PIMAGE_THUNK_DATA>(image + descriptors->FirstThunk);

        for (; thunk->u1.AddressOfData; ++thunk) {
            if (thunk->u1.Ordinal & IMAGE_ORDINAL_FLAG64) {
                imports.push_back({moduleName, "", static_cast<uint16_t>(IMAGE_ORDINAL64(thunk->u1.Ordinal)), true});
            } else {
                auto importByName = reinterpret_cast<PIMAGE_IMPORT_BY_NAME>(image + thunk->u1.AddressOfData);
                imports.push_back({moduleName, reinterpret_cast<char*>(importByName->Name), 0, false});
            }
        }
    }
    return imports;
}
```

### Assembly: import thunk resolution

In x64 binaries, imported function calls often look like:

```asm
mov rax, qword ptr [rip + __imp__CreateFileW]
call rax
```

This indicates a direct IAT call rather than a hard-coded function address.

In x86 binaries, the common pattern is:

```asm
call dword ptr [__imp__CreateFileA]
```

To identify imported calls, search for references to `__imp__` symbols or memory references inside the `.idata` region.

## Delay-load imports and manual binding

Delay-load imports are not resolved during initial load. Instead, they are resolved when the code first references the imported symbol.

This is represented by the delay-load import directory and helper thunks.

### Why delay-load is used

- reduce startup cost
- avoid requiring certain DLLs unless needed
- implement optional features
- complicate static analysis and packers

### Detection

Look for code that calls compiler-generated helpers and then jumps through a resolver thunk.

### Example delayed import pattern

- `__delayLoadHelper2` or `__delayLoadHelper2@8`
- thunks that call `GetModuleHandle` / `LoadLibrary`
- IAT entries that are initially null or contain stub code

## Import table obfuscation and tampering

Attackers and protectors may modify the import table at runtime.
Common techniques:
- IAT hooks
- inline function patching of imported calls
- import table erasure with manual resolution fallback
- code that builds a fake import directory for analysis evasion

### Detecting tampered imports

Validate imported addresses against the expected module base:
- resolve each IAT entry at runtime
- verify the address falls within the imported DLL’s memory range
- compare function names to actual export names

If imported addresses point to non-module memory, the IAT may be hooked.

## Import-related PE anomalies

### Missing import directory

A binary may omit the import directory entirely. In those cases look for dynamic call patterns using `LoadLibrary` / `GetProcAddress`.

### Stubbed imports

A binary may declare imports but resolve them lazily or through a custom loader. Inspect stub code around the import table.

### Relocated import tables

Because the import table is itself part of the image, its addresses are subject to relocation. When manually mapping a PE, apply relocation fixes before reading the IAT.

### Bound imports

Older binaries may use bound imports. The `TimeDateStamp` field in the descriptor points to the timestamp of the resolved DLL. Bound imports can speed startup but may also confuse static analysis if the DLL version changes.

## Import analysis for game security and anti-cheat

### What imports reveal in games

Game clients often import:
- rendering and graphics APIs (`d3d11.dll`, `dxgi.dll`)
- input APIs (`user32.dll`, `XInput1_4.dll`)
- networking (`ws2_32.dll`, `Wininet.dll`)
- audio (`xaudio2_9.dll`)
- system time and performance counters

Custom game engine modules may import plugin loaders, scripting systems, or engine frameworks.

### What imports reveal in anti-cheat

Anti-cheat modules often import:
- system integrity APIs (`NtQuerySystemInformation`, `CreateRemoteThread`)
- process/memory APIs (`OpenProcess`, `ReadProcessMemory`)
- driver-loading APIs if a user-mode companion is present
- network and telemetry APIs for cloud reporting

Early-loaded anti-cheat components may use TLS and delayed imports to obfuscate their initialization.

## Cross-platform context (brief)

While this skill focuses on PE, import analysis shares common themes with ELF and Mach-O.
- ELF: `.dynsym`, `.dynstr`, `.rel.plt`, `.got.plt`
- Mach-O: `LC_LOAD_DYLIB`, `LC_DYLD_INFO`, symbol tables

The key concept is the same: imports define external dependencies and are essential for understanding runtime behavior.

## Common mistakes

- treating imported symbols as actual runtime usage without execution evidence
- ignoring delayed imports and dynamic resolution paths
- assuming the presence of a PE import directory means the binary is not protected
- relying on section names instead of actual directory and thunk contents
- failing to verify IAT entries against loaded module ranges

## Practical tips

- always parse both the ILT and IAT
- search for `LoadLibrary` / `GetProcAddress` patterns when imports look absent or sparse
- inspect `TimeDateStamp` for bound imports and suspicious versioning
- use dynamic debugging to confirm whether imports are resolved before first use
- document import categories and use them to prioritize analyst focus

## Practical Guidance

- Prefer dynamic validation: verify imports are actually invoked during execution traces or instrumented runs.
- When static-only analysis is required, resolve ILT/IAT and delay-load descriptors first and verify pointer ranges.

## Tools & Commands

- `pefile` (Python), `CFF Explorer`, `rizin`, `radare2`, and `r2pipe` for scripted import enumeration.
- Use debugger breakpoints on `LoadLibrary`/`GetProcAddress` and instrumentation frameworks (`frida`, `PIN`) for runtime checks.

## Validation Checklist

- Confirm each IAT entry points into the expected module's export address range at runtime.
- Verify delayed imports are resolved when helper thunks execute and that bound imports reflect the expected DLL versions.

## References

- Microsoft PE/COFF Specification — Import Directory
- Windows Internals — Dynamic Linking and Load-Time Resolution
- Microsoft Visual C++ Delay Load documentation
- Anti-analysis research on import table tampering

## Related Material

### Knowledge
- [decompilers](decompilers.md)
- [demangling](demangling.md)
- [disassemblers](disassemblers.md)

### Patterns
- [encrypted-string](../patterns/encrypted-string.md)
- [export-table](../patterns/export-table.md)
- [import-table](../patterns/import-table.md)

### Recipes
- [analyze-binary](../recipes/analyze-binary.md)
- [recover-exports](../recipes/recover-exports.md)
- [recover-imports](../recipes/recover-imports.md)

### Playbooks
- [analyze-elf](../playbooks/analyze-elf.md)
- [analyze-packed-binary](../playbooks/analyze-packed-binary.md)
- [analyze-pe](../playbooks/analyze-pe.md)

### References
- [elf](../references/elf.md)
- [intel](../references/intel.md)
- [microsoft](../references/microsoft.md)

### Rules
- [rule](../rules/rule.md)

### Prompts
- [analyze-binary](../prompts/analyze-binary.md)

### Checklists
- [checklist](../checklists/checklist.md)

