# ASLR Check Snippet

```cpp
#include <windows.h>
#include <iostream>

int main() {
    HMODULE module = GetModuleHandle(nullptr);
    if (module) {
        PIMAGE_DOS_HEADER dos = reinterpret_cast<PIMAGE_DOS_HEADER>(module);
        PIMAGE_NT_HEADERS nt = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<BYTE*>(module) + dos->e_lfanew);
        bool aslr = (nt->OptionalHeader.DllCharacteristics & IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE) != 0;
        std::cout << "ASLR enabled: " << aslr << "\n";
    }
    return 0;
}
```
