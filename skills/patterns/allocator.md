# Allocator Pattern

Goal:
Recognize heap allocation, free, and custom allocator idioms in assembly.

Recognition signs:
- Calls to `malloc`, `operator new`, `HeapAlloc`, `VirtualAlloc` or custom allocator functions.
- Patterns: prepare size in register/stack, call allocator, check return, initialize memory.

Assembly examples:
- x64 (operator new wrapper):
```
mov ecx, esi ; size
call operator_new
test rax, rax
jz alloc_fail
```
- Using HeapAlloc:
```
push 0
push size
push heapHandle
call HeapAlloc
```

Decompiled equivalent:
```
void* p = operator new(size);
if (!p) throw bad_alloc;
```

Why compiler generates this pattern:
- Separate allocation and construction phases; constructors follow allocation.

Variations across compilers:
- Naming and wrapper functions may differ; custom allocators replace standard calls.

Common mistakes:
- Confusing allocator wrapper with constructor; allocation is before constructor call.

Reverse engineering tips:
- Trace allocation return pointer to find object layout; useful to locate global caches.
- Identify allocator call sites to map memory ownership semantics.

Detection heuristics:
- Call to known allocator symbols or typical calling sequences; following `mov rcx, size` / `call` patterns.

Related patterns:
- `constructor.md`
- `destructor.md`

Related knowledge pages:
- knowledge/cpp/stl.md
- knowledge/windows/memory-manager.md

