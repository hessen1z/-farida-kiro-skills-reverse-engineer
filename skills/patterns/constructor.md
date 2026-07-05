# Constructor Patterns
Goal: Recognize C++ constructors in assembly.

Signs:
- Writes vtable pointer.
- Initializes member fields.
- Calls base constructor first.
- Returns this pointer.
- No return value computation.

Assembly Examples:
```
mov [rcx], offset vtable
mov dword ptr [rcx+18],0
call BaseClass::BaseClass
```

Recognition: Confidence: High

Common mistakes:
- Confusing constructor with initializer.
