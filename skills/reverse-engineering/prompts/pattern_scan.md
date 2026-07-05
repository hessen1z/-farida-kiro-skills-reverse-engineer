# Prompt: Pattern Scan

## Objective

Create, validate, and deploy a byte-pattern signature for a target function or data structure. The pattern must be version-stable, unique within the binary, and robust against minor updates.

---

## Methodology

### Step 1 — Obtain Bytes at Target

In IDA Pro: place cursor at target address, press `H` to see hex bytes. Or use the IDA Python API:
```python
import idc
start = here()
data = idc.get_bytes(start, 32)
hex_bytes = ' '.join(f'{b:02X}' for b in data)
```

In x64dbg: right-click instruction → Binary → Copy bytes.

Typical function start (16 bytes):
```
48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 48
```

### Step 2 — Identify Bytes That Must Be Wildcarded

Rules for wildcards:
- `E8 XX XX XX XX` (CALL rel32) — wildcard 4 bytes: `E8 ?? ?? ?? ??`
- `E9 XX XX XX XX` (JMP rel32) — wildcard 4 bytes: `E9 ?? ?? ?? ??`
- `EB XX` (JMP rel8) — wildcard 1 byte: `EB ??`
- `48 8D 05 XX XX XX XX` (LEA rax, [rip+disp]) — wildcard 4: `48 8D 05 ?? ?? ?? ??`
- `48 8B 05 XX XX XX XX` (MOV rax, [rip+disp]) — wildcard 4: `48 8B 05 ?? ?? ?? ??`
- `FF 15 XX XX XX XX` (CALL [rip+disp], IAT call) — wildcard 4: `FF 15 ?? ?? ?? ??`
- `48 B8 XX XX XX XX XX XX XX XX` (MOV rax, imm64) — wildcard 8: `48 B8 ?? ?? ?? ?? ?? ?? ?? ??`
- Conditional JMPs (7X XX) if near: `7? ??`

**Keep as literal:** opcode bytes, ModRM bytes, register operands, small immediate constants that are part of the algorithm (not addresses).

### Step 3 — Build the Initial Pattern

Start from the first byte of the function. Build a pattern of at least 16 bytes (24+ preferred):

```
; Original function start:
48 89 5C 24 08     ; mov [rsp+8], rbx      — literal: stable
48 89 74 24 10     ; mov [rsp+10h], rsi    — literal: stable
57                 ; push rdi              — literal: stable
48 83 EC 20        ; sub rsp, 20h          — literal: stable
48 8B F9           ; mov rdi, rcx          — literal: stable (save this)
E8 A3 1F 00 00     ; call +0x1FA3          — WILDCARD: E8 ?? ?? ?? ??
48 8B D8           ; mov rbx, rax          — literal: stable

Pattern: "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 48 8B F9 E8 ?? ?? ?? ?? 48 8B D8"
```

### Step 4 — Verify Pattern Uniqueness

Scan the full module for all matches:

```cpp
auto matches = PatternScanAll("48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 48 8B F9 E8 ?? ?? ?? ?? 48 8B D8");
if (matches.size() != 1) {
    // Pattern is not unique — extend it
}
```

**If multiple matches:**
1. Extend the pattern by adding more bytes from the function body.
2. Or use a pattern from a more unique region (a distinctive constant, a rare opcode sequence).
3. Repeat until exactly 1 match.

### Step 5 — Test Across Versions

Compare the target function bytes in multiple binary versions:

| Version | Bytes at target RVA | Pattern matches? |
|---------|---------------------|-----------------|
| 1.0.0   | 48 89 5C 24 ...     | ✓ 1 match       |
| 1.0.1   | 48 89 5C 24 ...     | ✓ 1 match       |
| 1.1.0   | 48 89 5C 24 ...     | ✓ 1 match       |
| 1.2.0   | ? (different build) | ✗ 0 matches → revise |

If a version breaks:
1. Diff bytes at the old and new function addresses.
2. Find which bytes changed (usually relative operands or compiler-reordered code).
3. Add wildcards for the changed bytes.

### Step 6 — Handle Edge Cases

**Pattern at function boundary:**
- If the function is inlined, there is no unique standalone copy — pattern won't find it.
- Solution: pattern the inlined site itself, or pattern a unique caller that calls it exclusively.

**Function starts with a common prologue:**
- `48 89 5C 24 08 57 48 83 EC 20` is very common.
- Extend pattern deeper into the function body to a more unique sequence.

**Highly optimized function (leaf, no prologue):**
- The function body is the pattern — use the first unique instruction sequence.

**Pattern for data (vtable, global):**
- Data patterns use the actual data bytes, not instruction-level wildcards.
- Vtable pattern: 3+ consecutive pointers into .text, each 8 bytes.
- Global struct pattern: a unique combination of known field values.

### Step 7 — Deploy the Pattern

```cpp
// Production pattern usage:
static uintptr_t s_cachedAddr = 0;

uintptr_t GetTargetFunction() {
    if (s_cachedAddr) return s_cachedAddr;

    uintptr_t moduleBase = reinterpret_cast<uintptr_t>(GetModuleHandleW(nullptr));
    uintptr_t va = PatternScanModule(moduleBase,
        "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 "
        "48 8B F9 E8 ?? ?? ?? ?? 48 8B D8");

    if (!va) {
        // Pattern not found — binary updated or wrong module
        OutputDebugStringA("[Error] CNetworkManager::Send pattern not found\n");
        return 0;
    }

    s_cachedAddr = va;
    return va;
}
```

---

## Checklist

- [ ] Target function/data address confirmed in debugger
- [ ] Raw bytes captured (at least 32 bytes)
- [ ] All relative operand bytes wildcarded
- [ ] All absolute address bytes wildcarded
- [ ] Pattern length ≥ 16 bytes (24+ preferred)
- [ ] Uniqueness verified (exactly 1 match in target module)
- [ ] Pattern tested on at least 3 binary versions
- [ ] Pattern documented with: target name, version found, bytes, rationale for wildcards
- [ ] Production code caches the result after first scan
- [ ] Failure path implemented (pattern not found → log and return 0)

---

## Expected Output

```cpp
// Pattern: CNetworkManager::Send
// Found in: game.exe v1.23.456 (SHA-256: a1b2...)
// Uniqueness: 1 match verified
// Version stability: tested on v1.22, v1.23, v1.24 — all pass

static const char* PATTERN_NETWORK_SEND =
    "48 89 5C 24 08 "   // mov [rsp+8], rbx
    "48 89 74 24 10 "   // mov [rsp+10h], rsi
    "57 "               // push rdi
    "48 83 EC 20 "      // sub rsp, 20h
    "48 8B F9 "         // mov rdi, rcx (save this)
    "E8 ?? ?? ?? ?? "   // call [relative] — wildcarded
    "48 8B D8";         // mov rbx, rax
```

---

## Validation

1. Run `PatternScanAll` on current binary — confirm exactly 1 match.
2. Verify the match address equals the known function VA in the debugger.
3. Set a breakpoint at the pattern result VA — confirm it fires on expected calls.
4. Rerun on at least one other version — confirm still 1 match.
5. Compute RVA from match: `rva = match_va - module_base`. Verify against IDA's RVA for the function.

---

## Common Mistakes

- Not wildcarding `FF 15` IAT calls — the displacement changes across every build.
- Stopping the pattern too early (< 12 bytes) — common prologues match everywhere.
- Not testing uniqueness — a pattern with 3 matches hooks the wrong function 2/3 of the time.
- Including loop condition bytes — loop structure can change with optimization settings.
- Wildcarding too aggressively — a pattern of all `??` matches everything.
- Not caching the result — scanning the module on every frame is massively wasteful.

## Related Material

### Knowledge
- [common-instructions](../knowledge/assembly/common-instructions.md)
- [compiler-patterns](../knowledge/assembly/compiler-patterns.md)
- [exceptions](../knowledge/cpp/exceptions.md)

### Prompts
- [analyze_binary](analyze_binary.md)
- [analyze_crash](analyze_crash.md)
- [analyze_memory](analyze_memory.md)

