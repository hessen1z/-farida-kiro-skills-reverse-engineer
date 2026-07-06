---
title: Prompt: Recover C++ Class Layout
skill: reverse-engineering
category: prompts
difficulty: intermediate
tags: [pe, asm, gui, debug]
updated: 2026-07-05
---
# Prompt: Recover C++ Class Layout

## Objective

Reconstruct a complete C++ class definition from a stripped MSVC binary. Produce an accurate struct layout with all field offsets, types, sizes, and names. The output must be importable into ReClass.NET and usable as an IDA struct type.

---

## Methodology

### Step 1 — Identify the Class Entry Point

Start from one of these sources:
- RTTI TypeDescriptor name (`.?AVMyClass@@`) found in .rdata
- A `new MyClass()` allocation call followed by a constructor call
- A vtable pointer observed in the debugger (`[RCX]` at a virtual call site)
- An XREF to a known string that names the class

### Step 2 — Find and Analyze the Constructor

The constructor is the primary source of field layout. It initializes every field.

1. Find all constructor calls for this class:
   - Follow XREFs to `operator new(sizeof(MyClass))` — the call immediately after is the constructor.
   - Search for `mov [rcx+N], value` sequences — each is a field initialization.
   - The first `mov [rcx], vtable_ptr` always writes the vptr at offset 0.

2. In the constructor body:
   - Record every `[this + offset]` write with its value and width (byte/dword/qword).
   - Note sub-constructors called with `this + offset` as the first argument — those are embedded objects.
   - Note `HeapAlloc`/`new` calls with the result stored in `[this + offset]` — those are pointer fields.

3. Build the initial field map:

```
+0x000  vptr              (qword, from vtable write)
+0x008  field_008         (dword, = 0)
+0x00C  field_00C         (dword, = -1)
+0x010  field_010         (qword, = NULL — pointer)
+0x018  field_018         (float, = 1.0f)
+0x01C  field_01C         (bool, = false)
...
```

### Step 3 — Find and Analyze All Member Functions

1. Collect all virtual functions from the vtable.
2. Collect all non-virtual functions that take the class pointer (this) as RCX.
3. For each method:
   - Note every field it reads or writes: `[rcx+offset]`.
   - Infer type from how the field is used: passed to `sinf` = float, passed to `CreateFile` = HANDLE, compared to `NULL` = pointer.
   - Note field widths from instruction widths: `mov eax, [rcx+8]` = dword, `movss xmm0, [rcx+8]` = float, `movzx eax, byte ptr [rcx+8]` = byte.

### Step 4 — Analyze Destructor for Pointer Fields

The destructor deletes/frees all pointer fields. This confirms which fields are owning pointers vs raw pointers.

1. Find the destructor (vtable slot 0 in MSVC, or slot 1 for scalar deleting destructor).
2. For every `delete [this + offset]` call, mark that field as an owning pointer.
3. For every `CloseHandle [this + offset]` call, mark as HANDLE.
4. Note the order of destruction (reverse of construction order in most cases).

### Step 5 — Determine Class Size

Class size = allocation argument to operator new for this class.

```asm
; Example:
mov  ecx, 0x58        ; sizeof(MyClass) = 0x58 bytes
call operator_new
mov  rcx, rax         ; rcx = this
call MyClass__constructor
```

Cross-check: last field offset + last field size must be ≤ total size (accounting for alignment padding).

### Step 6 — Identify Embedded Objects vs Pointers

Distinguish:
- **Pointer field**: `[this+N]` is 8 bytes, passed to `delete` or `free`, or dereferenced before use.
- **Embedded object**: `lea rcx, [this+N]` passed to a constructor — the sub-object is embedded in place.
- **Array field**: `[this+N]` has size = element_size * count, iterated with `[this+N + i*stride]` pattern.

### Step 7 — Recover Base Class Portion

For inherited classes:

1. Check RTTI ClassHierarchyDescriptor for base classes.
2. The base class subobject is at PMD.mdisp within the derived object (usually offset 0).
3. The base class has its own vtable (or shares slots in the derived vtable for single inheritance).
4. Run this same analysis on the base class first, then embed it as the first field.

### Step 8 — Name Fields

Apply names based on evidence:

| Evidence                                              | Naming                         |
|-------------------------------------------------------|--------------------------------|
| Field passed to `CreateFile` as a handle out-param    | `m_fileHandle`                 |
| Field compared to 0 in a condition named "IsReady"    | `m_isReady`                    |
| Field read in `GetHealth()` virtual function          | `m_health`                     |
| Field = allocation size from `HeapAlloc`              | `m_bufferSize`                 |
| Field contains count of valid elements                | `m_count` or `m_size`          |
| Field points to another recovered class               | `m_pOtherClass`                |
| Field written with result of `timeGetTime`            | `m_lastUpdateTime`             |

---

## Checklist

- [ ] Constructor located and fully analyzed
- [ ] All `[this+offset]` writes recorded with offset, width, and initial value
- [ ] Sub-constructors for embedded objects identified
- [ ] Destructor analyzed — owning pointer fields confirmed
- [ ] Object allocation size found
- [ ] Virtual functions enumerated from vtable
- [ ] Non-virtual member functions identified via RCX usage
- [ ] All field types confirmed by usage context
- [ ] Base class portion identified and recursively recovered
- [ ] Total struct size verified (last field + padding ≤ alloc size)
- [ ] All fields named with evidence
- [ ] IDA struct definition created and applied

---

## Expected Output

```cpp
// Recovered class: CNetworkManager
// vtable @ 0x14001A2000  (12 slots)
// Size: 0x68 bytes
// Base: CBase (offset 0)

struct CNetworkManager {
    /* 0x00 */ void*        vptr;            // vtable pointer
    /* 0x08 */ int          m_state;         // compared to 0/1/2 in state machine
    /* 0x0C */ int          m_errorCode;     // written in error paths, read in GetError()
    /* 0x10 */ CConnection* m_pConnection;   // owned, deleted in destructor
    /* 0x18 */ float        m_timeout;       // passed to select() as timeout
    /* 0x1C */ bool         m_isConnected;   // read in IsConnected() virtual
    /* 0x1D */ uint8_t      _pad[3];         // alignment padding
    /* 0x20 */ SOCKET       m_socket;        // passed to send/recv, closed in dtor
    /* 0x28 */ uint32_t     m_sendBufferSize;// written from config, used in send()
    /* 0x2C */ uint32_t     m_recvBufferSize;
    /* 0x30 */ uint8_t*     m_pSendBuffer;   // owned, HeapAlloc'd in ctor
    /* 0x38 */ uint8_t*     m_pRecvBuffer;   // owned, HeapAlloc'd in ctor
    /* 0x40 */ uint32_t     m_sequenceNum;   // incremented on each send
    /* 0x44 */ uint32_t     m_remotePort;
    /* 0x48 */ char         m_remoteHost[32]; // embedded char array, no pointer
};
// Total: 0x68 bytes ✓ (matches operator new argument)
```

---

## Validation

1. Load the struct into IDA (Local Types → insert) and apply to the constructor — verify all member accesses resolve cleanly.
2. Apply to the destructor — verify all delete/free calls reference pointer fields.
3. Apply to all virtual functions — verify field accesses match the struct layout.
4. Import into ReClass.NET and walk a live object at a debugger breakpoint — verify values make sense at runtime.
5. Verify that `sizeof(struct)` matches the `operator new` argument exactly.

---

## Common Mistakes

- Using the vtable slot count as the class size — completely unrelated.
- Confusing embedded object offsets with pointer dereferences — look for `lea` vs `mov`.
- Missing padding bytes between fields — struct size calculation becomes wrong.
- Not analyzing the destructor — missing ownership information for pointer fields.
- Assigning types from a single use — a field passed to `printf` as `%d` may still be a bool.
- Treating union-like fields as separate — a field accessed as both float and int is a union.
- Not checking base class fields — they occupy the low offsets and shift everything.

## Related Material

### Knowledge
- [common-instructions](../knowledge/assembly/common-instructions.md)
- [compiler-patterns](../knowledge/assembly/compiler-patterns.md)
- [exceptions](../knowledge/cpp/exceptions.md)

### Prompts
- [analyze_binary](analyze_binary.md)
- [analyze_crash](analyze_crash.md)
- [analyze_memory](analyze_memory.md)

