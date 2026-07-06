---
title: Analyze Crash Recipe
skill: debugging
category: recipes
difficulty: intermediate
tags: [pe, loader, pdb, kernel, debug]
updated: 2026-07-05
---
# Analyze Crash Recipe

## Purpose
Diagnose a crash by collecting crash dump evidence, recovering the call stack, and identifying the faulting module.

## Prerequisites
- Crash dump file or live process crash.
- Symbols or PDBs for the target binary and relevant modules.
- Debugging tools such as WinDbg or Visual Studio.

## Inputs
- minidump or full dump.
- module list and binary paths.
- symbol path and loaded PDB metadata.

## Steps
1. Open the dump in WinDbg.
2. Load symbols with `.symfix` and `.reload`.
3. Use `!analyze -v` to get a summary.
4. Inspect the exception record and faulting address.
5. Walk the call stack with `k` or `kv`.
6. Validate module boundaries and image bases.
7. Examine register state and disassembly around the fault.

## Verification
- Confirm the faulting instruction and exception code.
- Verify the call stack frames are valid and symbolized.
- Check for inlined frames or missing symbols.

## Notes
- If symbols are missing, use code addresses and module offsets.
- For protected games, match module hashes and custom loader behavior.

## References
- WinDbg crash dump analysis
- Visual Studio dump debugging

## Related Material

### Knowledge
- [anti-debugging](../knowledge/anti-debugging.md)
- [debugging](../knowledge/debugging.md)
- [kernel-debugging](../knowledge/kernel-debugging.md)

### Patterns
- [breakpoint](../patterns/breakpoint.md)
- [exception-handler](../patterns/exception-handler.md)
- [stack-unwind-failure](../patterns/stack-unwind-failure.md)

### Recipes
- [analyze-exception](analyze-exception.md)
- [analyze-hang](analyze-hang.md)
- [capture-dump](capture-dump.md)

### Playbooks
- [Crash](../playbooks/Crash.md)
- [Hang](../playbooks/Hang.md)
- [Performance](../playbooks/Performance.md)

### Examples
- [kernel-debugging](../examples/kernel-debugging.md)
- [stack-unwind](../examples/stack-unwind.md)
- [winDbg-crash-analysis](../examples/winDbg-crash-analysis.md)

### References
- [references](../references/references.md)

### Rules
- [debugging-principles](../rules/debugging-principles.md)

### Prompts
- [debug-process](../prompts/debug-process.md)
- [exception-analysis](../prompts/exception-analysis.md)
- [hang-analysis](../prompts/hang-analysis.md)

### Checklists
- [checklist](../checklists/checklist.md)

