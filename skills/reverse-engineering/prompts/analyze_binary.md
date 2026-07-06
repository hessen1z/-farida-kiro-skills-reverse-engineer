---
title: Prompt: Analyze Binary
skill: reverse-engineering
category: prompts
difficulty: intermediate
tags: [pe, windows, x64, driver, pdb, gui, kernel, debug, dll, elf]
updated: 2026-07-05
---
# Prompt: Analyze Binary

## Objective

Perform a complete initial analysis of an unknown Windows PE binary. Produce a structured report covering file type, packing status, capabilities, imported APIs, identified classes, key algorithms, and entry points for deeper analysis. This is the triage phase — the goal is maximum information density in minimum time.

---

## Methodology

### Step 1 — File Identification

Before loading in any disassembler, identify the binary type:

1. Read the first 2 bytes — `4D 5A` (MZ) confirms a PE file.
2. Read `e_lfanew` at offset 0x3C to find the NT headers.
3. Read `IMAGE_FILE_HEADER.Machine`: `0x8664` = x64, `0x014C` = x86.
4. Read `IMAGE_OPTIONAL_HEADER.Magic`: `0x020B` = PE32+, `0x010B` = PE32.
5. Read `IMAGE_OPTIONAL_HEADER.Subsystem`: 2 = GUI, 3 = console, 1 = native driver.
6. Check `DataDirectory[14]` (CLR header) — if present, binary is .NET managed code.
7. Check `IMAGE_FILE_HEADER.Characteristics` for `IMAGE_FILE_DLL` (0x2000).

### Step 2 — Packing Detection

1. Compute entropy for each section: entropy > 7.0 bits/byte = likely packed/encrypted.
2. Check import table size: only LoadLibrary + GetProcAddress = manual import resolution.
3. Check entry point section — if EP is not in `.text`, suspect a packing stub.
4. Check for known packer section names: `.UPX0`, `.MPRESS1`, `.nsp0`, `.themida`, `.vmp0`.
5. Check overlay: data after the last section = appended payload or self-extracting archive.

If packed: unpack first (see workflow.md Phase 2) before proceeding.

### Step 3 — Security Mitigations Audit

Read `IMAGE_OPTIONAL_HEADER.DllCharacteristics`:

| Flag  | Value  | Meaning                    |
|-------|--------|----------------------------|
| ASLR  | 0x0040 | Dynamic base enabled       |
| DEP   | 0x0100 | NX compatible              |
| CFG   | 0x4000 | Control Flow Guard enabled |
| HiEnt | 0x0020 | High-entropy 64-bit ASLR   |

Read `IMAGE_LOAD_CONFIG_DIRECTORY` for:
- `GuardCFCheckFunctionPointer` — CFG check stub address
- `SecurityCookie` — stack cookie value
- `SEHandlerTable` / `SEHandlerCount` — SafeSEH handler list

### Step 4 — Import Analysis

For each imported DLL and function:

1. Note all DLLs — the DLL list alone reveals the binary's capability surface.
2. Flag high-interest imports:
   - `VirtualAlloc` + `PAGE_EXECUTE_*` → code injection or JIT
   - `CreateRemoteThread`, `WriteProcessMemory` → process injection
   - `RegOpenKey`, `RegSetValue` → registry persistence
   - `WSAConnect`, `InternetOpen`, `WinHttpOpen` → network activity
   - `CryptEncrypt`, `BCryptEncrypt` → encryption
   - `IsDebuggerPresent`, `NtQueryInformationProcess` → anti-debug
   - `LoadLibrary` only (no others) → manual import resolution post-unpack
3. Note the absence of expected imports — a DLL without CreateFile that does file I/O resolves it dynamically.

### Step 5 — Export Analysis

For DLLs:
1. List all exported names and ordinals.
2. Identify forwarded exports.
3. Identify ordinal-only exports (no name string).
4. Note the DLL name embedded in the export directory.

### Step 6 — String Analysis

1. Search for UTF-8 and UTF-16 strings in all sections.
2. Categorize found strings:
   - URLs, IPs, domain names → network targets
   - Registry paths → persistence or config locations
   - File paths → disk artifacts
   - Error messages → function purpose identification
   - Version strings → build identification
   - RTTI names (`.?AV...@@`) → C++ class names
   - Crypto constants as strings → algorithm identification
3. Flag encrypted/obfuscated string sections (no readable strings in large data blobs).

### Step 7 — Section Analysis

For each section:

| Field               | What to record                                    |
|---------------------|---------------------------------------------------|
| Name                | Standard (.text, .rdata, .data) or unusual        |
| VirtualAddress      | RVA in memory                                     |
| VirtualSize         | Actual size used                                  |
| Characteristics     | Execute / Read / Write flags                      |
| Entropy             | > 6.5 = compressed, > 7.0 = encrypted             |

### Step 8 — Entry Point and Main Function

1. Note the entry point RVA and the section it falls in.
2. Load in IDA / Ghidra with auto-analysis.
3. Apply FLIRT signatures for the target platform (MSVC 2019+, MSVC 2022, etc.).
4. Identify the CRT startup function (`__tmainCRTStartup` or `mainCRTStartup`).
5. Find the real `main` / `WinMain` — it is the last non-CRT call before `ExitProcess`.

### Step 9 — C++ Class Discovery

If the binary is MSVC-compiled C++:

1. Search for `.?AV` strings in .rdata / .data — each is a TypeDescriptor name.
2. Locate each TypeDescriptor (string address - 16 bytes).
3. Find all COLs that reference each TypeDescriptor via their `pTypeDescriptor` RVA.
4. Map COL → vtable (vtable is at COL + 8 in .rdata).
5. Build a class list with: mangled name, demangled name, vtable address, slot count.
6. Build the inheritance tree from ClassHierarchyDescriptor.

### Step 10 — Algorithm Identification

1. Search for known cryptographic constants (see cheatsheet.md).
2. Note all compression-related imports (RtlDecompressBuffer, LZO, etc.).
3. Identify hashing loops: XOR with rotating key, MOD prime, 256-byte S-box.
4. Flag any custom serialization: structured read/write of fields in fixed order.

---

## Checklist

- [ ] File type confirmed (PE32 / PE32+ / .NET)
- [ ] Architecture confirmed (x86 / x64)
- [ ] Subsystem identified (GUI / console / native)
- [ ] Packing status determined — unpacked if necessary
- [ ] Security mitigations documented (ASLR, DEP, CFG, stack cookie)
- [ ] Import table fully read and categorized
- [ ] Export table read (DLLs only)
- [ ] Debug directory checked — PDB path recorded if present
- [ ] TLS directory checked — callback addresses noted
- [ ] Section list documented with entropy values
- [ ] All readable strings collected and categorized
- [ ] Entry point identified; real main located
- [ ] FLIRT signatures applied
- [ ] C++ class list built from RTTI (if applicable)
- [ ] Cryptographic constants identified

---

## Expected Output

```markdown
## Binary Analysis Report

**File:** target.exe
**SHA-256:** [hash]
**Architecture:** x64 PE32+
**Subsystem:** Console
**Timestamp:** 0x64A1B2C3 (approx. 2023-07-XX)
**Packed:** No
**ASLR:** Yes | **DEP:** Yes | **CFG:** Yes | **Stack Cookie:** Yes

### Import Summary
- kernel32.dll: CreateFile, ReadFile, WriteFile, VirtualAlloc, LoadLibrary
- advapi32.dll: RegOpenKeyEx, RegSetValueEx, CryptAcquireContext
- ws2_32.dll: WSAStartup, connect, send, recv

### Capability Assessment
- File I/O: Yes (CreateFile, ReadFile, WriteFile)
- Network: Yes (ws2_32 usage — likely C2 communication)
- Encryption: Yes (CryptAcquireContext — CAPI-based)
- Persistence: Yes (Registry writes)
- Anti-debug: Possible (VirtualAlloc + PAGE_EXECUTE_READWRITE)

### C++ Classes Identified
| Class               | vtable RVA  | Base Classes       | Slots |
|---------------------|-------------|--------------------|-------|
| CNetworkManager     | 0x001A2000  | CBase              | 12    |
| CConnectionHandler  | 0x001A2100  | CBase, IDisposable | 8     |

### Key Functions (Entry Points for Deep Analysis)
- 0x14001F800: Probable main dispatch loop (all network activity routes here)
- 0x140023400: Encryption routine (AES S-box constants found at 0x14005A000)
- 0x14002B000: Registry persistence installer
```

---

## Validation

After producing the report:

1. Cross-check capability assessment against observed imports — every claimed capability needs an import or dynamic resolution.
2. Verify at least one C++ class name against its COL.pSelf RVA — confirms RTTI is intact.
3. Confirm entry point is in .text section — if not, unpacking was incomplete.
4. Verify the SHA-256 hash matches the file on disk — ensures the report is file-specific.
5. Confirm all TLS callback addresses fall within the module's mapped range.

---

## Common Mistakes

- Starting deep analysis before checking for packing — wastes hours on stub code.
- Missing TLS callbacks — anti-debug fires before entry point breakpoint.
- Skipping import analysis — capability surface is the fastest indicator of binary purpose.
- Trusting the compile timestamp — many tools fake or zero it.
- Treating all `.rdata` strings as user-visible strings — many are RTTI names or format strings for internal logging.
- Ignoring ordinal-only imports — they are often the most interesting undocumented functions.
- Not checking CFG — hooks without CFG bypass will crash immediately on protected binaries.

## Related Material

### Knowledge
- [common-instructions](../knowledge/assembly/common-instructions.md)
- [compiler-patterns](../knowledge/assembly/compiler-patterns.md)
- [exceptions](../knowledge/cpp/exceptions.md)

### Prompts
- [analyze_crash](analyze_crash.md)
- [analyze_memory](analyze_memory.md)
- [build_reclass](build_reclass.md)

