---
title: Factory Patterns
skill: patterns
category: 
difficulty: intermediate
tags: [pe, windows, asm]
updated: 2026-07-05
---
# Factory Patterns

## Goal
Recognize factory-style functions that encapsulate object allocation, initialization, and lifecycle management.

## Recognition
- Allocation APIs followed by constructor or initialization calls.
- A single entry point that returns a newly allocated object handle or pointer.
- Cleanup or error-handling branches around allocation and initialization.

## Internal Mechanism
Factories centralize creation logic so callers receive an initialized object without needing to know how memory is obtained or how the object is wired up.

## Assembly Examples
```asm
call operator_new
mov rcx, rax
call MyClass::MyClass
ret
```

## Decompiled Examples
```cpp
MyClass* CreateMyClass() {
    auto* obj = new MyClass();
    return obj;
}
```

## Compiler Variations
- MSVC commonly uses `operator new` or heap allocation helpers.
- GCC/Clang may route through allocator wrappers or internal runtime helpers.

## Common Mistakes
- Confusing a factory with a plain constructor because both return an object pointer.
- Missing the allocation path when the factory wraps a platform allocator or custom pool manager.

## Reverse Engineering Tips
- Break on allocation routines and the returned object initializer to confirm the full flow.
- Track the factory return value to understand ownership and object lifetime.

## Detection Heuristics
- A function that allocates memory and then calls an initialization routine before returning.
- Patterns that build manager registries or object pools in one place.

## Validation Checklist
- [ ] Allocation and initialization are observed in sequence.
- [ ] The returned pointer is validated by runtime or static evidence.

## Related Knowledge
- [constructor](constructor.md)
- [singleton](singleton.md)

## Related Recipes
- [Recover_Classes](../recipes/Recover_Classes.md)

## Related Playbooks
- [GameHacking](../playbooks/GameHacking.md)

## References
- C++ object construction basics
- Windows allocation and memory management documentation
