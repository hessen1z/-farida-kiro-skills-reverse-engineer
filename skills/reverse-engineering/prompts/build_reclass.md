# Prompt: Build ReClass.NET Layout

## Objective
Build a complete ReClass.NET class node tree from a recovered binary. Every field must have the correct type, offset, name, and size. The result must display meaningful live values when attached to the process.

## Methodology

### Step 1 — Prepare Prerequisites
Before opening ReClass.NET:
1. Complete struct recovery for all target classes (see `recover_class.md`).
2. Know module base address (find with Process Hacker or GetModuleHandle).
3. Know pointer chain to each target object's address.
4. Have IDA open alongside ReClass for cross-referencing.

### Step 2 — Create the Root Node
In ReClass.NET:
1. New class → name it `CPlayerManager` (matching recovered IDA name).
2. Set the address: `<module_base> + <g_playerManager_rva>` or use a pointer chain.
3. For a pointer chain: add a pointer node at offset 0, then a class node as its child.

### Step 3 — Add Fields In Order
Add fields in ascending offset order. For each field:

| IDA type          | ReClass node type    | Notes                          |
|-------------------|----------------------|-------------------------------|
| `QWORD` pointer   | Pointer (8 bytes)    | Set child class if known       |
| `DWORD` int       | Int32                |                               |
| `float`           | Float                |                               |
| `bool` (byte)     | Bool / Int8          |                               |
| `HANDLE` (qword)  | Hex64                | Show as hex                   |
| `char[N]` array   | UTF8Text or Bytes    |                               |
| `wchar_t[N]`      | UTF16Text            |                               |
| embedded object   | Class node (inline)  | Expand the embedded struct     |
| `void*` unknown   | Pointer → Unknown    | Placeholder                   |
| padding bytes     | Padding (N bytes)    |                               |

### Step 4 — Handle Pointer-to-Class Fields
When a field is a pointer to another class:
1. Add a Pointer node at that offset.
2. Create (or reference) a child class node.
3. Name the pointer field `m_pChildClass`.
4. In ReClass, right-click → "Change node type" → Class → select the child class.

### Step 5 — Verify Live Values
Attach ReClass to the process:
1. File → Attach to Process → select target.
2. Navigate to the class node.
3. Watch live field values update in the right panel.
4. For each field verify:
   - Integer fields: value within expected range.
   - Float fields: reasonable float value.
   - Pointer fields: non-null, points to recognizable memory.
   - String fields: readable text.

Unexpected values (0xCDCDCDCD = uninitialized MSVC debug, 0xDDDDDDDD = freed) indicate wrong offset or wrong type.

### Step 6 — Adjust Padding
Where ReClass shows misaligned values:
1. Insert padding nodes between fields.
2. Padding = `next_field_offset - (previous_field_offset + previous_field_size)`.
3. Common padding: 1–7 bytes for alignment to 4 or 8 byte boundaries.

### Step 7 — Export for IDA
ReClass can export as C++ header:
1. File → Generate Code → C++ header.
2. Clean up: remove ReClass-specific attributes, add `#pragma pack` if needed.
3. Import into IDA: Local Types → Insert → paste struct definition.

## Checklist
- [ ] All classes created as ReClass nodes
- [ ] All fields typed correctly (no `Unknown` nodes in final layout)
- [ ] All pointer fields linked to child class nodes
- [ ] Live value verification completed for all fields
- [ ] Padding nodes added for all alignment gaps
- [ ] Total node size matches `operator new` argument from IDA
- [ ] C++ header exported and imported into IDA

## Expected Output
```
CPlayerManager (size: 0x68)
  +0x00  Pointer    vptr          → vtable_CPlayerManager
  +0x08  Int32      m_state
  +0x0C  Int32      m_errorCode
  +0x10  Pointer    m_pConnection → CConnection
  +0x18  Float      m_timeout
  +0x1C  Bool       m_isConnected
  +0x1D  Padding    [3 bytes]
  +0x20  Hex64      m_socket
  +0x28  UInt32     m_sendBufferSize
  +0x2C  UInt32     m_recvBufferSize
  +0x30  Pointer    m_pSendBuffer → Uint8
  +0x38  Pointer    m_pRecvBuffer → Uint8
  +0x40  UInt32     m_sequenceNum
  +0x44  UInt32     m_remotePort
  +0x48  UTF8Text   m_remoteHost  [32 bytes]
```

## Validation
1. Total size = 0x68 = 104 bytes. Last field ends at 0x48 + 32 = 0x68. ✓
2. Attach to process. m_state = 2 (connected state). m_isConnected = true. ✓
3. m_pConnection → follow pointer → CConnection node shows valid child object. ✓
4. m_socket = valid SOCKET value (non-INVALID_SOCKET). ✓

## Common Mistakes
- Missing padding — next field shows wrong value because offset is shifted.
- Using wrong pointer width (Int32 for a 64-bit pointer on x64).
- Attaching before the object is constructed — shows all zeros (uninitialized).
- Not following pointer fields — pointers show an address, not the pointed-to data.
- Setting wrong class size — ReClass reads past the object end into adjacent heap metadata.

## Related Material

### Knowledge
- [common-instructions](../knowledge/assembly/common-instructions.md)
- [compiler-patterns](../knowledge/assembly/compiler-patterns.md)
- [exceptions](../knowledge/cpp/exceptions.md)

### Prompts
- [analyze_binary](analyze_binary.md)
- [analyze_crash](analyze_crash.md)
- [analyze_memory](analyze_memory.md)
## Practical Guidance

- Start from the core objective and define the expected outcome before applying the workflow.
- Use the related examples, recipes, and playbooks as the first implementation reference.
- Keep the advice grounded in the surrounding skill context and verify the result against the available evidence.
- Favor practical, maintainable steps over abstract theory when this document is used in real work.
## Verification Checklist

- Confirm that the main objective is clear and the workflow is actionable.
- Ensure the document points to the most relevant examples, recipes, or playbooks.
- Validate that the terminology is consistent with the rest of the skill.
- Check that the practical guidance is specific enough to be used without further interpretation.
