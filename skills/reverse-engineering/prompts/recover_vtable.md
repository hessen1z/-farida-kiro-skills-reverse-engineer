---
title: Prompt: Recover Vtable
skill: reverse-engineering
category: prompts
difficulty: intermediate
tags: [pe, asm, x64, gui, debug, elf]
updated: 2026-07-05
---
# Prompt: Recover Vtable

## Objective

Locate, validate, and fully document all vtables in an MSVC binary. For each vtable: identify the owning class, enumerate all virtual function slots with names and signatures, detect thunks, and produce a complete vtable definition for IDA structs and ReClass.

---

## Methodology

### Step 1 — Find All Vtable Candidates in .rdata

A vtable in MSVC x64 has this structure:
```
[vtable - 0x08]  →  _RTTICompleteObjectLocator*  (COL, in .rdata)
[vtable + 0x00]  →  VirtualFunc0*                (in .text)
[vtable + 0x08]  →  VirtualFunc1*                (in .text)
...
```

Scan .rdata 8 bytes at a time:
1. Read candidate as potential vtable[0].
2. Value must point into .text (executable, MEM_IMAGE).
3. Read candidate[-1] (8 bytes before): must be a valid COL (signature=1, pSelf validates).
4. If both pass → this is a vtable.

### Step 2 — Validate Each Vtable

For each candidate vtable_va:
```
COL_va = *(vtable_va - 8)
COL.signature == 1                    # x64
image_base + COL.pSelf == COL_va      # self-referential validation
```

Only proceed with vtables that pass both checks.

### Step 3 — Enumerate All Slots

Starting at vtable[0], read 8-byte values:
- Each value must point into an executable region.
- Stop at first NULL or non-executable pointer.
- Special case: `__purecall` is valid and executable — do not stop there.

Record:
```
vtable @ 0x14001A2000  (CNetworkManager)
  slot  0: 0x140010C80  CNetworkManager::~CNetworkManager (scalar deleting dtor)
  slot  1: 0x140010D40  CNetworkManager::~CNetworkManager (vector deleting dtor)
  slot  2: 0x140011000  CNetworkManager::Connect
  slot  3: 0x140011200  CNetworkManager::Disconnect
  slot  4: 0x140011400  CNetworkManager::Send
  slot  5: 0x140011600  CNetworkManager::Receive
  slot  6: 0x140011800  CNetworkManager::GetState
  ...
```

### Step 4 — Identify Thunks

A thunk is a small stub that adjusts `this` before jumping to the real implementation:

```asm
; Secondary vtable thunk (multiple inheritance)
sub  rcx, 0x10        ; adjust this from derived to base subobject
jmp  CNetworkManager::Send_real
```

Detection: vtable slot points to a function that is <= 10 bytes and ends with `jmp` to another function in the primary vtable.

Mark thunks with their adjustment value and real target:
```
slot 0 (thunk): sub rcx,0x10 → CConnectionHandler::Update
```

### Step 5 — Identify Destructor Slots

MSVC always places destructors first:
- Slot 0: Scalar deleting destructor (`delete obj;`)
- Slot 1: Vector deleting destructor (`delete[] obj;`)

Both call the actual destructor body and then call `operator delete`. The real destructor body can be found by following the call inside slot 0's code.

### Step 6 — Identify Inherited vs Overridden vs New Slots

For a derived class vtable:
1. Compare slot addresses against the base class vtable.
2. Same address = inherited (not overridden).
3. Different address = overridden in derived class.
4. New slot (index > base slot count) = new virtual function added in derived class.

```
CBase vtable (5 slots):
  slot 0: dtor_scalar
  slot 1: dtor_vector
  slot 2: CBase::Init
  slot 3: CBase::Update
  slot 4: CBase::Shutdown

CDerived vtable (7 slots):
  slot 0: CDerived::~CDerived (scalar)   [OVERRIDE]
  slot 1: CDerived::~CDerived (vector)   [OVERRIDE]
  slot 2: CBase::Init                    [INHERITED — same address]
  slot 3: CDerived::Update               [OVERRIDE]
  slot 4: CBase::Shutdown                [INHERITED]
  slot 5: CDerived::NewMethod            [NEW]
  slot 6: CDerived::AnotherMethod        [NEW]
```

### Step 7 — Name Each Slot

Evidence for naming virtual functions:

| Evidence Type                             | Example Name             |
|-------------------------------------------|--------------------------|
| Called from outside with a meaningful context | `Update`, `Draw`, `Init` |
| Function body calls specific Win32 API    | `Connect`, `ReadFile`    |
| String reference near function body       | `"Failed to send data"` → `Send` |
| RTTI — base class has same slot named     | Inherit base class name  |
| Return value compared to 0 in `IsX` pattern | `IsConnected`, `IsReady` |

### Step 8 — Document Multiple Inheritance Vtables

For classes with multiple inheritance, each base class with virtual functions gets its own vtable. Name them clearly:

```
CConnectionHandler primary vtable     @ 0x14001A2280  (for CObject base)
CConnectionHandler secondary vtable   @ 0x14001A22C0  (for IDisposable base)
```

The secondary vtable's slots contain thunks. The offset value in the COL indicates which subobject this vtable belongs to.

---

## Checklist

- [ ] All vtable candidates in .rdata found and validated
- [ ] COL validation passed (signature + pSelf) for all vtables
- [ ] Slot count determined for every vtable
- [ ] Destructor slots (scalar + vector) identified
- [ ] Thunks identified and documented with adjustment value and real target
- [ ] Inherited vs overridden vs new slots distinguished
- [ ] Every slot named with evidence
- [ ] Multiple inheritance vtables grouped under their owning class
- [ ] Abstract class vtables marked (contain __purecall slots)
- [ ] IDA struct or enum created for vtable slot indices

---

## Expected Output

```cpp
// CNetworkManager vtable
// Address: 0x14001A2000
// Class: CNetworkManager : CObject, INetworkInterface
// Slots: 12

enum CNetworkManager_VtableSlots {
    CNetworkManager_dtor_scalar    = 0,
    CNetworkManager_dtor_vector    = 1,
    CNetworkManager_Connect        = 2,   // override of INetworkInterface::Connect
    CNetworkManager_Disconnect     = 3,   // override of INetworkInterface::Disconnect
    CNetworkManager_Send           = 4,   // override of INetworkInterface::Send
    CNetworkManager_Receive        = 5,   // override of INetworkInterface::Receive
    CNetworkManager_GetState       = 6,   // new in CNetworkManager
    CNetworkManager_SetTimeout     = 7,   // new in CNetworkManager
    CNetworkManager_GetLastError   = 8,   // new in CNetworkManager
    CNetworkManager_OnConnected    = 9,   // new in CNetworkManager
    CNetworkManager_OnDisconnected = 10,  // new in CNetworkManager
    CNetworkManager_OnDataReceived = 11,  // new in CNetworkManager
};

// Secondary vtable (for INetworkInterface subobject)
// Address: 0x14001A2080
// All slots are thunks: sub rcx, 0x08 → primary vtable method
```

---

## Validation

1. In debugger: break at a virtual call `call [rax+N*8]`. Read `rax` — it must equal the vtable address you documented.
2. Verify slot 0 is the destructor: read the function body — it should have `delete this` pattern.
3. For each thunk: trace the JMP target — it must land in the primary vtable's function body.
4. Verify inherited slots: compare function pointer at that slot against the base class vtable — must be identical.
5. Apply vtable struct type in IDA to a known object pointer — verify all member calls resolve cleanly.

---

## Common Mistakes

- Stopping slot enumeration at a NULL that is actually a thunk jump target — read all slots until truly non-executable.
- Confusing secondary vtable thunks for regular functions — check for the `sub rcx, N` + `jmp` pattern.
- Forgetting that MSVC always puts two destructor slots first (scalar + vector) — off-by-two on all subsequent slots.
- Treating all functions in a vtable as user-defined — RTTI glue functions may appear as slots.
- Not grouping multiple inheritance vtables — documenting them independently loses context.

## Related Material

### Knowledge
- [common-instructions](../knowledge/assembly/common-instructions.md)
- [compiler-patterns](../knowledge/assembly/compiler-patterns.md)
- [exceptions](../knowledge/cpp/exceptions.md)

### Prompts
- [analyze_binary](analyze_binary.md)
- [analyze_crash](analyze_crash.md)
- [analyze_memory](analyze_memory.md)

