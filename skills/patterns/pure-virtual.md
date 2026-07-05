# Pure Virtual / __purecall Pattern

Goal:
Detect pure-virtual call sites and the `__purecall` handler indicating abstract methods.

Recognition signs:
- Calls to `__purecall` (MSVC) or references to pure virtual stubs in vtables.
- Vtable entries pointing to `__purecall` address.

Assembly examples:
- x64 vtable slot pointing to `__purecall`:
```
mov rax, [rcx]
call qword ptr [rax+0x10]  ; if points to __purecall
```

Decompiled equivalent:
```
virtual void Foo() = 0; // pure virtual
```

Why compiler generates this pattern:
- Abstract base classes need a placeholder to crash at runtime if pure virtual is invoked.

Variations across compilers:
- MSVC uses `__purecall`; GCC/Clang use `__cxa_pure_virtual`.

Common mistakes:
- Treating `__purecall` hits as legitimate API calls; they indicate a design/logic error in the program.

Reverse engineering tips:
- Rename vtable slots that point to `__purecall` as `pure_virtual_stub` and mark class as abstract.
- Search for `__purecall` symbol in imports or within the binary to locate abstract methods.

Detection heuristics:
- vtable entries equal to address of known pure-call stubs.

Related patterns:
- `virtual-call.md`
- `vtables.md` (knowledge)

Related knowledge pages:
- knowledge/windows/cpp/vtables.md
- knowledge/windows/cpp/rtti.md
