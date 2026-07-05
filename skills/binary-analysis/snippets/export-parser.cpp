// export-parser.cpp
// Snippet: parse export names and function RVAs.

#include <windows.h>

void ParseExports(uint8_t* base, PIMAGE_NT_HEADERS nt) {
    auto exportDir = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
    if (!exportDir.VirtualAddress) return;

    auto exportData = reinterpret_cast<PIMAGE_EXPORT_DIRECTORY>(base + exportDir.VirtualAddress);
    auto names = reinterpret_cast<uint32_t*>(base + exportData->AddressOfNames);
    auto ordinals = reinterpret_cast<uint16_t*>(base + exportData->AddressOfNameOrdinals);
    auto functions = reinterpret_cast<uint32_t*>(base + exportData->AddressOfFunctions);

    for (uint32_t i = 0; i < exportData->NumberOfNames; ++i) {
        const char* name = reinterpret_cast<const char*>(base + names[i]);
        uint16_t ordinal = exportData->Base + ordinals[i];
        uint32_t rva = functions[ordinals[i]];
        // record export name, ordinal, and RVA
    }
}
