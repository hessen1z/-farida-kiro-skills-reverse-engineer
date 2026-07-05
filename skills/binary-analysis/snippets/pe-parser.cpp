// pe-parser.cpp
// Snippet: validate PE header and locate the optional header.

#include <windows.h>

bool IsValidPeImage(uint8_t* base) {
    auto dos = reinterpret_cast<PIMAGE_DOS_HEADER>(base);
    if (dos->e_magic != IMAGE_DOS_SIGNATURE) return false;

    auto nt = reinterpret_cast<PIMAGE_NT_HEADERS>(base + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE) return false;
    return true;
}

PIMAGE_NT_HEADERS GetNtHeaders(uint8_t* base) {
    auto dos = reinterpret_cast<PIMAGE_DOS_HEADER>(base);
    return reinterpret_cast<PIMAGE_NT_HEADERS>(base + dos->e_lfanew);
}
