# CFG Check Snippet

```cpp
#include <windows.h>
#include <iostream>

int main() {
    HMODULE module = GetModuleHandle(nullptr);
    if (module) {
        PIMAGE_DOS_HEADER dos = reinterpret_cast<PIMAGE_DOS_HEADER>(module);
        PIMAGE_NT_HEADERS nt = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<BYTE*>(module) + dos->e_lfanew);
        bool cfg = (nt->OptionalHeader.DllCharacteristics & IMAGE_DLLCHARACTERISTICS_GUARD_CF) != 0;
        std::cout << "CFG enabled: " << cfg << "\n";
    }
    return 0;
}
```
