# Portable Executable (PE)

## Overview

The Portable Executable (PE) format is the canonical Windows binary container for executables, DLLs, drivers, and system libraries. It defines the on-disk layout, loader metadata, runtime section mapping, import/export resolution, relocation data, thread-local storage, resources, and debug information.

This reference is written for senior C++ engineers, reverse engineers, game security analysts, and anti-cheat practitioners. It combines structural analysis, loader behavior, and practical reverse engineering workflows.

## Why PE matters

PE is the bridge between raw bytes on disk and process memory at runtime. Every Windows loader path, exception handler, dynamic symbol resolution, and runtime initialization step depends on PE metadata.

Understanding PE is essential for:
- recovering symbol information from stripped executables
- diagnosing loader crashes and DLL initialization failures
- unpacking packers and protected loaders
- analyzing C++ RTTI, vtables, and compiler-generated artifacts
- mapping game engine modules and anti-cheat components

## File layout and sections

A PE file consists of:
1. DOS header and stub
2. NT headers (`Signature`, `FileHeader`, `OptionalHeader`)
3. Section table (`IMAGE_SECTION_HEADER` entries)
4. Section contents
5. Data directories and optional metadata

### DOS header and stub

The file starts with an `IMAGE_DOS_HEADER`.

Important fields:
- `e_magic` = `0x5A4D` (`MZ`)
- `e_lfanew` = offset to `IMAGE_NT_HEADERS`

The DOS stub is legacy compatibility code. Modern analysis only relies on `e_lfanew` and the `MZ` signature for format validation.

### NT headers

At `e_lfanew`, the file contains `IMAGE_NT_HEADERS`.

Structure order:
- `Signature` = `0x00004550` (`PE\0\0`)
- `IMAGE_FILE_HEADER`
- `IMAGE_OPTIONAL_HEADER`

`IMAGE_FILE_HEADER` contains target architecture, section count, time stamps, and characteristics.
`IMAGE_OPTIONAL_HEADER` defines image base, entry point, alignment settings, subsystem, and data directories.

#### Key file header fields
- `Machine` identifies `x86`, `x64`, or `ARM64`.
- `NumberOfSections` indicates how many section headers follow.
- `Characteristics` flags the binary as executable, DLL, system file, or position-independent.

#### Key optional header fields
- `Magic` distinguishes PE32 and PE32+.
- `AddressOfEntryPoint` is the RVA of the startup function.
- `ImageBase` is the preferred load address.
- `SectionAlignment` and `FileAlignment` control memory and disk layout.
- `SizeOfImage` is the memory size reserved for the image.
- `SizeOfHeaders` is the header region size on disk.
- `DataDirectory` points to runtime metadata tables.

### Section headers

`IMAGE_SECTION_HEADER` entries map section names to file and memory regions.

Typical section fields:
- `Name`
- `VirtualSize`
- `VirtualAddress`
- `SizeOfRawData`
- `PointerToRawData`
- `Characteristics`

Common section names:
- `.text` — code
- `.rdata` — read-only data and import/export metadata
- `.data` — initialized writable data
- `.rsrc` — resources
- `.reloc` — base relocations
- `.pdata` and `.xdata` — unwind metadata for x64
- `.tls` — thread-local storage data

### Image layout diagram

```
FILE LAYOUT
+------------------------+
| DOS HEADER + STUB      |
+------------------------+
| NT HEADERS             |
+------------------------+
| SECTION HEADERS        |
+------------------------+
| .text raw data         |
+------------------------+
| .rdata raw data        |
+------------------------+
| .data raw data         |
+------------------------+
| .rsrc raw data         |
+------------------------+
| .reloc raw data        |
+------------------------+

RUNTIME IMAGE
+------------------------+
| ImageBase              |
+------------------------+
| .text mapped           |
+------------------------+
| .rdata mapped          |
+------------------------+
| .data mapped           |
+------------------------+
| .tls mapped            |
+------------------------+
| .rsrc mapped           |
+------------------------+
| .reloc mapped          |
+------------------------+
```

## PE memory mapping and loader behavior

The Windows loader follows these steps:
1. Validate the DOS header and NT signature.
2. Reserve memory for the image using `SizeOfImage`.
3. Map each section according to `VirtualAddress` and `SectionAlignment`.
4. Copy raw data from disk to mapped memory.
5. Zero-initialize slack space when `VirtualSize` exceeds `SizeOfRawData`.
6. Apply base relocations if the image is not loaded at its preferred base.
7. Resolve imports and populate the Import Address Table (IAT).
8. Call TLS callbacks.
9. Execute global constructors and `DllMain` for DLLs.
10. Jump to `AddressOfEntryPoint`.

### File alignment vs section alignment

- `FileAlignment` is the on-disk granularity.
- `SectionAlignment` is the in-memory granularity.

Do not assume sections are contiguous on disk or in memory. Use the section header mapping logic when converting between RVA and file offset.

### Image base and ASLR

`ImageBase` is the recommended load address. If that address is unavailable, relocations patch base-relative references.

`IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE` enables ASLR. A binary without a relocation table cannot be relocated safely.

## Data directories and runtime metadata

`IMAGE_OPTIONAL_HEADER.DataDirectory` contains entries for runtime metadata.
Each entry has an RVA and size.

Important directories:
- `IMAGE_DIRECTORY_ENTRY_EXPORT`
- `IMAGE_DIRECTORY_ENTRY_IMPORT`
- `IMAGE_DIRECTORY_ENTRY_RESOURCE`
- `IMAGE_DIRECTORY_ENTRY_EXCEPTION`
- `IMAGE_DIRECTORY_ENTRY_SECURITY`
- `IMAGE_DIRECTORY_ENTRY_BASERELOC`
- `IMAGE_DIRECTORY_ENTRY_DEBUG`
- `IMAGE_DIRECTORY_ENTRY_TLS`
- `IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG`

When analyzing a PE, validate each data directory before dereferencing it. Malformed or packed binaries may contain invalid directory entries.

## Import table

The import table resolves external dependencies.
It is composed of `IMAGE_IMPORT_DESCRIPTOR` entries, one per imported module.

Descriptor fields:
- `OriginalFirstThunk` — pointer to import lookup data
- `TimeDateStamp`
- `ForwarderChain`
- `Name` — DLL name
- `FirstThunk` — pointer to IAT

### ILT vs IAT

- The Import Lookup Table (ILT) lists imports by name or ordinal.
- The Import Address Table (IAT) receives resolved addresses.

The loader uses the ILT to determine which functions to import, then writes their addresses into the IAT.

### Import by name vs ordinal

If the high bit is set in a thunk entry, the import uses an ordinal instead of a name.

Example:
- `IMAGE_ORDINAL_FLAG64` for x64
- `IMAGE_ORDINAL_FLAG32` for x86

Ordinals are common in games and drivers to reduce import metadata size.

### Reverse engineering value of imports

Imports reveal runtime behavior and attack surface.
They tell you which APIs a binary uses, such as:
- file I/O (`CreateFileW`, `ReadFile`)
- network (`InternetReadFile`, `send`)
- process control (`CreateProcess`, `OpenProcess`)
- anti-debugging (`IsDebuggerPresent`, `NtQueryInformationProcess`)

In game hacking and anti-cheat analysis, imports also reveal loader techniques, dynamic module resolution, and syscall wrappers.

### C++ import parsing example

```cpp
#include <windows.h>
#include <vector>
#include <string>

struct ImportEntry {
    std::string module;
    std::string name;
    uint16_t ordinal;
    bool byOrdinal;
};

std::vector<ImportEntry> parse_imports(uint8_t* base) {
    std::vector<ImportEntry> result;
    auto dos = reinterpret_cast<PIMAGE_DOS_HEADER>(base);
    auto nt = reinterpret_cast<PIMAGE_NT_HEADERS>(base + dos->e_lfanew);
    auto importDir = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    if (!importDir.VirtualAddress) return result;

    auto imports = reinterpret_cast<PIMAGE_IMPORT_DESCRIPTOR>(base + importDir.VirtualAddress);
    for (; imports->Name; ++imports) {
        auto moduleName = reinterpret_cast<char*>(base + imports->Name);
        auto thunk = reinterpret_cast<PIMAGE_THUNK_DATA>(base + imports->OriginalFirstThunk);
        if (!imports->OriginalFirstThunk) thunk = reinterpret_cast<PIMAGE_THUNK_DATA>(base + imports->FirstThunk);

        for (; thunk->u1.AddressOfData; ++thunk) {
            if (thunk->u1.Ordinal & IMAGE_ORDINAL_FLAG64) {
                result.push_back({moduleName, "", static_cast<uint16_t>(IMAGE_ORDINAL64(thunk->u1.Ordinal)), true});
            } else {
                auto importByName = reinterpret_cast<PIMAGE_IMPORT_BY_NAME>(base + thunk->u1.AddressOfData);
                result.push_back({moduleName, reinterpret_cast<char*>(importByName->Name), 0, false});
            }
        }
    }
    return result;
}
```

## Export table

Exports define the functions and data a module makes available.
The export directory contains:
- `AddressOfFunctions`
- `AddressOfNames`
- `AddressOfNameOrdinals`
- `Name`
- `NumberOfFunctions`
- `NumberOfNames`

### Export types
- named exports
- ordinal-only exports
- forwarded exports

Forwarded exports redirect callers to another module. They appear as strings like `OTHERDLL.Func` rather than actual function code.

### Why exports matter

For reverse engineering, exports provide visible entry points and API surface area. In anti-cheat and game security, exported functions may include:
- integrity checks
- communication interfaces
- driver entry routines
- plugin registration callbacks

### Export parsing example

```cpp
void parse_exports(uint8_t* base) {
    auto dos = reinterpret_cast<PIMAGE_DOS_HEADER>(base);
    auto nt = reinterpret_cast<PIMAGE_NT_HEADERS>(base + dos->e_lfanew);
    auto exportDir = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
    if (!exportDir.VirtualAddress) return;

    auto exports = reinterpret_cast<PIMAGE_EXPORT_DIRECTORY>(base + exportDir.VirtualAddress);
    auto names = reinterpret_cast<uint32_t*>(base + exports->AddressOfNames);
    auto ordinals = reinterpret_cast<uint16_t*>(base + exports->AddressOfNameOrdinals);
    auto functions = reinterpret_cast<uint32_t*>(base + exports->AddressOfFunctions);

    for (DWORD i = 0; i < exports->NumberOfNames; ++i) {
        char* name = reinterpret_cast<char*>(base + names[i]);
        uint16_t ordinal = ordinals[i] + exports->Base;
        uint32_t rva = functions[ordinals[i]];
        // record export name and RVA
    }
}
```

## Base relocations

Relocations patch absolute addresses when the loader chooses a different base.
Relocation entries are stored in the `.reloc` section.

Each block is an `IMAGE_BASE_RELOCATION` followed by 16-bit relocation entries.

Entry format:
- high 4 bits: type
- low 12 bits: offset within the page

Common types:
- `IMAGE_REL_BASED_ABSOLUTE` — no relocation
- `IMAGE_REL_BASED_HIGHLOW` — 32-bit patch
- `IMAGE_REL_BASED_DIR64` — 64-bit patch

### Relocation usage

Relocations are required for:
- ASLR compatibility
- manual mapping and injection
- runtime pointer patching

A missing relocation table means the image is not relocatable and may require special loader logic.

### Apply relocations example

```cpp
void apply_relocations(uint8_t* base, intptr_t delta) {
    auto dos = reinterpret_cast<PIMAGE_DOS_HEADER>(base);
    auto nt = reinterpret_cast<PIMAGE_NT_HEADERS>(base + dos->e_lfanew);
    auto relocDir = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC];
    if (!relocDir.VirtualAddress) return;

    auto reloc = reinterpret_cast<PIMAGE_BASE_RELOCATION>(base + relocDir.VirtualAddress);
    while (reloc->VirtualAddress) {
        uint32_t count = (reloc->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(uint16_t);
        auto entries = reinterpret_cast<uint16_t*>(reloc + 1);
        for (uint32_t i = 0; i < count; ++i) {
            uint16_t type = entries[i] >> 12;
            uint16_t offset = entries[i] & 0x0FFF;
            auto patchAddr = reinterpret_cast<uint8_t*>(base + reloc->VirtualAddress + offset);
            if (type == IMAGE_REL_BASED_DIR64) {
                *reinterpret_cast<uint64_t*>(patchAddr) += delta;
            } else if (type == IMAGE_REL_BASED_HIGHLOW) {
                *reinterpret_cast<uint32_t*>(patchAddr) += static_cast<uint32_t>(delta);
            }
        }
        reloc = reinterpret_cast<PIMAGE_BASE_RELOCATION*>(reinterpret_cast<uint8_t*>(reloc) + reloc->SizeOfBlock);
    }
}
```

## Thread Local Storage (TLS)

TLS data supports per-thread variables and callbacks.
Important fields:
- `StartAddressOfRawData`
- `EndAddressOfRawData`
- `AddressOfIndex`
- `AddressOfCallBacks`
- `SizeOfZeroFill`

TLS callbacks run before the main entry point. They are frequently used by packers and anti-cheat code for early validation.

### TLS analysis

To analyze TLS:
1. Parse the TLS directory.
2. Enumerate callback pointers.
3. Inspect callback code for anti-debug or protection logic.
4. Correlate TLS data with thread creation and initialization behavior.

### Assembly pattern

```asm
mov rax, qword ptr [image_base + tlsDirectory.AddressOfCallbacks]
cmp qword ptr [rax], 0
je tls_done
call qword ptr [rax]
add rax, 8
jmp short tls_loop
```

## Resources

Resources are stored in a hierarchical directory tree.
Resource levels:
1. type
2. name or ID
3. language

Common resource types:
- `RT_ICON`
- `RT_STRING`
- `RT_MANIFEST`
- `RT_VERSION`

### Resource value

Resources can contain:
- build and version strings
- vendor metadata
- manifest policies
- embedded compressed data

For game analysis, resources may hold licensing information, DRM payloads, or anti-cheat flags.

## Debug information

The debug directory points to symbol and build metadata.
Common debug formats:
- CodeView (`RSDS`)
- COFF debug
- embedded PDB information

`IMAGE_DEBUG_DIRECTORY`
fields:
- `Type`
- `SizeOfData`
- `AddressOfRawData`
- `PointerToRawData`

The `RSDS` record includes:
- signature
- GUID
- age
- PDB file path

### PDB analysis

PDB metadata can reveal build information and symbol server paths.
Use it to:
- recover function and data names
- correlate binaries with source builds
- verify compiler versions

Do not assume the PDB file is available. The debug directory may contain only a reference.

## C++ and compiler artifacts

PEs often include C++ runtime artifacts:
- import thunks
- TLS callbacks
- exception handling frames
- RTTI structures
- security cookie initialization

For Visual C++ binaries, common sections are:
- `.idata`
- `.rdata`
- `.tls`
- `.pdata`
- `.xdata`

RTTI data is often near vtables and includes:
- `TypeDescriptor`
- `ClassHierarchyDescriptor`
- `CompleteObjectLocator`

These structures are crucial for class recovery and virtual function analysis.

### C++ thunk example

```asm
jmp qword ptr [__imp__CreateFileW@20]
```

This indicates a direct imported API call through the IAT rather than a hardcoded function pointer.

## Reverse engineering workflow

### Step 1: validate the PE
- verify `MZ` at offset 0
- verify `PE\0\0` at `e_lfanew`
- confirm `NumberOfSections` is reasonable
- confirm `SizeOfHeaders` is within file bounds

### Step 2: map RVAs to file offsets
Use section headers to convert RVAs:

```cpp
uint8_t* rva_to_ptr(uint8_t* image, uint32_t rva) {
    auto dos = reinterpret_cast<PIMAGE_DOS_HEADER>(image);
    auto nt = reinterpret_cast<PIMAGE_NT_HEADERS>(image + dos->e_lfanew);
    auto sections = IMAGE_FIRST_SECTION(nt);
    for (WORD i = 0; i < nt->FileHeader.NumberOfSections; ++i) {
        auto& section = sections[i];
        uint32_t start = section.VirtualAddress;
        uint32_t end = start + std::max(section.Misc.VirtualSize, section.SizeOfRawData);
        if (rva >= start && rva < end) {
            return image + section.PointerToRawData + (rva - start);
        }
    }
    return nullptr;
}
```

### Step 3: inspect data directories
- import directory
- export directory
- relocation directory
- TLS directory
- debug directory
- resource directory

### Step 4: identify suspicious patterns
Look for:
- missing or stubbed import tables
- unusual section names like `.vmp0`, `.themida`, `.upx`
- large `.text` sections with few imports
- corrupted header values

### Step 5: validate runtime behavior
Use a debugger to confirm:
- loader entry point flow
- TLS callback execution
- import resolution
- relocation patching
- exception handler setup

## Common mistakes and gotchas

### RVA vs file offset
RVA is relative to `ImageBase`. File offset is relative to the file start. Always use the section table to translate.

### VirtualSize vs SizeOfRawData
The runtime section size is `VirtualSize`. The on-disk size is `SizeOfRawData`. Use the larger boundary when validating memory ranges.

### False trust in section names
Section names can be forged. Use header metadata and characteristics instead.

### Missing relocations
A binary can still load at a preferred base on one machine but fail elsewhere without relocation support.

### TLS callbacks
TLS executes before the main entry point. Missing them means missing early-stage initialization or anti-analysis checks.

### Delayed imports
Delayed-loading imports may be absent from the primary import table but are still semantically important.

## Game and anti-cheat considerations

### Game client PE patterns
Game clients often use custom loaders, dynamic imports, and packed modules. They may also embed engine metadata in resources or use obfuscated export tables.

### Driver and kernel PEs
Drivers use the PE format with kernel-specific constraints. Driver PEs can omit imports and rely on kernel loader fixups.

### Anti-cheat patterns
Anti-cheat modules may leverage TLS callbacks, custom section names, encrypted resources, and runtime decryption of imports.

Watch for:
- early `IsDebuggerPresent` or `CheckRemoteDebuggerPresent` calls
- anti-tamper logic in TLS callbacks
- imports resolved via `GetProcAddress`
- exports that expose integrity-check functions

## Cross-links

- `../patterns/import-table.md`
- `../patterns/export-table.md`
- `../patterns/packer.md`
- `../recipes/recover-imports.md`
- `../recipes/recover-exports.md`
- `../playbooks/analyze-packed-binary.md`

## References

- Microsoft "Portable Executable and Common Object File Format Specification"
- Microsoft Windows Internals
- Microsoft PE/COFF Specification
- Malware analysis books on PE packers and loaders
- Microsoft Visual C++ ABI documentation

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

