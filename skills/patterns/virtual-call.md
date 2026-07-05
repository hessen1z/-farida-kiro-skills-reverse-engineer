# Virtual Call Pattern

Goal:
Recognize object-oriented virtual calls through vtables and map them to slots.

Pattern:
```
mov rax, [rcx]
call qword ptr [rax+30]
```
Recognition: Virtual call
Slot = 6 (30/8)
Meaning: Call through vtable. Possible OO dispatch.
Assembly examples (x86/x64):
- x64: `mov rax, [rcx]` / `call qword ptr [rax+8*slot]`
- x86: `mov eax, [ecx]` / `call dword ptr [eax+4*slot]`

Why compiler generates this pattern:
- Implement virtual dispatch via vtable pointers stored at object base.

Variations:
- Multiple inheritance may use secondary vtables and thunks that adjust `this`.

Reverse engineering tips:
- Use RTTI and COL detection to recover class names; find `vtable[-1]` to locate COL.
- In IDA: create a structure for the vtable and apply function names to slots.

Related knowledge:
- knowledge/windows/cpp/vtables.md

