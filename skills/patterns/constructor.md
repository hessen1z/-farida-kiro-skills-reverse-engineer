---
title: Constructor Patterns
skill: patterns
category: 
difficulty: intermediate
tags: [pe, windows, asm, gui]
updated: 2026-07-05
---
# Constructor Patterns

## Goal
Identify constructor implementations in disassembly and distinguish them from simple initialization helpers or wrapper functions.

## Recognition
- A vtable write at object base such as `mov [rcx], offset vtable`.
- Immediate member initialization after the vtable write.
- Nearby calls into base-class constructors or member initializer helpers.
- A return of the `this` pointer in the standard register convention.

## Internal Mechanism
Constructors are usually a short sequence of object setup operations: initialize the vtable, assign fields, call base constructors, and perform optional validation before returning.

## Assembly Examples
```asm
mov [rcx], qword ptr offset vtable
mov dword ptr [rcx+0x18], 0
call BaseClass::BaseClass
ret
```

## Decompiled Examples
```cpp
Foo::Foo() {
    vptr = &Foo::vtable;
    field = 0;
    Base::Base();
}
```

## Compiler Variations
- MSVC commonly emits direct vtable writes and calls to base constructors.
- GCC/Clang may use different prologue/epilogue conventions but still perform the same logical initialization sequence.

## Common Mistakes
- Mislabeling a helper function that only initializes one field as a full constructor.
- Assuming every `call` near object setup is a base constructor without confirming the target.

## Reverse Engineering Tips
- Follow allocation sites and cross-references to the constructor to validate object lifetime.
- Rename the function based on the class name once the vtable and field usage are confirmed.

## Detection Heuristics
- Repeated initialization of object members at the start of a function.
- Presence of object base writes and immediate control flow into constructor helpers.

## Validation Checklist
- [ ] Vtable assignment observed at the beginning of the function.
- [ ] Member fields initialized immediately after the vtable write.
- [ ] Calls to base constructors or member initializers are present.

## Related Knowledge
- [virtual-call](virtual-call.md)
- [vtable reconstruction](../reverse-engineering/knowledge/windows/cpp/vtables.md)

## Related Recipes
- [Recover_Classes](../recipes/Recover_Classes.md)

## Related Playbooks
- [GameHacking](../playbooks/GameHacking.md)

## References
- Microsoft C++ ABI documentation
- IDA/Ghidra vtable analysis guidance
