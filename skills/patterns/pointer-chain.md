---
title: Pointer Chain Patterns
skill: patterns
category: 
difficulty: intermediate
tags: [pe, windows, asm]
updated: 2026-07-05
---
# Pointer Chain Patterns

## Goal
Recognize multi-step pointer dereferences used to reach objects, lists, or global state through one or more indirections.

## Recognition
- Repeated memory loads with constant offsets and null checks.
- Base-plus-offset patterns that traverse linked structures or arrays.
- A chain such as `base -> next -> value` where each hop is a pointer dereference.

## Internal Mechanism
Pointer chains are often used to navigate object graphs, linked lists, game state containers, or runtime registries without hardcoding absolute addresses.

## Assembly Examples
```asm
mov rax, [rip+g_list_head]
test rax, rax
je .end
mov rbx, [rax+0x10]
```

## Decompiled Examples
```cpp
auto* node = g_list_head;
if (node) {
    auto* next = node->next;
}
```

## Compiler Variations
- The pattern is compiler-agnostic and appears in hand-written code and optimized builds alike.
- Different compilers may use different register allocation and stack handling but preserve the same dereference chain.

## Common Mistakes
- Treating a single indirect load as a full pointer chain when multiple hops are required.
- Failing to validate the chain at runtime when a pointer can be null or invalid.

## Reverse Engineering Tips
- Record each hop and offset to reconstruct the logical structure.
- Validate the same chain under multiple states or builds when possible.

## Detection Heuristics
- Multiple dereference operations with null checks between them.
- Use of global or object-local pointers that feed into additional loads.

## Validation Checklist
- [ ] The chain is confirmed by static and, where possible, runtime evidence.
- [ ] Offsets map to coherent structure fields.

## Related Knowledge
- [stl-vector](stl-vector.md)
- [singleton](singleton.md)

## Related Recipes
- [Find_Offsets](../recipes/Find_Offsets.md)

## Related Playbooks
- [GameHacking](../playbooks/GameHacking.md)

## References
- Reverse engineering tutorials on pointer chasing
- Windows memory and object layout references
