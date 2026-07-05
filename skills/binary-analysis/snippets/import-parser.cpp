// import-parser.cpp
// Snippet: parse import descriptors and resolve imported function names.

#include <windows.h>

void ParseImports(uint8_t* base, PIMAGE_NT_HEADERS nt) {
    auto importDir = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    if (!importDir.VirtualAddress) return;

    auto importDesc = reinterpret_cast<PIMAGE_IMPORT_DESCRIPTOR>(base + importDir.VirtualAddress);
    for (; importDesc->Name; ++importDesc) {
        const char* dllName = reinterpret_cast<const char*>(base + importDesc->Name);
        auto thunk = reinterpret_cast<PIMAGE_THUNK_DATA>(base + importDesc->OriginalFirstThunk);
        if (!importDesc->OriginalFirstThunk) thunk = reinterpret_cast<PIMAGE_THUNK_DATA>(base + importDesc->FirstThunk);
        for (; thunk->u1.AddressOfData; ++thunk) {
            if (IMAGE_SNAP_BY_ORDINAL(thunk->u1.Ordinal)) continue;
            auto name = reinterpret_cast<PIMAGE_IMPORT_BY_NAME>(base + thunk->u1.AddressOfData);
            // use name->Name as the imported function name
        }
    }
}
