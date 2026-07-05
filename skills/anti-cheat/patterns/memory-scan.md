# Memory Scan Pattern

## Pattern Name
Process memory scanning

## Problem
Detect scanning logic used to inspect process memory for cheats, injected code, or unauthorized hooks.

## Context
Anti-cheat systems often scan user processes or game memory for known patterns or anomalies.

## Recognition
- calls to `ReadProcessMemory`, `NtQueryVirtualMemory`, `VirtualQueryEx`
- iterating over process address space or module ranges
- pattern matching against known cheat signatures

## Evidence
- repeated memory reads across potential cheat areas
- comparisons against known code or data patterns
- cache of scanned regions and detection status

## Resolution / Action
- identify the scanning target and signature logic
- determine whether scanning occurs in user-mode or kernel-mode
- validate whether false positives can arise from legitimate code

## Notes
- Kernel-mode scanning can observe user-mode process memory without API restrictions.
- Anti-cheat scanners may exclude trusted modules or subsystems.

## References
- Windows process memory inspection guidance

## Related Material

### Knowledge
- [architecture](../knowledge/architecture.md)

### Patterns
- [driver-enforcement](driver-enforcement.md)
- [hook-detection](hook-detection.md)

### Recipes
- [analyze-driver](../recipes/analyze-driver.md)
- [analyze-user-mode](../recipes/analyze-user-mode.md)

### Playbooks
- [DetectionAndEnforcement](../playbooks/DetectionAndEnforcement.md)

### Examples
- [driver-analysis](../examples/driver-analysis.md)
- [user-mode-analysis](../examples/user-mode-analysis.md)

### References
- [references](../references/references.md)

### Rules
- [anti-cheat-principles](../rules/anti-cheat-principles.md)

### Prompts
- [anti-cheat-analysis](../prompts/anti-cheat-analysis.md)

### Checklists
- [checklist](../checklists/checklist.md)

