# Breakpoint and Watchpoint Snippet

```cpp
#include <windows.h>
#include <iostream>

void SetHardwareBreakpoint(void* address) {
    CONTEXT ctx = {};
    ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
    HANDLE thread = GetCurrentThread();
    if (SuspendThread(thread) != -1) {
        GetThreadContext(thread, &ctx);
        ctx.Dr0 = reinterpret_cast<DWORD_PTR>(address);
        ctx.Dr7 = 1;
        SetThreadContext(thread, &ctx);
        ResumeThread(thread);
    }
}

int main() {
    int target = 0;
    SetHardwareBreakpoint(&target);
    target = 42;
    std::cout << "Target = " << target << "\n";
    return 0;
}
```
