---
title: Resource Sections
skill: binary-analysis
category: knowledge
difficulty: intermediate
tags: [pe, windows, loader, driver, malware, gui, debug, dll, elf]
updated: 2026-07-05
---
# Resource Sections

## Overview

PE resource sections store application assets, configuration data, and UI elements. Resources are organized as a hierarchical tree keyed by type, name, and language.

Resource analysis is valuable for:
- extracting strings, dialogs, icons, and version metadata
- identifying embedded configuration, server addresses, or plugin manifests
- locating hidden payloads, encrypted assets, and digital certificates

## PE Resource architecture

Resources live in the `.rsrc` section and are accessed through a directory tree.

### Resource directory structure

The resource section uses nested directories:
- root directory: entries by type
- type directory: entries by name or ID
- name directory: entries by language

Each leaf entry points to an `IMAGE_RESOURCE_DATA_ENTRY`, which describes the resource size, code page, and byte offset.

### Key resource types

Common resource types include:
- `RT_VERSION` — version information and file metadata
- `RT_STRING` — localized strings stored in string tables
- `RT_DIALOG` — dialog templates and controls
- `RT_ICON` / `RT_GROUP_ICON` — icon images
- `RT_MANIFEST` — application manifests and policies
- `RT_CERTIFICATE` — embedded digital signatures

## Analysis workflow

### 1. Locate the `.rsrc` section

Confirm the resource section exists in the section table and validate its file offset and virtual address range.

### 2. Parse the resource tree

Walk the root directory, then nested type/name/language directories. Resolve each `IMAGE_RESOURCE_DATA_ENTRY` to a file offset.

### 3. Extract resource payloads

For each data entry:
- read the resource bytes
- decode strings, manifests, icons, or dialogs
- preserve language and ID metadata

### 4. Inspect version and manifest data

Version resources often contain:
- product name, internal name, company name
- file and product version strings
- build flags and platform targets

Manifests may include:
- `requestedExecutionLevel`
- DLL loading policies
- compatibility and security settings

### 5. Look for hidden or malicious resources

Review resource data for:
- encrypted payloads disguised as strings or blobs
- embedded executables or drivers
- certificate blobs and white-label data

## Practical pointers

### Resource strings vs symbol names

Resource IDs are numeric values, not symbol names. The loader resolves them with `FindResource` or `LoadResource` APIs.

### Resource names and IDs

Resources may be identified by numeric IDs or by unicode names. A named resource tree can reveal custom internal assets.

### Runtime resolution

Resources are loaded via APIs such as `FindResourceEx`, `LoadResource`, and `LockResource`. Static analysis should map these calls to the resource tree.

## Example: parse a version resource in C++

```cpp
#include <windows.h>
#include <vector>

bool ExtractVersionInfo(HMODULE module) {
    auto hData = FindResource(module, MAKEINTRESOURCE(VS_VERSION_INFO), RT_VERSION);
    if (!hData) return false;

    auto hLoaded = LoadResource(module, hData);
    if (!hLoaded) return false;

    auto ptr = reinterpret_cast<VS_FIXEDFILEINFO*>(LockResource(hLoaded));
    if (!ptr) return false;

    // Use ptr->dwFileVersionMS / dwFileVersionLS
    return true;
}
```

## Reverse engineering notes

- Resource metadata often contains product identifiers, version strings, and copyright notices.
- Malware may hide configuration or encryption keys in otherwise innocent-looking resource blobs.
- Manifests can reveal whether the binary was built for `asInvoker`, `highestAvailable`, or `requireAdministrator`.

## Debugging notes

- Missing or corrupt resource data can cause UI load failures or manifest-related policy errors.
- Resource loading errors may surface as `ERROR_RESOURCE_DATA_NOT_FOUND` or `ERROR_BAD_EXE_FORMAT`.

## Common mistakes

- Assuming resource IDs map to function names.
- Treating all `.rsrc` content as text; many resources are binary images or compressed data.
- Ignoring localized language directories when extracting strings.

## Cross-links

- `../knowledge/pe.md`
- `../knowledge/imports.md`
- `../knowledge/exports.md`
- `../recipes/recover-symbols.md`

## References

- Microsoft PE/COFF specification — Resource Directory
- Windows resource APIs: `FindResource`, `LoadResource`, `LockResource`

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

