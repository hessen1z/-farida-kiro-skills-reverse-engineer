# Memory Scan Snippet

```cpp
#include <windows.h>
#include <iostream>

bool ScanProcessMemory(HANDLE process, uintptr_t address, SIZE_T size) {
    std::vector<BYTE> buffer(size);
    SIZE_T read = 0;
    if (!ReadProcessMemory(process, reinterpret_cast<LPCVOID>(address), buffer.data(), size, &read)) {
        return false;
    }
    // Analyze buffer contents here.
    return true;
}

int main() {
    HANDLE process = GetCurrentProcess();
    ScanProcessMemory(process, 0x1000, 0x100);
    return 0;
}
```
