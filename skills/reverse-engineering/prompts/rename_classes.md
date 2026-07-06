---
title: Prompt: Rename Classes
skill: reverse-engineering
category: prompts
difficulty: intermediate
tags: [pe, gui, debug, dll]
updated: 2026-07-05
---
# Prompt: Rename Classes

## Objective

Assign accurate, consistent names to all recovered C++ classes in a stripped MSVC binary. Build a class naming table that covers all identified vtables, with demangled names, aliases, and confidence ratings.

---

## Methodology

### Step 1 — Collect All RTTI Names

From RTTI recovery (see `recover_rtti.md`), collect all mangled TypeDescriptor names:
```
.?AVCApplication@@           → CApplication
.?AVCNetworkManager@@        → CNetworkManager
.?AVCConnectionHandler@@     → CConnectionHandler
.?AUINetworkInterface@@      → INetworkInterface  (struct/interface)
.?AVCObject@@                → CObject
.?AV?$CList@VCEntity@@@@    → CList<CEntity>      (template)
```

These names are ground truth — use them verbatim (demangled) as class names.

### Step 2 — Demangle All Names

```python
import ctypes

def demangle_msvc(mangled):
    dbghelp = ctypes.WinDLL("dbghelp.dll")
    buf = ctypes.create_string_buffer(512)
    result = dbghelp.UnDecorateSymbolName(
        mangled.encode(), buf, 512,
        0x2000  # UNDNAME_NAME_ONLY
    )
    return buf.value.decode() if result else mangled

# Examples:
demangle_msvc(".?AVCNetworkManager@@")  → "CNetworkManager"
demangle_msvc(".?AUINetworkInterface@@") → "INetworkInterface"
demangle_msvc(".?AV?$CList@VCEntity@@@@") → "CList<CEntity>"
```

### Step 3 — Apply Class Names in IDA

For each recovered class:

1. Name the TypeDescriptor: `TypeDescriptor_CNetworkManager`
2. Name the COL: `rtti_col_CNetworkManager`
3. Name the vtable: `vtable_CNetworkManager`
4. Name the constructor: `CNetworkManager__CNetworkManager`
5. Name the destructor body: `CNetworkManager__dtor`
6. Name the scalar deleting destructor slot: `CNetworkManager__dtor_scalar`
7. Name the vector deleting destructor slot: `CNetworkManager__dtor_vector`

For multiple inheritance secondary vtables:
- `vtable_CNetworkManager_for_INetworkInterface`

### Step 4 — Handle Classes Without RTTI

Some classes lack RTTI (compiled with `/GR-`, templates not instantiated, or POD types).

**Evidence-based naming for non-RTTI classes:**

| Evidence                                              | Derived name                   |
|-------------------------------------------------------|--------------------------------|
| Log string: `"PlayerManager::Update"`                 | `CPlayerManager`               |
| Allocates a fixed 0x68 bytes, has 5 virtual methods   | Combine with other evidence    |
| Only used for socket operations                       | `CSocketContext` (provisional) |
| Has methods matching known interface pattern          | `IXxx` prefix                  |

Apply `possible_` prefix for all non-RTTI class names.

### Step 5 — Handle Template Classes

Template instantiations appear in RTTI as:
- `.?AV?$CList@VCEntity@@@@` → `CList<CEntity>`
- `.?AV?$CMap@HVCPlayer@@@@` → `CMap<int, CPlayer>`

Naming convention:
- IDA type: `CList_CEntity` (no angle brackets — IDA type names don't support them)
- Comment: `// CList<CEntity>`
- Local type alias in IDA: `typedef CList_CEntity CList_CEntity_t;`

### Step 6 — Establish Interface Naming Convention

From the TypeDescriptor prefix:
- `.?AV` → `class` → use `C` prefix for concrete classes: `CNetworkManager`
- `.?AU` → `struct` or interface → use `I` prefix for pure virtual: `INetworkInterface`
- `.?AW` → union → use `U` prefix

### Step 7 — Build Class Naming Table

```markdown
| Mangled Name                     | Class Name              | Type     | Vtable RVA   | Confidence |
|----------------------------------|-------------------------|----------|--------------|------------|
| .?AVCApplication@@               | CApplication            | class    | 0x001A2000   | HIGH (RTTI)|
| .?AVCNetworkManager@@            | CNetworkManager         | class    | 0x001A2080   | HIGH (RTTI)|
| .?AUINetworkInterface@@          | INetworkInterface       | interface| 0x001A2200   | HIGH (RTTI)|
| .?AV?$CList@VCEntity@@@@        | CList<CEntity>          | template | 0x001A2300   | HIGH (RTTI)|
| (no RTTI)                        | possible_CSocketContext | class    | 0x001A2400   | MEDIUM     |
```

---

## Checklist

- [ ] All RTTI TypeDescriptor strings collected
- [ ] All names demangled and human-readable
- [ ] All vtables named `vtable_ClassName`
- [ ] All COLs named `rtti_col_ClassName`
- [ ] Constructors named `ClassName__ClassName`
- [ ] Destructors named `ClassName__dtor`
- [ ] Template class names handle angle brackets via underscore convention
- [ ] Interface classes use `I` prefix
- [ ] Non-RTTI classes use `possible_` prefix
- [ ] Class naming table produced and documented

---

## Expected Output

```
Classes named from RTTI: 47
  - Concrete classes (C prefix):  38
  - Interfaces (I prefix):         6
  - Template instantiations:       3

Classes with evidence-based names (possible_): 12
Classes with no identifiable name (sub_):       4
```

Full IDA local types created for all 47 RTTI-confirmed classes.

---

## Validation

1. Verify each vtable name: read vtable[-1] → COL → TypeDescriptor → name matches what you set.
2. Check for duplicate class names — two vtables with the same name indicates a COMDAT folding edge case.
3. In debugger: at a virtual call, `[RCX-8]` → COL → class name must match the vtable name.
4. Verify template class instances: `CList<CEntity>` and `CList<CPlayer>` must be separate names.

---

## Common Mistakes

- Keeping angle brackets in IDA type names — IDA parser rejects them.
- Treating `.?AU` (struct) as the same as `.?AV` (class) — naming convention differs.
- Not distinguishing abstract interfaces (I prefix) from concrete implementations (C prefix).
- Naming COMDAT-folded classes with only one name — both names are valid and should be documented.
- Using abbreviated names inconsistently: `NetMgr` in one place, `NetworkManager` in another.

## Related Material

### Knowledge
- [common-instructions](../knowledge/assembly/common-instructions.md)
- [compiler-patterns](../knowledge/assembly/compiler-patterns.md)
- [exceptions](../knowledge/cpp/exceptions.md)

### Prompts
- [analyze_binary](analyze_binary.md)
- [analyze_crash](analyze_crash.md)
- [analyze_memory](analyze_memory.md)

