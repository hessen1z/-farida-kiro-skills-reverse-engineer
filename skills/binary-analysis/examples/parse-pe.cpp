// parse-pe.cpp
// Example: parse PE headers and section table.

#include <windows.h>
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: parse-pe <path>\n";
        return 1;
    }

    const char* path = argv[1];
    HANDLE file = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    DWORD size = GetFileSize(file, nullptr);
    HANDLE mapping = CreateFileMappingA(file, nullptr, PAGE_READONLY, 0, 0, nullptr);
    if (!mapping) {
        std::cerr << "Failed to create file mapping\n";
        CloseHandle(file);
        return 1;
    }

    uint8_t* base = reinterpret_cast<uint8_t*>(MapViewOfFile(mapping, FILE_MAP_READ, 0, 0, 0));
    if (!base) {
        std::cerr << "Failed to map view of file\n";
        CloseHandle(mapping);
        CloseHandle(file);
        return 1;
    }

    auto dos = reinterpret_cast<PIMAGE_DOS_HEADER>(base);
    if (dos->e_magic != IMAGE_DOS_SIGNATURE) {
        std::cerr << "Not a valid PE file\n";
        return 1;
    }

    auto nt = reinterpret_cast<PIMAGE_NT_HEADERS>(base + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE) {
        std::cerr << "Invalid NT headers\n";
        return 1;
    }

    std::cout << "Machine: " << std::hex << nt->FileHeader.Machine << std::dec << "\n";
    std::cout << "Entry point: 0x" << std::hex << nt->OptionalHeader.AddressOfEntryPoint << std::dec << "\n";
    std::cout << "Section count: " << nt->FileHeader.NumberOfSections << "\n";

    auto section = IMAGE_FIRST_SECTION(nt);
    for (unsigned i = 0; i < nt->FileHeader.NumberOfSections; ++i) {
        std::cout << "Section " << i << ": " << reinterpret_cast<char*>(section[i].Name) << "\n";
        std::cout << "  VirtualAddress: 0x" << std::hex << section[i].VirtualAddress << dec << "\n";
        std::cout << "  SizeOfRawData: " << section[i].SizeOfRawData << "\n";
    }

    UnmapViewOfFile(base);
    CloseHandle(mapping);
    CloseHandle(file);
    return 0;
}
