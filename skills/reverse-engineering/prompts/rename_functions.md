---
title: Prompt: Rename Functions
skill: reverse-engineering
category: prompts
difficulty: intermediate
tags: [pe, windows, pdb, debug, dll, elf]
updated: 2026-07-05
---
# Prompt: Rename Functions

## Objective

Systematically rename all unnamed functions in a stripped binary with high-confidence, evidence-based names. Apply consistent naming conventions. Document the evidence for every rename.

---

## Methodology

### Step 1 — Apply FLIRT Signatures First

Before any manual renaming, let IDA recognize known library code:

1. Go to File → Load File → FLIRT Signature File.
2. Apply all relevant signatures:
   - `vc32rtf.sig` / `vc64rtf.sig` — MSVC 2019/2022 CRT
   - `mssdk.sig` — Windows SDK functions
   - `seh.sig` — SEH helpers
   - `boost_*.sig` — Boost library (if applicable)
3. All recognized functions get names automatically — do not rename them manually.

### Step 2 — Rename from RTTI

RTTI is the highest-confidence source:

1. Find all vtables via RTTI (see `recover_rtti.md`).
2. For each vtable, name the vtable itself: `vtable_ClassName`.
3. Name slot 0: `ClassName__dtor_scalar`.
4. Name slot 1: `ClassName__dtor_vector`.
5. For other slots, use the naming from base class if inherited (same address as base vtable slot).

### Step 3 — Rename from Exports

Exported functions have reliable names:

```python
import idautils, idc
for ea, name, ordinal in idautils.Entries():
    print(f"{ea:#x}: {name}")
    # These are already named by IDA — verify they are correct
```

If a DLL has forwarded exports, the target function should use the source name.

### Step 4 — Rename from Cross-References to Strings

1. In IDA: Search → Text → search for specific error/log strings.
2. XREF to string → function body.
3. The function containing `"Failed to connect to %s:%d"` is likely `Connect` or `Reconnect`.
4. Name evidence: `"Initializing NetworkManager"` → function is `NetworkManager_Init`.
5. Only name based on the string's specific meaning — generic strings like `"Error"` are not enough.

Rules:
- Require the string to be specific enough to identify the function's purpose uniquely.
- Require the function to not be a generic logger — verify it has meaningful logic around the string.

### Step 5 — Rename from Import Usage

A function that exclusively calls a set of related imports has a clear purpose:

| Imports used exclusively                              | Likely name                   |
|-------------------------------------------------------|-------------------------------|
| `CreateFile`, `ReadFile`, `CloseHandle` only          | `ReadFileContent`             |
| `RegOpenKeyEx`, `RegQueryValueEx`, `RegCloseKey`      | `ReadRegistryValue`           |
| `VirtualAlloc`, `memcpy`, `VirtualProtect`            | `InjectShellcode` or `AllocExec` |
| `WSAConnect`, `send`, `recv`                          | `NetworkSend` or `SocketLoop` |
| `CryptAcquireContext`, `CryptCreateHash`, `CryptHashData` | `HashData`               |

### Step 6 — Rename from Call Graph Position

Functions that:
- Are called from only one place → helper function for that caller → name as `CallerName_helper_N`.
- Call exactly one import → thin wrapper → name as `Wrapper_ImportName`.
- Are the last call before `ExitProcess` in the main function → likely cleanup/shutdown.
- Are called in a loop iterating a collection → likely `ProcessItem` or `UpdateAll`.

### Step 7 — Rename from Argument Patterns

Functions whose arguments reveal purpose:

1. First argument is always a specific known class pointer (from RTTI) → member function of that class.
2. Arguments include a string length and buffer → string processing function.
3. Arguments include a socket handle and buffer → network send/receive.
4. Returns `BOOL` and the body is entirely comparisons → validation/check function.

### Step 8 — Confidence-Based Naming Convention

| Confidence | Prefix/Convention | Condition                                    |
|------------|-------------------|----------------------------------------------|
| HIGH       | `ClassName__Method` | RTTI-confirmed class + 2+ evidence signals |
| HIGH       | `Module_Purpose`    | Export name or PDB symbol                   |
| MEDIUM     | `possible_Name`     | 1 strong signal (string or import pattern)  |
| LOW        | `sub_XXXXXXXX`      | Keep default — do not rename                |

### Step 9 — Batch Rename Script

For RTTI-discovered vtable methods:

```python
import idc, idaapi, idautils

VTABLE_NAMES = {
    0x14001A2000: "CNetworkManager",
    0x14001A2080: "CConnectionHandler",
    # ... etc
}

for vtable_va, class_name in VTABLE_NAMES.items():
    idc.set_name(vtable_va - 8, f"rtti_col_{class_name}", idc.SN_NOWARN)
    idc.set_name(vtable_va, f"vtable_{class_name}", idc.SN_NOWARN)

    slot = 0
    while True:
        fn_va = idc.get_qword(vtable_va + slot * 8)
        if not fn_va or not idc.is_code(idc.get_full_flags(fn_va)):
            break
        existing = idc.get_func_name(fn_va)
        if existing.startswith("sub_"):
            idc.set_name(fn_va, f"{class_name}__vslot{slot}", idc.SN_NOWARN)
        slot += 1
```

---

## Checklist

- [ ] FLIRT signatures applied before any manual renaming
- [ ] All RTTI-identified classes have vtables named `vtable_ClassName`
- [ ] All destructor slots named with `__dtor_scalar` / `__dtor_vector` suffix
- [ ] All exported functions verified (IDA auto-names them but verify)
- [ ] String XREFs analyzed for meaningful function names
- [ ] Import usage patterns analyzed for unnamed functions
- [ ] Every rename has documented evidence
- [ ] No LOW-confidence names committed — keep `sub_` prefix
- [ ] `possible_` prefix used for all MEDIUM-confidence names
- [ ] Repeatable comments added to all renamed functions

---

## Expected Output

Annotated IDA database with:
```
Functions renamed: 342 / 1,847 total
  - FLIRT auto-recognized: 156
  - RTTI vtable methods: 89 (sub_* → ClassName__slot_N)
  - String XREF: 47
  - Import pattern: 38
  - Export names: 12
  - Call graph: 0 (too low confidence)

Remaining unnamed: 1,505 (marked sub_*)
```

Plus a rename log:
```
0x140011000  CNetworkManager__Connect         RTTI + "connecting to %s" string
0x140011200  CNetworkManager__Disconnect      RTTI + closesocket call
0x140023400  possible_AES_Encrypt             AES S-box constant + CBC pattern
0x14002B000  possible_RegistryPersist         RegSetValue + RunKey path string
```

---

## Validation

1. Open the Names window (Shift+F4) in IDA — verify no collisions (two functions with same name).
2. Spot-check 10 renamed functions: each must have at least 2 pieces of evidence.
3. Verify all `vtable_` names point to the actual vtable (vtable[-1] is a valid COL).
4. Open the FLIRT-recognized functions — verify they behave consistently with their names.
5. In the debugger: set breakpoints at 5 renamed functions and verify they fire in the expected context.

---

## Common Mistakes

- Renaming from a single string that is used in multiple functions (generic logger).
- Using plural names for methods on singular objects (`players` instead of `player`).
- Forgetting to use repeatable comments — names alone disappear in caller context.
- Not applying FLIRT first — manually renaming CRT functions is a waste of time.
- Naming at LOW confidence — wrong names spread confusion and corrupt future analysis.
- Using abbreviations inconsistently — `Mgr` vs `Manager` in the same codebase.

## Related Material

### Knowledge
- [common-instructions](../knowledge/assembly/common-instructions.md)
- [compiler-patterns](../knowledge/assembly/compiler-patterns.md)
- [exceptions](../knowledge/cpp/exceptions.md)

### Prompts
- [analyze_binary](analyze_binary.md)
- [analyze_crash](analyze_crash.md)
- [analyze_memory](analyze_memory.md)

