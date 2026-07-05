# C++ RTTI in MSVC (Run-Time Type Information)

## Overview

RTTI allows programs to determine the type of an object at runtime. MSVC implements
RTTI through a set of structures embedded in the binary, primarily used by
`dynamic_cast` and `typeid`. Understanding these structures is essential for
recovering class names and hierarchies from binaries.

---

## Core RTTI Structures (MSVC x64)

### TypeDescriptor (type_info)

Stored in `.data` section. Contains the mangled class name.

```
Offset  Size  Field
------  ----  -----
+0x00    8    pVFTable  -> type_info's vtable (for typeid comparisons)
+0x08    8    spare     -> 0 (unused, historically a demangled name cache)
+0x10    ?    name[]    -> null-terminated mangled name, e.g. ".?AVMyClass@@"
```

Mangled name format:
- Classes:   `.?AVClassName@@` or `.?AVClassName@Namespace@@`
- Structs:   `.?AUStructName@@`
- Templates: `.?AV?$Vector@H@@`

### _RTTICompleteObjectLocator (COL)

Stored in `.rdata`. One per vtable. Found at `vtable[-1]`.

```cpp
struct _RTTICompleteObjectLocator {
    DWORD signature;        // 0=x86, 1=x64
    DWORD offset;           // byte offset from this vtable's object to the complete object
    DWORD cdOffset;         // constructor displacement offset
    int   pTypeDescriptor;  // RVA (x64) or ptr (x86) to TypeDescriptor
    int   pClassDescriptor; // RVA/ptr to _RTTIClassHierarchyDescriptor
    int   pSelf;            // RVA to this COL (x64 only; used for rebasing)
};
```

**pSelf** is the self-referential RVA — its value equals `COL_address - image_base`.
This is used to verify you have a valid COL and to rebase correctly.

... (content copied from existing rtti.md)

## Related Material

### Knowledge
- [common-instructions](../../assembly/common-instructions.md)
- [compiler-patterns](../../assembly/compiler-patterns.md)
- [exceptions](../../cpp/exceptions.md)

### Prompts
- [analyze_binary](../../../prompts/analyze_binary.md)
- [analyze_crash](../../../prompts/analyze_crash.md)
- [analyze_memory](../../../prompts/analyze_memory.md)

