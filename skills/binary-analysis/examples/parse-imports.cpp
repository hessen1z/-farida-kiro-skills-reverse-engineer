// parse-imports.cpp
// Example: parse PE import directory and list imported DLLs and functions.

#include <windows.h>
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: parse-imports <path>\n";
        return 1;
    }

    const char* path = argv[1];
    HANDLE file = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE) return 1;

    HANDLE mapping = CreateFileMappingA(file, nullptr, PAGE_READONLY, 0, 0, nullptr);
    uint8_t* base = reinterpret_cast<uint8_t*>(MapViewOfFile(mapping, FILE_MAP_READ, 0, 0, 0));
    auto dos = reinterpret_cast<PIMAGE_DOS_HEADER>(base);
    auto nt = reinterpret_cast<PIMAGE_NT_HEADERS>(base + dos->e_lfanew);
    auto importDir = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    if (!importDir.VirtualAddress) return 1;

    auto importDesc = reinterpret_cast<PIMAGE_IMPORT_DESCRIPTOR>(base + importDir.VirtualAddress);
    for (; importDesc->Name; ++importDesc) {
        const char* dllName = reinterpret_cast<const char*>(base + importDesc->Name);
        std::cout << "DLL: " << dllName << "\n";

        auto thunk = reinterpret_cast<PIMAGE_THUNK_DATA>(base + importDesc->OriginalFirstThunk);
        if (!importDesc->OriginalFirstThunk) thunk = reinterpret_cast<PIMAGE_THUNK_DATA>(base + importDesc->FirstThunk);

        for (; thunk->u1.AddressOfData; ++thunk) {
            if (IMAGE_SNAP_BY_ORDINAL(thunk->u1.Ordinal)) {
                std::cout << "  Ordinal: " << IMAGE_ORDINAL(thunk->u1.Ordinal) << "\n";
            } else {
                auto name = reinterpret_cast<PIMAGE_IMPORT_BY_NAME>(base + thunk->u1.AddressOfData);
                std::cout << "  Name: " << name->Name << "\n";
            }
        }
    }

    UnmapViewOfFile(base);
    CloseHandle(mapping);
    CloseHandle(file);
    return 0;
}
