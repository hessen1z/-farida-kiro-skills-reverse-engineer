---
title: Hook Detection Pattern
skill: anti-cheat
category: patterns
difficulty: intermediate
tags: [pe, anti-cheat, driver]
updated: 2026-07-05
---
# Hook Detection Pattern

## Pattern Name
Runtime hook detection

## Problem
Detect code paths that verify whether function pointers or import entries have been modified.

## Context
Anti-cheat systems look for hooks installed by cheat tools or injected overlays.

## Recognition
- scanning import tables or function prologues
- comparing code bytes to expected signatures
- checking for inline patches or trampoline hooks

## Evidence
- checks against original module images
- detection of non-standard branch targets
- metadata describing hook locations

## Resolution / Action
- trace the hook detection workflow and impacted functions
- identify whether detection is per-module or global
- inspect the enforcement response when a hook is found

## Notes
- Hook detection may be localized to security-critical functions.
- Some anti-cheat logic checks the IAT/Import Address Table directly.

## References
- API hook detection and integrity validation

## Related Material

### Knowledge
- [architecture](../knowledge/architecture.md)

### Patterns
- [driver-enforcement](driver-enforcement.md)
- [memory-scan](memory-scan.md)

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

