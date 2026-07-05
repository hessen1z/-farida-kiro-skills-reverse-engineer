# Prompt: Analyze Crash

## Objective

Determine the root cause of a crash in a Windows native process. Identify the faulting instruction, the bad memory access, the call path leading to the fault, and the original code defect. Produce an actionable root cause report.

---

## Methodology

### Step 1 — Collect Crash Artifacts

Before analysis, gather:
- Minidump file (`.dmp`) or live process at crash state in debugger
- WER (Windows Error Reporting) logs in `%LOCALAPPDATA%\CrashDumps`
- Access violation exception code and faulting address
- Module name and RVA of faulting instruction
- Call stack at time of crash (full backtrace)

### Step 2 — Load and Initialize Crash Context

**In WinDbg:**
```
.opendump crash.dmp
.sympath srv*C:\Symbols*https://msdl.microsoft.com/download/symbols
.reload
!analyze -v       ; automated crash analysis
```

**Key WinDbg commands:**
```
k        ; call stack
kb       ; call stack with first 3 args
.exr -1  ; last exception record
.cxr     ; switch to crash context
r        ; registers at crash
u .      ; disassemble at crash instruction
dq rsp   ; stack contents
```

**In x64dbg:**
1. Run process to crash — exception dialog fires.
2. View → Call stack.
3. Note exception address, code, and all registers.

### Step 3 — Classify the Exception

| Exception Code  | Meaning                                      |
|-----------------|----------------------------------------------|
| 0xC0000005      | Access Violation (read/write to bad address) |
| 0xC0000034      | Object Not Found                             |
| 0xC0000096      | Privileged Instruction                       |
| 0xC000001D      | Illegal Instruction (bad opcode)             |
| 0xC0000094      | Integer divide by zero                       |
| 0xC00000FD      | Stack overflow                               |
| 0xC0000409      | Stack buffer security check (GS cookie)      |
| 0x80000003      | Breakpoint                                   |
| 0x80000004      | Single step                                  |

For 0xC0000005 (Access Violation), note:
- Read violation vs Write violation (parameter 0 = 0 for read, 1 for write)
- Faulting address (parameter 1) — the bad pointer value

### Step 4 — Analyze the Faulting Instruction

1. Disassemble at the exception address:
   ```
   u eip-20 ; disassemble instructions before crash point
   u eip    ; crash instruction
   u eip+20 ; instructions after
   ```

2. Identify the instruction type:
   - `mov rax, [rcx+N]` → null or invalid `rcx`
   - `call [rax+N]` → null or invalid vtable pointer
   - `mov [rax], value` → null or read-only target
   - `div rcx` → zero divisor in `rcx`

3. Note which register holds the bad value and its current content.

### Step 5 — Trace the Bad Pointer

For a null/invalid pointer crash:

1. Note the bad pointer register (e.g., `rcx = 0x0000000000000000`).
2. Look at the call stack — which function passed this value?
3. Go to the caller: which argument corresponds to the bad register?
4. Trace upward: which function generated this value and why is it null/invalid?

Common root causes:
- Return value not checked: function returned null and caller dereferenced it.
- Use-after-free: object was deleted but a dangling pointer still references it.
- Race condition: object is valid on one thread but deleted on another.
- Uninitialized pointer: field was never set in the constructor path.
- Off-by-one: pointer arithmetic produced an address past the end of an array.

### Step 6 — Walk the Full Call Stack

For each frame in the call stack:
1. Note function name (or address if stripped).
2. Note arguments at that frame.
3. Identify which frame introduced the invalid state.

```
Frame 0: CNetworkManager::Send + 0x3C      ← crash here
Frame 1: CConnectionHandler::Update + 0x18  ← called Send
Frame 2: CApplication::Tick + 0x44          ← called Update
Frame 3: CApplication::Run + 0x2C           ← main loop
Frame 4: WinMain + 0x1A
```

### Step 7 — Identify Root Cause Category

**Null pointer dereference:**
- Pointer is 0x0 or very small (< 0x10000).
- Cause: uninitialized field, failed allocation not checked, early return skipped init.

**Use-after-free (UAF):**
- Pointer is non-zero but access is invalid.
- Memory region was freed: VirtualQuery shows MEM_FREE or protection changed.
- The faulting address falls in a region that was previously MEM_COMMIT.
- MSVC Debug Heap fills freed memory with `0xDD` bytes — if you see `0xDD...` at the pointer, it is UAF.

**Stack overflow:**
- Exception 0xC00000FD.
- RSP is near the thread's stack limit.
- Call stack shows infinite or very deep recursion.

**Buffer overflow:**
- Access violation at `base_address + large_offset`.
- Array index out of bounds: check the index calculation and the array size.
- String operation past null terminator: `strlen` on non-terminated buffer.

**Corrupted vtable:**
- Crash at `call [rax+N]` where `rax` is a vtable pointer.
- `rax` value is non-canonical or points to non-executable memory.
- Cause: buffer overflow overwrote the object's vptr, or the object was freed.

### Step 8 — Document the Root Cause

Produce a structured crash report:

```markdown
## Crash Report

**Exception:** 0xC0000005 ACCESS_VIOLATION (read at 0x0000000000000078)
**Module:** game.exe
**RVA:** 0x0011F3A4
**Function:** CNetworkManager::Send + 0x3C

**Root Cause:** Null pointer dereference.
The `m_pConnection` field (offset 0x10 in CNetworkManager) is NULL.
The connection object was never created because the `Connect()` call failed silently
and the caller did not check the return value.

**Call Path:**
  CApplication::Tick → CConnectionHandler::Update → CNetworkManager::Send
  (CNetworkManager::m_pConnection accessed at offset 0x78 without null check)

**Fix:** Add null check for `m_pConnection` in `CNetworkManager::Send` before
any dereference. Alternatively, ensure `Connect()` failure is propagated
to the caller and `Update()` is not called on a disconnected manager.

**Evidence:**
- RSP at crash: 0x... (frame restored)
- RCX at crash: 0x14C3D2000 (CNetworkManager object, valid)
- RAX at crash: 0x0 (m_pConnection = NULL)
- Faulting address: 0x78 (NULL + 0x78 = offset 0x78 in null object)
```

---

## Checklist

- [ ] Exception code identified and classified
- [ ] Faulting instruction disassembled
- [ ] Bad register value noted with its contents
- [ ] Access type noted (read vs write vs execute)
- [ ] Full call stack recorded with frame arguments
- [ ] Root cause category identified (null, UAF, overflow, vtable corruption)
- [ ] Code path leading to bad state traced
- [ ] Root cause statement written
- [ ] Fix proposed with rationale
- [ ] Evidence attached (register dump, memory state)

---

## Expected Output

```
== Crash Analysis ==
Exception:   0xC0000005 (Access Violation — Read)
Address:     0x0000000000000078 (near-NULL)
Module RVA:  0x0011F3A4 in game.exe

Root Cause:  NULL pointer dereference on m_pConnection (+0x10 in CNetworkManager).
             Connect() returned false (network unavailable) but caller ignored return value.

Fix:         In CNetworkManager::Send(), add: if (!m_pConnection) return E_NOT_CONNECTED;
             In callers, check Connect() return value and handle failure.
```

---

## Validation

1. Reproduce the crash deliberately by triggering the same code path.
2. Apply the proposed fix.
3. Trigger the same code path again — verify no crash.
4. Test edge cases: what if `m_pConnection` becomes null mid-operation (race condition)?
5. Check all other call sites for the same missing null check.

---

## Common Mistakes

- Reading only the top frame — the bug is usually in a caller, not the crash site itself.
- Assuming the faulting address is meaningful — address 0x78 just means `NULL + 0x78 = struct offset 0x78`.
- Not distinguishing UAF from uninitialized pointer — the fix is completely different.
- Missing the case where a deleted object's memory was reallocated — UAF can produce non-NULL bad pointers.
- Ignoring exception code 0xC0000409 (GS cookie) — this indicates stack corruption, not a simple dereference.

## Related Material

### Knowledge
- [common-instructions](../knowledge/assembly/common-instructions.md)
- [compiler-patterns](../knowledge/assembly/compiler-patterns.md)
- [exceptions](../knowledge/cpp/exceptions.md)

### Prompts
- [analyze_binary](analyze_binary.md)
- [analyze_memory](analyze_memory.md)
- [build_reclass](build_reclass.md)

