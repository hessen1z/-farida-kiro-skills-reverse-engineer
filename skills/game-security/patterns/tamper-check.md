---
title: Tamper Check Pattern
skill: game-security
category: patterns
difficulty: intermediate
tags: [pe, anti-cheat, driver, debug]
updated: 2026-07-05
---
# Tamper Check Pattern

## Pattern Name
Runtime integrity validation

## Problem
Detect code that verifies whether executable pages or critical data structures have been modified.

## Context
Anti-tamper protections protect game assets, client code, and runtime state from unauthorized changes.

## Recognition
- code page hashing or checksum routines
- repeated validation of memory regions
- comparisons against stored signatures or encrypted data

## Evidence
- failures trigger process termination or protection escalation.
- code checks appear in initialization or hot paths.
- integrity checks cover mapped files, modules, and stack data.

## Resolution / Action
- trace the check to its protected region.
- identify whether it can be bypassed or satisfied cleanly.
- preserve original memory state before modifying it.

## Notes
- Tamper checks may use anti-debug and anti-hook techniques.
- Some engines encrypt or pack code to make integrity checks harder.

## References
- Runtime integrity verification articles

## Related Material

### Knowledge
- [anti-cheat](../knowledge/anti-cheat.md)

### Patterns
- [anti-debug](anti-debug.md)

### Recipes
- [analyze-tamper](../recipes/analyze-tamper.md)
- [trace-anti-debug](../recipes/trace-anti-debug.md)

### Playbooks
- [ClientSecurity](../playbooks/ClientSecurity.md)
- [DriverSecurity](../playbooks/DriverSecurity.md)

### Examples
- [anti-debug-analysis](../examples/anti-debug-analysis.md)

### References
- [references](../references/references.md)

### Rules
- [security-principles](../rules/security-principles.md)

### Prompts
- [security-analysis](../prompts/security-analysis.md)

### Checklists
- [checklist](../checklists/checklist.md)

