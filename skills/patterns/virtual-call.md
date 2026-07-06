---
title: Virtual Call Pattern
skill: patterns
category: 
difficulty: intermediate
tags: [pe, windows, asm, x64]
updated: 2026-07-05
---
# Virtual Call Pattern

Virtual calls use vtables to dispatch virtual functions at runtime. Recognizing virtual call idioms allows mapping of vtable slots to method names and reconstructing class behavior.

## Canonical Pattern

```asm
mov rax, [rcx]           ; load vtable pointer
call qword ptr [rax+8*slot]
```

On x86 the equivalent uses `eax` and `dword ptr [eax+4*slot]`.

## Interpretation

- `rcx` is typically `this` (object base). The first qword at object base is the vtable pointer.
- `slot` index identifies which virtual method is being invoked — divide offset by pointer size (8 on x64, 4 on x86).

## Variations and Complexities

- Multiple inheritance: object may hold multiple vtable pointers at different offsets; compiler-generated thunks adjust `this`.
- Inlined virtual calls: optimizer may eliminate indirection in rare cases; verify with cross-references.

## Analysis Workflow

1. Identify repeated indirect call locations across codebase that use the same slot offset. These likely map to a vtable slot.
2. Collect candidate functions and label them consistently in the disassembly.
3. Locate vtable object(s) in data section and apply names to slots.

## Tools and Tips

- Use RTTI `_RTTICompleteObjectLocator` when present to map vtable to class names.
- IDA/Ghidra: define vtable as an array of pointers and apply function names to slots.

## Verification Checklist

- [ ] Mapped vtable slots to consistent function addresses across binaries.
- [ ] Cross-validated vtable assignments using RTTI or runtime inspection.

## Related Knowledge

- `knowledge/windows/cpp/vtables.md`

