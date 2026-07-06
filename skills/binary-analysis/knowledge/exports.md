---
title: Exports
skill: binary-analysis
category: knowledge
difficulty: intermediate
tags: [pe, windows, loader, asm, anti-cheat, driver, malware, pdb, gui, kernel, dll, elf]
updated: 2026-07-05
---
# Exports

## Overview

In PE binaries, exports define the functions and data objects a module exposes to other modules. The export table is the contract a DLL or executable offers to callers, and it is one of the most valuable artifacts for reverse engineering, plug-in analysis, driver inspection, and security architecture mapping.

This document covers export table internals, loader resolution, analysis workflows, and practical tips for understanding PE exports in game engines, anti-cheat systems, and runtime security modules.

## Why exports matter

Exports reveal the public surface of a binary. They are especially useful for:
- identifying plugin or callback interfaces
- understanding driver and kernel module entry points
- reconstructing API layers in stripped binaries
- mapping game engine and engine plugin interactions
- discovering anti-cheat monitoring or integrity-check endpoints

In defensive engineering, exports also indicate an attack surface and the functions an external component may call.

## PE export table architecture

The export table resides in the `IMAGE_DATA_DIRECTORY` at index `IMAGE_DIRECTORY_ENTRY_EXPORT`. It is composed of:
- `IMAGE_EXPORT_DIRECTORY`
- Export Address Table (`AddressOfFunctions`)
- Name Pointer Table (`AddressOfNames`)
- Ordinal Table (`AddressOfNameOrdinals`)

Each exported entry may be:
- a named export
- an ordinal-only export
- a forwarded export

### IMAGE_EXPORT_DIRECTORY

Fields to inspect:
- `Characteristics`
- `TimeDateStamp`
- `MajorVersion` / `MinorVersion`
- `Name` — RVA to DLL name
- `Base` — starting ordinal
- `NumberOfFunctions`
- `NumberOfNames`
- `AddressOfFunctions`
- `AddressOfNames`
- `AddressOfNameOrdinals`

### Export Address Table

This array contains RVAs for each exported function or data item. Its length is `NumberOfFunctions`.

An RAV may point to:
- code in `.text`
- data in `.data` or `.rdata`
- a forwarded export string

### Name Pointer Table

This table contains RVAs to ASCII export names. Only named exports appear here.

### Ordinal Table

This table contains 16-bit ordinals corresponding to name table entries. Each value is an index into the export address table.

The actual ordinal of a named export is `Base + OrdinalTable[i]`.

## Export resolution behavior

When a caller imports a symbol by name or ordinal, the loader locates the target DLL’s export table and resolves the symbol address.

Important loader behaviors:
- name lookups are case-sensitive
- ordinal lookups bypass names and are faster but less stable
- forwarded exports redirect resolution to another module

### Forwarded exports

Forwarded exports are represented by an RVA to an ASCII string rather than code.

Example forwarded export string:

```
kernel32.Sleep
```

Forwarded exports reveal dependency chains and can indicate redirection through syscall wrappers or compatibility layers.

### Ordinal-only exports

When an export has no name, it is only callable by ordinal. This is common in:
- compact modules
- obfuscated binaries
- game engine interfaces designed for fast lookup

Ordinal exports are harder to reverse engineer because they lack human-readable names.

## Export analysis workflow

### Step 1: validate the export directory

Check that:
- the export directory exists and maps to a valid section
- `NumberOfFunctions` and `NumberOfNames` are consistent
- `AddressOfFunctions`, `AddressOfNames`, and `AddressOfNameOrdinals` do not point outside the file
- the DLL name string is valid

### Step 2: enumerate exports

Extract:
- all named exports
- all ordinal-only exports
- forwarded exports

Record:
- export name
- export ordinal
- export RVA
- forwarding target if present

### Step 3: categorize exported interfaces

Group exports by purpose:
- plugin registration functions
- callback installation functions
- initialization and shutdown entry points
- data accessors
- integrity checks

In game engines and anti-cheat modules, exports may also include telemetry endpoints and diagnostic hooks.

### Step 4: resolve forwarded exports

If an export is forwarded, follow the string to the target module and target export. This can reveal intermediate compatibility libraries and redirection chains.

### Step 5: find code or data targets

Convert each export RVA to a file offset. Determine whether the target is:
- executable code
- data/static object
- a thunk or stub
- a forwarded string

Use section headers and the runtime image map for accurate resolution.

## C++ analysis example

```cpp
#include <windows.h>
#include <vector>
#include <string>

struct ExportEntry {
    std::string name;
    uint32_t ordinal;
    uint32_t rva;
    bool forwarded;
    std::string forwardName;
};

std::vector<ExportEntry> parse_exports(uint8_t* image) {
    std::vector<ExportEntry> exports;
    auto dos = reinterpret_cast<PIMAGE_DOS_HEADER>(image);
    auto nt = reinterpret_cast<PIMAGE_NT_HEADERS>(image + dos->e_lfanew);
    auto exportDir = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
    if (!exportDir.VirtualAddress) return exports;

    auto exportsHeader = reinterpret_cast<PIMAGE_EXPORT_DIRECTORY>(image + exportDir.VirtualAddress);
    auto names = reinterpret_cast<uint32_t*>(image + exportsHeader->AddressOfNames);
    auto ordinals = reinterpret_cast<uint16_t*>(image + exportsHeader->AddressOfNameOrdinals);
    auto functions = reinterpret_cast<uint32_t*>(image + exportsHeader->AddressOfFunctions);

    for (DWORD i = 0; i < exportsHeader->NumberOfNames; ++i) {
        char* name = reinterpret_cast<char*>(image + names[i]);
        uint16_t ordinalIndex = ordinals[i];
        uint32_t rva = functions[ordinalIndex];
        uint32_t ordinal = exportsHeader->Base + ordinalIndex;
        bool forwarded = false;
        std::string forwardName;

        uint8_t* target = image + rva;
        if (target && *reinterpret_cast<char*>(target) && memchr(target, '.', 1)) {
            forwarded = true;
            forwardName = reinterpret_cast<char*>(target);
        }

        exports.push_back({name, ordinal, rva, forwarded, forwardName});
    }

    return exports;
}
```

### Assembly example: exported thunk

A common exported thunk in a DLL looks like:

```asm
jmp dword ptr [rip + __imp__SomeFunction]
```

This indicates the export is a pass-through to another imported function or runtime helper.

### Assembly example: ordinal-only export

```asm
jmp qword ptr [rip + 0x1234]
```

Without a name in the export table, the only reliable identifier is the ordinal.

## Export recovery for reverse engineering

### Recovering API surfaces

Exports are the most reliable source for identifying a module’s public API surface. Use them to:
- name functions in disassembly
- understand plugin loading interfaces
- identify event dispatchers and callback setters

### Inferring purpose from export names

Export names often include domain-specific hints:
- `CreateDevice`, `Initialize`, `Connect`
- `RegisterCallback`, `UnregisterCallback`
- `LoadMap`, `SpawnActor`
- `ReportIntegrity`, `ValidateMemory`

For game modules, exports are often entry points to engine subsystems.
For anti-cheat modules, exported functions may be diagnostic or registration hooks.

### Dealing with stripped exports

If a module exports only ordinals, analyze the implementation around the export target, discover nearby RTTI or vtable references, and look for patterns used by known engine or cheating frameworks.

## Forwarded export analysis

Forwarded exports can form chains. To analyze them:
1. parse the export string
2. determine the target module name and symbol
3. locate the target module in the loaded process image
4. resolve the target export recursively

Forwarded exports often appear in compatibility layers or thunking DLLs.

## Export anomalies and protection patterns

### Export table obfuscation

Protectors may modify export tables to hide functionality.
Signs include:
- inconsistent `NumberOfNames`
- fake export names
- exports pointing to garbage or invalid addresses
- `AddressOfFunctions` values outside valid sections

### Export table removal

Some modules remove or encrypt the export directory to frustrate static analysis. In those cases, use runtime inspection and export enumeration through APIs such as `EnumProcessModules` and `GetProcAddress`.

### Export stubs and trampolines

Exports may resolve through stubs or trampolines, especially in loader or compatibility DLLs. Inspect the code at each exported RVA to determine whether it is a real implementation or a redirect.

## Game security and anti-cheat export patterns

### What game binaries export

Common exported functions in game modules include:
- engine initialization and shutdown hooks
- plugin registration functions
- network and replication helpers
- cheat detection callbacks

### What anti-cheat modules export

Anti-cheat DLLs may export:
- registration and heartbeat functions
- integrity-check request handlers
- driver communication endpoints
- telemetry submission routines

Exports in anti-cheat modules are often minimal, focusing on controlled interaction with the game or launcher.

## Cross-references

- `../patterns/export-table.md`
- `../recipes/recover-exports.md`
- `../playbooks/analyze-packed-binary.md`
- `../knowledge/imports.md`
- `../knowledge/pdb.md`

## Common mistakes

- assuming export names are exact source names
- ignoring forwarded exports
- failing to validate export RVAs before dereferencing
- miscalculating ordinals when `Base` is non-zero
- overlooking ordinal-only exports in obfuscated binaries

## Practical tips

- use export tables to seed disassembly naming
- verify forwarded exports before assuming implementation location
- track ordinal-only exports by implementation signature and neighboring data
- combine export analysis with import and relocation analysis for a complete API picture

## Practical Guidance

- Enumerate exports programmatically and validate forwarded exports by resolving their target modules.
- Use exports to seed symbol names in disassembly and prioritize functions for dynamic tracing.

## Tools & Commands

- `dumpbin /exports`, `objdump`, `rizin`, and `radare2` to list exports and follow forwarded entries.
- Use a runtime loader (e.g., `LoadLibrary` + `GetProcAddress`) in a controlled process to validate export behavior.

## Validation Checklist

- Confirm export RVAs map to valid code or data sections and that forwarded strings parse to valid module/symbol names.
- Verify ordinal-only exports by matching function behavior across versions and ensuring ordinal bases are applied correctly.

## References

- Microsoft PE/COFF Specification — Export Directory
- Microsoft Windows Internals — DLL loading and export resolution
- Malware analysis literature on export table protection
- Reverse engineering resources on ordinal-only APIs

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

