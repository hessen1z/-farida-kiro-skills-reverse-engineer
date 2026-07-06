---
title: Pure Virtual / __purecall Pattern
skill: patterns
category: 
difficulty: intermediate
tags: [pe, windows, asm, gui]
updated: 2026-07-05
---
# Pure Virtual / __purecall Pattern

## Overview
This pattern appears when a class hierarchy uses a pure virtual function and the compiler emits a stub that will crash or terminate if invoked unexpectedly. In practice, analysts use it as a strong signal that a class is abstract and that an invalid call path exists.

## Recognition Signs
- A call target named `__purecall` on MSVC builds.
- A vtable slot that resolves to the compiler-generated pure virtual stub.
- A decompiled or source-level declaration such as `virtual void Foo() = 0;`.
- A call chain that reaches a stub after a vtable dispatch.

## Typical Assembly Form
A common MSVC form looks like this:
```asm
mov rax, [rcx]
call qword ptr [rax+0x10] ; vtable slot resolves to __purecall
```

## Why the Compiler Generates It
Abstract base classes require a stub implementation so that a broken call path can fail deterministically. The stub is not a normal runtime entry point; it is a guardrail for invalid usage.

## Variations Across Compilers
- MSVC: `__purecall`
- GCC/Clang: `__cxa_pure_virtual`

## Practical Guidance
- Treat the call as a design or logic failure unless you have evidence that the code intentionally dispatches through the stub for a controlled path.
- Rename the vtable slot or function to something like `pure_virtual_stub` during reconstruction to preserve the architectural meaning.
- Search for the compiler-generated symbol name in imports, strings, or the binary image to find additional abstract methods.

## Reverse Engineering Notes
- Inspect the owning class hierarchy and identify which abstract method is being invoked.
- Correlate the stub with RTTI and vtable layout to reconstruct the class hierarchy accurately.
- Use this pattern to validate that a class should be treated as abstract rather than as a concrete implementation.

## Common Mistakes
- Treating a pure-call stub as a legitimate API or helper routine.
- Missing that the issue may be caused by an object being used through the wrong interface or after construction failure.

## Validation Checklist
- Confirm that the target is a pure-virtual implementation stub rather than a normal function.
- Verify that the vtable slot or call target matches the expected abstract method.
- Record the finding as an architectural signal, not as ordinary program logic.

## Related Patterns
- [virtual-call](virtual-call.md)

## Related Knowledge
- [vtables](../reverse-engineering/knowledge/windows/cpp/vtables.md)
- [rtti](../reverse-engineering/knowledge/windows/cpp/rtti.md)