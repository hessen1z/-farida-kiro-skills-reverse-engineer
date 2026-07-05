# Destructor Pattern

Goal:
Recognize C++ destructors and cleanup sequences in assembly.

Recognition signs:
- Destructor functions often free members, call base destructors, and may destroy vptrs.
- Patterns: sequence of calls to member destructors, vptr write (in some patterns), and deallocation.

Assembly examples:
- x64:
```
mov rax, [rcx] ; vptr
call qword ptr [rax+8] ; virtual dtor
mov rcx, rdx
call operator_delete
```

Decompiled equivalent:
```
MyClass::~MyClass() {
  if (this->member) delete this->member;
  Base::~Base();
}
```

Why compiler generates this pattern:
- Ensure deterministic resource release; destructor code mirrors constructor but in reverse order.

Variations across compilers:
- MSVC emits scalar and vector deleting destructors with different thunks; GCC/Clang have different naming and destructor variants.

Common mistakes:
- Confusing destructor with plain function that frees memory — destructors often also adjust vptrs and call base destructors.

Reverse engineering tips:
- Identify destructors by common sequences: calls to `operator delete` after member cleanup.
- In IDA, use cross-references from `delete` and naming heuristics to mark destructor functions.

Detection heuristics:
- Calls to `operator delete` or `free` in conjunction with member-cleanup calls.

Related patterns:
- `constructor.md`
- `allocator.md`

Related knowledge pages:
- knowledge/cpp/exceptions.md
- knowledge/windows/cpp/vtables.md
