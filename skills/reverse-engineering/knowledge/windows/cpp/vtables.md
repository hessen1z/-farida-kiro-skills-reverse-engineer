---
title: C++ Virtual Function Tables (vtables)
skill: reverse-engineering
category: knowledge
difficulty: intermediate
tags: [pe, x64, gui]
updated: 2026-07-05
---
# C++ Virtual Function Tables (vtables)

## Overview

A **vtable** (virtual method table) is a mechanism used by C++ compilers to
implement runtime polymorphism. Every class with at least one virtual function
— or that inherits from such a class — gets a vtable. Each *instance* of such
a class carries a hidden pointer (the **vptr**) to its class's vtable.

---

## Memory Layout

### Class Instance Layout (MSVC x64)

```
+------------------+  <- object base address
|      vptr        |  8 bytes — points to vtable[0]
+------------------+
|   member var 1   |
+------------------+
|   member var 2   |
+------------------+
```

### vtable Layout (MSVC)

```
[vtable - 0x08]  ptr to _RTTICompleteObjectLocator   <- RTTI metadata
[vtable + 0x00]  ptr to VirtualFunc0                 <- slot 0
[vtable + 0x08]  ptr to VirtualFunc1                 <- slot 1
[vtable + 0x10]  ptr to VirtualFunc2                 <- slot 2
```

... (content copied from existing vtables.md)

## Related Material

### Knowledge
- [common-instructions](../../assembly/common-instructions.md)
- [compiler-patterns](../../assembly/compiler-patterns.md)
- [exceptions](../../cpp/exceptions.md)

### Prompts
- [analyze_binary](../../../prompts/analyze_binary.md)
- [analyze_crash](../../../prompts/analyze_crash.md)
- [analyze_memory](../../../prompts/analyze_memory.md)
## Practical Guidance

- Start from the concrete objective and define the expected outcome before applying the workflow.
- Use the related examples, recipes, playbooks, and references as the first implementation reference.
- Keep the guidance grounded in the surrounding skill context and verify the result with available evidence.
- Favor practical, maintainable steps over abstract theory when the document is used in real work.
## Verification Checklist

- Confirm that the main objective is clear and the workflow is actionable.
- Ensure the document points to the most relevant examples, recipes, or playbooks.
- Validate that the terminology is consistent with the rest of the skill.
- Check that the practical guidance is specific enough to be used without further interpretation.
