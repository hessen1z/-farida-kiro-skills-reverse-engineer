// parse-exports.cpp
// Example: parse PE export directory and list exports.

#include <windows.h>
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: parse-exports <path>\n";
        return 1;
    }

    const char* path = argv[1];
    HANDLE file = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE) return 1;

    HANDLE mapping = CreateFileMappingA(file, nullptr, PAGE_READONLY, 0, 0, nullptr);
    uint8_t* base = reinterpret_cast<uint8_t*>(MapViewOfFile(mapping, FILE_MAP_READ, 0, 0, 0));
    auto dos = reinterpret_cast<PIMAGE_DOS_HEADER>(base);
    auto nt = reinterpret_cast<PIMAGE_NT_HEADERS>(base + dos->e_lfanew);
    auto exportDir = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
    if (!exportDir.VirtualAddress) return 1;

    auto exportData = reinterpret_cast<PIMAGE_EXPORT_DIRECTORY>(base + exportDir.VirtualAddress);
    auto names = reinterpret_cast<uint32_t*>(base + exportData->AddressOfNames);
    auto ordinals = reinterpret_cast<uint16_t*>(base + exportData->AddressOfNameOrdinals);
    auto functions = reinterpret_cast<uint32_t*>(base + exportData->AddressOfFunctions);

    for (uint32_t i = 0; i < exportData->NumberOfNames; ++i) {
        const char* name = reinterpret_cast<const char*>(base + names[i]);
        uint16_t ordinal = exportData->Base + ordinals[i];
        uint32_t rva = functions[ordinals[i]];
        std::cout << "Export: " << name << " @ ordinal " << ordinal << " RVA 0x" << std::hex << rva << std::dec << "\n";
    }

    UnmapViewOfFile(base);
    CloseHandle(mapping);
    CloseHandle(file);
    return 0;
}
