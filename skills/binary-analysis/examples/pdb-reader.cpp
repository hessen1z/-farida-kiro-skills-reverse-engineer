// pdb-reader.cpp
// Example: inspect PE debug directory and print PDB CodeView metadata.

#include <windows.h>
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: pdb-reader <path>\n";
        return 1;
    }

    const char* path = argv[1];
    HANDLE file = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE) return 1;

    HANDLE mapping = CreateFileMappingA(file, nullptr, PAGE_READONLY, 0, 0, nullptr);
    uint8_t* base = reinterpret_cast<uint8_t*>(MapViewOfFile(mapping, FILE_MAP_READ, 0, 0, 0));
    auto dos = reinterpret_cast<PIMAGE_DOS_HEADER>(base);
    auto nt = reinterpret_cast<PIMAGE_NT_HEADERS>(base + dos->e_lfanew);
    auto debugDir = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG];
    if (!debugDir.VirtualAddress) return 1;

    auto debugEntry = reinterpret_cast<PIMAGE_DEBUG_DIRECTORY>(base + debugDir.VirtualAddress);
    for (; debugEntry->Type; ++debugEntry) {
        if (debugEntry->Type == IMAGE_DEBUG_TYPE_CODEVIEW) {
            auto cv = reinterpret_cast<uint8_t*>(base + debugEntry->AddressOfRawData);
            if (std::memcmp(cv, "RSDS", 4) == 0) {
                auto sig = reinterpret_cast<GUID*>(cv + 4);
                auto age = *reinterpret_cast<uint32_t*>(cv + 20);
                auto pdbName = reinterpret_cast<const char*>(cv + 24);
                std::cout << "PDB: " << pdbName << "\n";
                std::cout << "GUID: " << std::hex << sig->Data1 << "-" << sig->Data2 << "-" << sig->Data3 << std::dec << "\n";
                std::cout << "Age: " << age << "\n";
            }
        }
    }

    UnmapViewOfFile(base);
    CloseHandle(mapping);
    CloseHandle(file);
    return 0;
}
