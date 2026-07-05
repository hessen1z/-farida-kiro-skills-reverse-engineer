# Symbol Initialization Snippet

```cpp
#include <windows.h>
#include <dbghelp.h>

void InitSymbols(HANDLE process) {
    SymSetOptions(SYMOPT_DEFERRED_LOADS | SYMOPT_UNDNAME | SYMOPT_LOAD_LINES);
    SymInitialize(process, nullptr, FALSE);
    SymSetSearchPath(process, "srv*C:\\symbols*https://msdl.microsoft.com/download/symbols");
}
```
