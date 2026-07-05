# Asset Path Snippet

```cpp
#include <windows.h>
#include <string>

std::wstring BuildAssetPath(const std::wstring& root, const std::wstring& relative) {
    std::wstring path = root;
    if (!path.empty() && path.back() != L'\\') {
        path.push_back(L'\\');
    }
    path += relative;
    return path;
}

int main() {
    auto assetPath = BuildAssetPath(L"C:\\Game\\Assets", L"textures\\hero.dds");
    return 0;
}
```
