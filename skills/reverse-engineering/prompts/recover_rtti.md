---
title: Prompt: Recover RTTI Structures
skill: reverse-engineering
category: prompts
difficulty: intermediate
tags: [pe, x64, debug, elf]
updated: 2026-07-05
---
# Prompt: Recover RTTI Structures

## Objective

Extract all C++ class names and inheritance relationships from a stripped MSVC binary using Run-Time Type Information (RTTI). Produce a complete class hierarchy map with vtable addresses, class names, and base class relationships.

---

## Methodology

### Step 1 — Verify RTTI Is Present

RTTI may be stripped with `/GR-` compiler flag. Check:
1. Search .rdata and .data for strings starting with `.?AV` or `.?AU` — these are TypeDescriptor names.
2. If none found → binary compiled with `/GR-` → class names unrecoverable via RTTI.
3. If found → RTTI is intact → proceed.

### Step 2 — Locate TypeDescriptors

TypeDescriptor layout (MSVC x64):
```
+0x00  QWORD  pVFTable   → type_info's vtable (in .rdata)
+0x08  QWORD  spare      = 0
+0x10  CHAR[] name       → ".?AVClassName@@" null-terminated
```

For each `.?AV` string found:
- The TypeDescriptor base is at `string_address - 0x10`
- Verify `spare` field at `TD + 0x08` = 0
- Verify `pVFTable` at `TD + 0x00` points into .rdata (type_info vtable)

### Step 3 — Find Complete Object Locators (COLs)

For each TypeDescriptor, find all COLs that reference it.

COL layout (MSVC x64):
```cpp
struct _RTTICompleteObjectLocator {
    DWORD signature;        // +0x00: must be 1 for x64
    DWORD offset;           // +0x04: byte offset from object to this vtable's vptr
    DWORD cdOffset;         // +0x08: constructor displacement
    INT   pTypeDescriptor;  // +0x0C: RVA to TypeDescriptor
    INT   pClassDescriptor; // +0x10: RVA to ClassHierarchyDescriptor
    INT   pSelf;            // +0x14: RVA to this COL (self-referential)
};
```

Scan .rdata for structures where:
- `DWORD[0]` = 1 (x64 signature)
- `INT[5]` (pSelf at +0x14): `image_base + pSelf == COL_address`

The self-referential pSelf field is the unique validation key for x64 COLs.

### Step 4 — Extract Class Information From Each COL

For each valid COL:

```python
# Given: col_va = virtual address of COL, image_base

# Step A: Get TypeDescriptor
td_rva  = signed_dword(col_va + 0x0C)
td_va   = image_base + td_rva
name    = cstring(td_va + 0x10)    # ".?AVMyClass@@"
demangled = demangle(name)          # "class MyClass"

# Step B: Get vtable address
# vtable is immediately after the COL pointer slot
# COL is stored at vtable[-1], so vtable[0] = col_va + 8
vtable_va = col_va + 8

# Step C: Get ClassHierarchyDescriptor
chd_rva = signed_dword(col_va + 0x10)
chd_va  = image_base + chd_rva

# Step D: Get base classes
num_bases = dword(chd_va + 0x08)
arr_rva   = signed_dword(chd_va + 0x0C)
arr_va    = image_base + arr_rva

bases = []
for i in range(num_bases):
    bcd_rva = signed_dword(arr_va + i * 4)
    bcd_va  = image_base + bcd_rva
    btd_rva = signed_dword(bcd_va + 0x00)
    btd_va  = image_base + btd_rva
    bname   = cstring(btd_va + 0x10)
    bases.append(bname)
# bases[0] is always the class itself
```

### Step 5 — Count Vtable Slots

For each vtable:
1. Read consecutive 8-byte values from `vtable_va` onward.
2. Each value must point into an executable section (.text).
3. Stop at the first value that is zero or does not point into executable memory.
4. Slot count = number of valid consecutive pointers.

### Step 6 — Build Inheritance Tree

From the base class list for each class (excluding index 0 which is self):

```
CNetworkManager
  └─ CBase
       └─ IUnknown

CConnectionHandler
  ├─ CBase
  └─ IDisposable
       └─ IUnknown
```

For multiple inheritance, note that the primary vtable (offset=0) covers the first base's virtual functions. Secondary vtables (offset > 0) cover subsequent bases.

### Step 7 — Handle Multiple Inheritance COLs

A class with multiple bases has multiple COLs (one per vtable):
- Primary COL: `offset = 0`
- Secondary COL: `offset = N` (byte offset within complete object to this vptr)

Each COL points to the same ClassHierarchyDescriptor — use this to group them.

### Step 8 — Identify Abstract Classes

An abstract class has at least one vtable slot pointing to `__purecall`:
- Search for the `__purecall` function address (usually exported by msvcrt or embedded in the binary)
- Any vtable slot equal to that address is a pure virtual function
- If all virtual functions in a class are pure → fully abstract interface

---

## Checklist

- [ ] Confirmed RTTI is present (`.?AV` strings found in .rdata)
- [ ] All TypeDescriptors located and validated
- [ ] All COLs found and validated via pSelf check
- [ ] Class names extracted and demangled for all COLs
- [ ] ClassHierarchyDescriptors parsed for all classes
- [ ] Base class arrays read for all classes
- [ ] Vtable slot counts determined for all vtables
- [ ] Multiple inheritance COLs grouped correctly
- [ ] Abstract classes (with `__purecall` slots) identified
- [ ] Complete inheritance tree built
- [ ] All vtable addresses documented with class names

---

## Expected Output

```markdown
## RTTI Recovery Results

### Classes Found: 47

| Class Name              | Vtable RVA   | Base Classes                    | Slots | Abstract |
|-------------------------|--------------|----------------------------------|-------|----------|
| CApplication            | 0x001A2000   | CObject                          | 6     | No       |
| CNetworkManager         | 0x001A2080   | CObject, INetworkInterface       | 12    | No       |
| INetworkInterface       | 0x001A2200   | (none)                           | 4     | Yes      |
| CConnectionHandler      | 0x001A2280   | CObject, IDisposable             | 8     | No       |
| IDisposable             | 0x001A2400   | (none)                           | 1     | Yes      |
...

### Inheritance Tree

CObject
├── CApplication
├── CNetworkManager (also: INetworkInterface)
└── CConnectionHandler (also: IDisposable)

INetworkInterface (abstract — 4 pure virtual slots)
IDisposable (abstract — 1 pure virtual slot)
```

---

## Validation

1. Spot-check 5 random COLs: verify pSelf RVA resolves back to COL address.
2. Verify vtable[-1] for 5 randomly chosen live objects in the debugger matches the COL address.
3. Verify class name matches known behavior (a class named `CSocketManager` should reference socket APIs).
4. Verify base class list makes semantic sense — a network class inheriting from a file class is suspicious.
5. For abstract classes, verify `__purecall` slot pointers in the debugger.

---

## Common Mistakes

- Not adding image_base to RVAs — all COL internal fields are RVAs on x64, not absolute pointers.
- Validating COL with signature=1 alone — always also validate pSelf.
- Treating bases[0] as a base class — it is always the class itself, not a parent.
- Missing secondary COLs for multiple inheritance classes — they have different COL offsets.
- Confusing slot count with method count — destructors take 1-2 slots in MSVC but are not user-defined methods.
- Missing RTTI for classes compiled with `/GR-` — no error thrown, just no data to find.

## Related Material

### Knowledge
- [common-instructions](../knowledge/assembly/common-instructions.md)
- [compiler-patterns](../knowledge/assembly/compiler-patterns.md)
- [exceptions](../knowledge/cpp/exceptions.md)

### Prompts
- [analyze_binary](analyze_binary.md)
- [analyze_crash](analyze_crash.md)
- [analyze_memory](analyze_memory.md)

