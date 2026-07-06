---
title: Prompt: Recover Offsets
skill: reverse-engineering
category: prompts
difficulty: intermediate
tags: [pe, asm, x64, debug]
updated: 2026-07-05
---
# Prompt: Recover Offsets

## Objective

Systematically locate and document all stable memory offsets for a target binary: struct field offsets, pointer chain paths, global variable RVAs, vtable slot indices, and function RVAs. Produce a version-tagged offset table suitable for production use.

---

## Methodology

### Step 1 — Identify Target Data

Define what offsets you need before starting. Categories:

1. **Struct field offsets**: `player->health`, `entity->position.x`, etc.
2. **Global/static variable RVAs**: singleton pointers, global arrays, config blocks.
3. **Pointer chain paths**: multi-level dereference sequences to reach a target value.
4. **Vtable slot indices**: which slot number corresponds to which virtual method.
5. **Function RVAs**: important functions addressable from module base.

### Step 2 — Find Struct Field Offsets

For each field of interest:

**Method A — Constructor analysis:**
```asm
; In MyClass constructor:
mov dword ptr [rcx+0x18], 100    ; field at offset 0x18 = int, initialized to 100
movss [rcx+0x1C], xmm0            ; field at offset 0x1C = float
mov qword ptr [rcx+0x20], rax     ; field at offset 0x20 = pointer (64-bit)
```
Record offset, width (byte/dword/qword/float), and initial value.

**Method B — Dynamic observation:**
1. Break at a known method that reads the target field.
2. Note `RCX` = object pointer.
3. Read `[RCX + N]` for each interesting offset.
4. Observe value in dump panel.

**Method C — XREF from known value:**
1. Search memory for a known value (health = 100.0f = 0x42C80000).
2. Note the address. Subtract the object base pointer to get the offset.

### Step 3 — Find Global Variable RVAs

**Method A — Import XREF:**
1. Find a function that accesses the global (e.g., GetPlayerManager returns a singleton).
2. In disassembly: `mov rax, [rip+disp32]` — disp32 is relative to next instruction's RIP.
3. Compute: `global_va = rip_after_instruction + disp32`.
4. Compute: `global_rva = global_va - module_base`.

**Method B — String XREF:**
1. Find an initialization string near the global: `"Initializing PlayerManager..."`.
2. Follow the function that prints that string — it likely writes to the global pointer.
3. Find `mov [absolute_address], rax` or `mov [rip+disp], rax`.

**Method C — PEB module walk:**
1. At debugger break, inspect .data section for 8-byte NULL values that get written to once.
2. A global pointer is zero at startup and written once during init.

### Step 4 — Build Pointer Chains

A pointer chain is: `static_rva → [+off0] → [+off1] → ... → target`

**Discovery process:**
1. Find the target value in memory (e.g., player health float).
2. Search memory for the address containing the target — find what points to it (level N-1).
3. Repeat: find what points to level N-1 (level N-2).
4. Continue until you reach a static address (.data or .rdata section).
5. Verify the static address is a fixed RVA from module base.

**Verification across restarts:**
1. Record the full chain: `[module+0x1A2B4C8] → +0x10 → +0x78 → float`.
2. Restart the process.
3. Recompute: `module_base` changes but `0x1A2B4C8` (RVA) stays fixed.
4. Verify each intermediate pointer is non-NULL and the final value is correct.

**Stability testing:**
Run the chain check 10 times across fresh launches and game state changes. If any intermediate pointer becomes invalid → the chain is not fully static — find a more stable root.

### Step 5 — Find Vtable Slot Indices

For each virtual function you want to call or hook:

1. Find the function address (via RTTI → vtable enumeration or pattern scan).
2. Scan the vtable from slot 0: find the index where the pointer equals the function address.
3. Verify: `vtable[index] == function_va`.

Alternatively — in debugger:
1. Break inside the virtual function.
2. Look at the call stack — note `call [rax+N]` in the caller.
3. `N / 8 = slot_index`.

### Step 6 — Find Function RVAs

**Method A — Pattern scan:**
1. Create a pattern from the function's unique byte sequence.
2. Scan the module and get the VA.
3. Compute: `rva = va - module_base`.

**Method B — Export by name:**
1. If exported: `GetProcAddress(module, "FunctionName")` → VA.
2. Compute: `rva = va - module_base`.

**Method C — RTTI + vtable:**
1. Find vtable via RTTI.
2. vtable[slot] = VA.
3. Compute: `rva = va - module_base`.

### Step 7 — Document All Offsets

Use a structured table with version tracking:

```cpp
// ============================================
// Target: game.exe v1.23.456
// SHA-256: a1b2c3d4...
// Build: 2025-03-15
// Module base: 0x140000000 (default, ASLR applied at runtime)
// ============================================

namespace Offsets_v1_23_456 {

    // Global pointers (RVA from module base)
    constexpr uintptr_t g_playerManager  = 0x01A2B4C8;
    constexpr uintptr_t g_worldManager   = 0x01A2B4D0;
    constexpr uintptr_t g_entityList     = 0x01A2B500;

    // Struct offsets — CPlayer
    namespace CPlayer {
        constexpr uintptr_t health       = 0x0064;
        constexpr uintptr_t maxHealth    = 0x0068;
        constexpr uintptr_t position_x   = 0x006C;
        constexpr uintptr_t position_y   = 0x0070;
        constexpr uintptr_t position_z   = 0x0074;
        constexpr uintptr_t velocity     = 0x0080;  // vec3 = 3 floats
        constexpr uintptr_t teamId       = 0x00A4;
        constexpr uintptr_t isAlive      = 0x00A8;  // bool
    }

    // Pointer chains
    // [g_playerManager] → +0x10 → +0x68 → float (localplayer.health)
    namespace Chains {
        constexpr uintptr_t localPlayerHealth_l0  = g_playerManager;
        constexpr uintptr_t localPlayerHealth_l1  = 0x10;
        constexpr uintptr_t localPlayerHealth_l2  = CPlayer::health;
    }

    // Function RVAs
    namespace Functions {
        constexpr uintptr_t CPlayer_TakeDamage    = 0x00123456;
        constexpr uintptr_t CWorld_SpawnEntity    = 0x00234567;
    }

    // Vtable slot indices — CPlayer
    namespace CPlayer_Slots {
        constexpr int dtor_scalar    = 0;
        constexpr int dtor_vector    = 1;
        constexpr int Update         = 2;
        constexpr int TakeDamage     = 3;
        constexpr int GetHealth      = 4;
        constexpr int Die            = 5;
    }
}
```

---

## Checklist

- [ ] Binary version and SHA-256 recorded
- [ ] All target struct fields located with offset, type, and width
- [ ] All global variable RVAs verified from at least 2 launches
- [ ] All pointer chains verified across at least 3 fresh process starts
- [ ] All pointer chain intermediate pointers validated (non-null, readable)
- [ ] All vtable slot indices verified in debugger
- [ ] All function RVAs tested (pattern scan matched, VA confirmed in debugger)
- [ ] Version-tagged offset header file created
- [ ] All offsets annotated with evidence source

---

## Expected Output

A version-tagged C++ header file as shown in Step 7, plus a markdown table:

```markdown
| Symbol                    | Type       | Offset/RVA   | Notes                           |
|---------------------------|------------|--------------|---------------------------------|
| g_playerManager           | Global*    | 0x01A2B4C8   | Singleton, written at startup   |
| CPlayer::health           | Field      | +0x0064      | float, range 0.0–1000.0         |
| CPlayer::isAlive          | Field      | +0x00A8      | bool, byte-width                |
| localPlayerHealth chain   | Chain      | +0x10, +0x64 | 2-level from g_playerManager    |
| CPlayer::TakeDamage       | Func RVA   | 0x00123456   | Pattern: 48 89 5C 24 08 ...     |
| CPlayer_Slots::TakeDamage | Slot index | 3            | Verified in debugger            |
```

---

## Validation

1. At runtime, resolve each global RVA: `module_base + rva`. Verify in debugger it points to the expected object.
2. Walk each pointer chain step by step in the debugger. Verify each intermediate value is non-null.
3. Call each function RVA directly: `((void(*)(void*))(module_base + rva))(obj)`. Verify no crash.
4. Hook each vtable slot by index. Verify the hook fires on the expected calls.
5. After a binary update: re-verify every offset. Update the version-tagged table.

---

## Common Mistakes

- Using VAs instead of RVAs — breaks on every launch with ASLR.
- Assuming pointer chain is stable without testing across restarts — chains through dynamic objects break.
- Documenting offsets without a version tag — offsets from v1.0 are wrong for v1.1.
- Missing padding between fields — struct size calculation and adjacent offset access both break.
- Not verifying vtable slot in debugger — slot counts can shift if base class adds a new virtual method.

## Related Material

### Knowledge
- [common-instructions](../knowledge/assembly/common-instructions.md)
- [compiler-patterns](../knowledge/assembly/compiler-patterns.md)
- [exceptions](../knowledge/cpp/exceptions.md)

### Prompts
- [analyze_binary](analyze_binary.md)
- [analyze_crash](analyze_crash.md)
- [analyze_memory](analyze_memory.md)

