---
title: Relocations
skill: binary-analysis
category: knowledge
difficulty: intermediate
tags: [pe, windows, loader, asm, x64, anti-cheat, driver, malware, gui, kernel, debug, dll, elf]
updated: 2026-07-05
---
# Relocations

## Overview

Relocations are the runtime patching mechanism that allows a PE image to execute correctly when it is not loaded at its preferred base address. They are essential for ASLR support, manual mapping, injection, and reliability across different processes.

This chapter explains PE base relocations in detail, describes loader behavior, and presents practical techniques for reverse engineering, unpacking, and manual mapping.

## Why relocations matter

A PE binary is built assuming a preferred `ImageBase`. When the operating system cannot map the image at that address, the loader applies relocation fixups.

Relocations matter because:
- they enable ASLR and address-space layout flexibility
- they allow multiple copies of the same DLL to coexist
- they are critical for manual map loaders and custom injection
- they provide evidence of pointer arithmetic and image-relative references

For anti-cheat and game security, relocation behavior is important when binaries are loaded in unexpected contexts or when custom loaders are used.

## PE relocation architecture

Relocations are defined by the `IMAGE_DIRECTORY_ENTRY_BASERELOC` directory. The data is normally stored in the `.reloc` section.

The relocation table is composed of a sequence of `IMAGE_BASE_RELOCATION` blocks.

Each block contains:
- `PageRVA` — the base RVA for the block
- `SizeOfBlock` — block size including the header
- a list of 16-bit relocation entries

Each 16-bit entry contains:
- top 4 bits: relocation type
- bottom 12 bits: offset within the page

### Relocation types

Common PE relocation types include:
- `IMAGE_REL_BASED_ABSOLUTE` (0) — no fixup, used to pad the block
- `IMAGE_REL_BASED_HIGH` (1) — high 16 bits of a 32-bit address
- `IMAGE_REL_BASED_LOW` (2) — low 16 bits of a 32-bit address
- `IMAGE_REL_BASED_HIGHLOW` (3) — 32-bit address fixup
- `IMAGE_REL_BASED_HIGHADJ` (4) — high 16 bits with adjustment
- `IMAGE_REL_BASED_DIR64` (10) — 64-bit address fixup

In modern x64 PE files, `IMAGE_REL_BASED_DIR64` is the primary relocation type.

### Relocation entry computation

The relocated address is computed by adding the delta between the actual load base and the preferred base to the target field.

For example, with a `DIR64` relocation:

```cpp
*reinterpret_cast<uint64_t*>(patchAddr) += static_cast<uint64_t>(imageDelta);
```

## Loader behavior

During image load, the Windows loader performs:
1. allocation of memory for the image at the chosen base
2. copy of sections into the mapped memory
3. application of relocation fixups if the chosen base differs from `ImageBase`

If the image cannot be loaded at its preferred base and relocations are stripped or invalid, the load fails unless the image is manually relocated with a custom loader.

### ASLR and dynamic base

`IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE` indicates the binary supports ASLR. If this flag is set but the relocation table is missing, the image is malformed.

### Relocation order and dependencies

Relocations are applied before import resolution and TLS callbacks. This ensures all image-relative pointers are correct prior to runtime initialization.

## Practical analysis workflow

### Step 1: locate the relocation directory

Validate the `IMAGE_DIRECTORY_ENTRY_BASERELOC` entry and ensure it points to a readable section.

### Step 2: enumerate relocation blocks

Parse each `IMAGE_BASE_RELOCATION` block:
- verify `PageRVA` is in a valid section
- verify `SizeOfBlock` is at least `sizeof(IMAGE_BASE_RELOCATION)`
- parse each 16-bit relocation entry

### Step 3: categorize relocation targets

Identify relocated fields that correspond to:
- imported function pointers
- global variables
- jump tables or function pointers in vtables
- data structure offsets

This helps distinguish between actual code/data references and unrelated data.

### Step 4: inspect relocation coverage

A full relocation table is typically present in relocatable images. If coverage is sparse, the binary may use a custom loader or may not be intended for relocation.

### Step 5: detect stripped or manipulated relocations

Signs of suspicious relocation tables:
- invalid page RVAs
- entries with unexpected relocation types
- blocks with zeroed entries except padding
- relocation data that points to non-executable sections only

Protectors and packers sometimes corrupt or encrypt the `.reloc` section to evade analysis.

## Manual mapping and custom loader example

Manual mapping requires explicit relocation of all image-relative pointers.

```cpp
void apply_relocations(uint8_t* image, intptr_t delta) {
    auto dos = reinterpret_cast<PIMAGE_DOS_HEADER>(image);
    auto nt = reinterpret_cast<PIMAGE_NT_HEADERS>(image + dos->e_lfanew);
    auto relocDir = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC];
    if (!relocDir.VirtualAddress) return;

    auto reloc = reinterpret_cast<PIMAGE_BASE_RELOCATION>(image + relocDir.VirtualAddress);
    auto end = reinterpret_cast<uint8_t*>(reloc) + relocDir.Size;

    while (reinterpret_cast<uint8_t*>(reloc) < end && reloc->SizeOfBlock) {
        auto entryCount = (reloc->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(uint16_t);
        auto entries = reinterpret_cast<uint16_t*>(reloc + 1);
        for (uint32_t i = 0; i < entryCount; ++i) {
            uint16_t entry = entries[i];
            uint16_t type = entry >> 12;
            uint16_t offset = entry & 0x0FFF;
            uint8_t* patchAddr = image + reloc->VirtualAddress + offset;
            switch (type) {
            case IMAGE_REL_BASED_DIR64:
                *reinterpret_cast<uint64_t*>(patchAddr) += static_cast<uint64_t>(delta);
                break;
            case IMAGE_REL_BASED_HIGHLOW:
                *reinterpret_cast<uint32_t*>(patchAddr) += static_cast<uint32_t>(delta);
                break;
            case IMAGE_REL_BASED_ABSOLUTE:
                break;
            default:
                // handle or log unsupported relocation type
                break;
            }
        }
        reloc = reinterpret_cast<PIMAGE_BASE_RELOCATION*>(reinterpret_cast<uint8_t*>(reloc) + reloc->SizeOfBlock);
    }
}
```

## Assembly example

Inspecting relocation fixups in assembly is rare, but you can identify initialization code that applies fixups in a custom loader.

A relocation loop may look like:

```asm
mov rax, [reloc_table]
mov rcx, [delta]
.rel_loop:
    mov edx, [rax + 4]      ; PageRVA
    mov ebx, [rax + 8]      ; SizeOfBlock
    add rax, 12
    ; process relocation entries
    ; patch at [image_base + edx + offset]
    add rax, ebx
    cmp rax, end_of_relocs
    jb .rel_loop
```

## Reverse engineering insights

### Image with no relocation table

A missing `.reloc` section indicates a fixed-base image or a custom loader. This is common in:
- kernel modules and drivers with fixed load addresses
- protected executables that use manual mapping
- some game engine runtimes optimized for a known base

In such cases, the binary may only work when loaded at its preferred base, or a separate bootstrap loader may exist.

### Partial relocation tables

Some binaries relocate only selected pointers. This can happen when the image has only a few absolute references and the rest are handled by position-independent code.

### Relocations in data vs code

Relocations can apply to data pointers, vtable entries, function pointers, and imported function stubs. Identifying the target data type helps determine whether a relocation points to:
- a global object
- a vtable
- a callback pointer
- an imported API thunk

### Relocation and C++ RTTI

C++ RTTI structures contain image-relative pointers. A relocation table ensures RTTI descriptors and vtable pointers remain valid when the image moves.

## Game and anti-cheat considerations

### Gaming binaries and manual mapping

Game engines may use manual mapping for plugins, mods, and anti-cheat components. In these cases, relocations are applied by custom loaders rather than the OS loader.

Inspect the initialization code for custom relocation loops, especially in loader stubs or packer entry points.

### Anti-cheat module behavior

Anti-cheat binaries often require strict relocation support because they may be injected into untrusted target processes. A missing or corrupted relocation table is a strong indicator of protection or a loader stub.

### Driver relocations

Kernel drivers use PE relocations too, but the kernel loader has restrictions. Drivers may be built with a hard-coded base and no relocation data when they are intended for a specific kernel version.

## Common mistakes

- applying relocations against file offsets instead of RVAs
- assuming `SizeOfBlock` is always aligned to 8 bytes
- failing to check `IMAGE_REL_BASED_ABSOLUTE` entries
- forgetting that relocation entries are page-relative offsets
- using the preferred image base when the binary was loaded elsewhere

## Practical tips

- always validate the relocation directory before processing
- check whether the image supports `IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE`
- use relocation coverage to infer whether the binary is meant for relocation
- when manually mapping, apply relocations before imports and TLS callbacks
- document relocation anomalies as evidence of custom loaders or protectors

## Tools & Commands

- Use `pefile`, `rizin`, `radare2`, or `CFF Explorer` to inspect `.reloc` sections and parse relocation blocks.
- For manual mapping, use debuggers or custom scripts to apply relocations and verify mapped image correctness.

## Validation Checklist

- Confirm relocation blocks map to valid page RVAs and that patched addresses point into expected sections.
- Validate relocation behavior by loading the image in a controlled process and confirming symbol/RTTI addresses are correct.

## Cross-links

- `../knowledge/pe.md`
- `../knowledge/imports.md`
- `../knowledge/exports.md`
- `../patterns/packer.md`
- `../recipes/unpack-binary.md`

## References

- Microsoft PE/COFF Specification — Base Relocation Table
- Microsoft Windows Internals — Image Relocation
- Malware analysis references on manual mapping and ASLR bypass techniques

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

