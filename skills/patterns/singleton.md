---
title: Singleton Patterns
skill: patterns
category: 
difficulty: intermediate
tags: [pe, windows, asm]
updated: 2026-07-05
---
# Singleton Patterns

## Goal
Recognize singleton-style accessors that maintain a single shared instance of a subsystem or manager.

## Recognition
- A static or global instance pointer checked before use.
- Lazy initialization that allocates once and then reuses the same object.
- Synchronization guards around initialization such as interlocked operations.

## Internal Mechanism
Singletons usually centralize state in a single object and guard its initialization so repeated access returns the same instance.

## Assembly Examples
```asm
mov rax, [rip+g_instance]
test rax, rax
jnz .return
call allocate
mov [rip+g_instance], rax
.return:
ret
```

## Decompiled Examples
```cpp
Manager& GetManager() {
    static Manager* instance = nullptr;
    if (!instance) instance = new Manager();
    return *instance;
}
```

## Compiler Variations
- Different compilers may emit `cmpxchg` or other synchronization primitives for thread-safe lazy initialization.
- The accessible pattern is still the same: one shared instance guarded by initialization state.

## Common Mistakes
- Confusing a singleton with a simple global variable.
- Missing the lazy initialization path when the object is created on first access.

## Reverse Engineering Tips
- Trace the global instance pointer and any locking code around it.
- Confirm that subsequent calls do not allocate a second instance.

## Detection Heuristics
- A global pointer that is first checked and then initialized if null.
- Additional locking or atomic instructions around the initialization path.

## Validation Checklist
- [ ] The global instance pointer is identified.
- [ ] Initialization and reuse semantics are documented.

## Related Knowledge
- [factory](factory.md)
- [constructor](constructor.md)

## Related Recipes
- [Recover_Classes](../recipes/Recover_Classes.md)

## Related Playbooks
- [GameHacking](../playbooks/GameHacking.md)

## References
- C++ singleton implementation patterns
- Synchronization primitives in Windows internals
