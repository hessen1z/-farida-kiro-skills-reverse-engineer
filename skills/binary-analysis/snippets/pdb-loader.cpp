// pdb-loader.cpp
// Snippet: initialize the symbol handler and load symbols for a module.

#include <windows.h>
#include <dbghelp.h>

bool LoadSymbols(HANDLE process, const char* imagePath) {
    if (!SymInitialize(process, nullptr, FALSE)) return false;
    if (!SymLoadModuleEx(process, nullptr, imagePath, nullptr, 0, 0, nullptr, 0)) return false;
    return true;
}
