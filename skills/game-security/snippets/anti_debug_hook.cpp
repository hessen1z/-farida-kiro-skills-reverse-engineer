# Anti-Debug Hook Snippet

```cpp
#include <windows.h>
#include <iostream>

BOOL WINAPI MyIsDebuggerPresent() {
    return FALSE;
}

int main() {
    std::cout << "Debugger present: " << MyIsDebuggerPresent() << "\n";
    return 0;
}
```
