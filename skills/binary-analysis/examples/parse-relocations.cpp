// parse-relocations.cpp
// Example: parse PE base relocations and list relocation entries.

#include <windows.h>
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: parse-relocations <path>\n";
        return 1;
    }

    const char* path = argv[1];
    HANDLE file = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE) return 1;

    HANDLE mapping = CreateFileMappingA(file, nullptr, PAGE_READONLY, 0, 0, nullptr);
    uint8_t* base = reinterpret_cast<uint8_t*>(MapViewOfFile(mapping, FILE_MAP_READ, 0, 0, 0));
    auto dos = reinterpret_cast<PIMAGE_DOS_HEADER>(base);
    auto nt = reinterpret_cast<PIMAGE_NT_HEADERS>(base + dos->e_lfanew);
    auto relocDir = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC];
    if (!relocDir.VirtualAddress) return 1;

    auto block = reinterpret_cast<PIMAGE_BASE_RELOCATION>(base + relocDir.VirtualAddress);
    while (block->VirtualAddress && block->SizeOfBlock) {
        uint32_t count = (block->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(uint16_t);
        auto entries = reinterpret_cast<uint16_t*>(block + 1);
        std::cout << "Relocation block at VA 0x" << std::hex << block->VirtualAddress << std::dec << " count=" << count << "\n";
        for (uint32_t i = 0; i < count; ++i) {
            uint16_t entry = entries[i];
            uint16_t type = entry >> 12;
            uint16_t offset = entry & 0x0FFF;
            std::cout << "  type=" << type << " offset=0x" << std::hex << offset << std::dec << "\n";
        }
        block = reinterpret_cast<PIMAGE_BASE_RELOCATION>(reinterpret_cast<uint8_t*>(block) + block->SizeOfBlock);
    }

    UnmapViewOfFile(base);
    CloseHandle(mapping);
    CloseHandle(file);
    return 0;
}
