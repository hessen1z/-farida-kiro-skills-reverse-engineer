---
title: CPU Architecture
skill: computer-architecture
category: knowledge
difficulty: intermediate
tags: [pe, windows, asm, x64, driver, gui, kernel, debug]
updated: 2026-07-05
---
# CPU Architecture

## Overview

The CPU is the central execution engine of a computer system. It interprets instructions, performs arithmetic and logic operations, manages control flow, and coordinates access to memory and I/O. Modern CPUs are built from multiple cores, execution units, caches, and control logic that together enable high instruction throughput and low latency.

## Internal Design

A modern CPU includes several functional components:
- Instruction Fetch Unit: reads instructions from memory or cache.
- Decode Unit: translates machine code into internal micro-operations.
- Execution Units: perform arithmetic, logic, load/store, and branch operations.
- Register File: holds architectural registers for immediate use.
- Cache Hierarchy: accelerates access to instructions and data.
- Memory Management Unit (MMU): translates virtual addresses to physical addresses.
- Branch Predictor: predicts control flow to keep pipelines full.
- Reorder Buffer: tracks out-of-order execution and retirement.

This architecture is optimized for parallelism and latency hiding. The CPU uses multiple pipelines and speculative execution to maximize instruction throughput while preserving program semantics.

## Data Structures

### Register File
The architectural register file stores:
- General purpose registers (RAX, RBX, RCX, RDX, RSI, RDI, RBP, RSP, R8–R15)
- Instruction Pointer: RIP
- Flags Register: RFLAGS
- Segment registers and control registers in protected mode

### Cache Lines and Sets
Modern caches are organized into lines and sets:
- Cache line size: usually 64 bytes on x86/x64
- Associativity: number of ways per set (e.g., 8-way)
- Set index: derived from the physical address

### Page Tables
The MMU uses page tables to map virtual addresses to physical frames. Common x86-64 structures include:
- PML4 (top-level directory)
- PDPT (page-directory pointer table)
- PD (page directory)
- PT (page table)

### Micro-op Queues
Decoded instructions are often converted to micro-operations (µops), which are dispatched to execution units. The reorder buffer and reservation stations hold µops until operands are ready.

## Important APIs

### CPUID
The CPUID instruction reports processor features and topology. It is essential for both runtime adaptation and reverse engineering.

### RDTSC
Read Time-Stamp Counter provides a cycle-level timestamp used for performance measurement and side-channel probing.

### RDPMC
Read Performance Monitoring Counters for hardware event counters such as cache misses and branch mispredictions.

### MSRs
Model Specific Registers expose processor configuration and control bits used for performance tuning and debug.

## Assembly Examples

### Basic CPUID Usage
```asm
mov eax, 0
cpuid
; returns vendor string in EBX, EDX, ECX
```

### Checking Feature Flags
```asm
mov eax, 1
cpuid
bt ecx, 0 ; check SSE3 support
jnc no_sse3
```

### Reading RDTSC
```asm
rdtsc
shl rdx, 32
or rax, rdx
```

## C++ Examples

### Read CPUID in C++
```cpp
#include <array>
#include <cstdint>

std::array<uint32_t, 4> cpuid(uint32_t leaf) {
    uint32_t eax, ebx, ecx, edx;
    __asm__ volatile("cpuid"
                     : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
                     : "a"(leaf));
    return {eax, ebx, ecx, edx};
}
```

### Read TSC in C++
```cpp
#include <cstdint>

uint64_t read_tsc() {
    uint32_t lo, hi;
    __asm__ volatile("rdtsc" : "=a"(lo), "=d"(hi));
    return ((uint64_t)hi << 32) | lo;
}
```

## Reverse Engineering Notes

- The CPU microarchitecture defines how instructions are decoded and retired, but the architectural behavior remains stable.
- Reverse engineers must distinguish between architectural semantics and microarchitectural side effects such as speculation and cache timing.
- CPUID and feature flags are often used in binaries to select optimized code paths.
- Many Windows drivers and performance-sensitive code use MSRs, which can be observed through kernel-mode instrumentation.

## Debugging Notes

- Instruction pointer faults indicate either bad control flow or invalid code/data boundaries.
- Watch for speculative execution side effects in post-mortem analysis: a wrong branch prediction can have side effects only visible through timing, not state.
- CPU exceptions such as #GP, #PF, and #UD reveal illegal instructions, page-faulting memory references, and unsupported features.
- When debugging low-level code, cross-check register values with the code's expected instruction stream and the current privilege level.

## Performance Notes

- Key performance factors include instruction-level parallelism, cache locality, branch prediction accuracy, and memory latency.
- The fastest code minimizes unpredictable branches and avoids cache conflicts.
- Use hardware performance counters to correlate events like branch misses and cache stalls with source-level hotspots.
- Compile-time optimizations often change instruction ordering and register allocation; profile the generated assembly, not just the source.

## Common Mistakes

- Confusing architectural registers with internal rename registers used by out-of-order execution.
- Assuming load/store ordering is the same as program order on weakly-ordered architectures.
- Ignoring the impact of cache line alignment and false sharing on performance.
- Treating speculative execution as synchronous execution; side effects may be visible only through timing and expanded microarchitecture analysis.

## References

- Intel 64 and IA-32 Architectures Software Developer’s Manual
- AMD64 Architecture Programmer’s Manual
- Agner Fog, "Optimizing Software in C++"
- Intel Developer Zone and whitepapers on Microarchitecture and Performance

## Related Material

- Skill overview: [skill.md](../skill.md)

