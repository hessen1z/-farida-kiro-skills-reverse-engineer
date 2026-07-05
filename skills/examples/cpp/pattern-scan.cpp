/**
 * pattern-scan.cpp
 *
 * Production-quality in-process pattern scanner for Windows x64.
 * Scans only committed executable memory regions.
 * Supports ?? wildcards for address operands.
 *
 * Build: cl /std:c++17 /O2 /W4 pattern-scan.cpp
 */

#include <Windows.h>
#include <cstdint>
#include <vector>
#include <string>
#include <sstream>
#include <optional>
#include <stdexcept>

// (content copied from reverse-engineering/examples/pattern-scan.cpp)
