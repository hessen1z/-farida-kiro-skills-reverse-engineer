---
title: Process Protection Pattern
skill: windows-security
category: patterns
difficulty: intermediate
tags: [pe, windows, gui, kernel, debug]
updated: 2026-07-05
---
# Process Protection Pattern

## Pattern Name
Windows Process Protection

## Problem
Detect process-level restrictions that prevent debugging, memory access, or interprocess inspection.

## Context
Windows process protection is designed to limit interactions with sensitive or elevated processes.

## Recognition
- processes marked as `ProtectedProcessLight` or `ProtectedProcess`.
- restricted handle access for `PROCESS_QUERY_INFORMATION`, `PROCESS_VM_READ`, or `PROCESS_DUP_HANDLE`.
- kernel-enforced denial of introspection operations.

## Evidence
- failed attach attempts with `ERROR_ACCESS_DENIED`.
- protected flags visible in process object structures.
- process behavior consistent with system or security services.

## Resolution / Action
- leverage trusted signed helper processes if available.
- focus on alternative analysis channels such as event logs, IPC, or loaded module metadata.
- document protection levels and access boundaries.

## Notes
- Process protection does not necessarily imply code integrity, but the two are often combined.

## Related Material

### Knowledge
- [code-integrity](../knowledge/code-integrity.md)
- [mitigations](../knowledge/mitigations.md)
- [protected-process](../knowledge/protected-process.md)

### Patterns
- [aslr](aslr.md)
- [cfg](cfg.md)
- [code-signing](code-signing.md)

### Recipes
- [analyze-code-integrity](../recipes/analyze-code-integrity.md)
- [analyze-protected-process](../recipes/analyze-protected-process.md)
- [analyze-security-policy](../recipes/analyze-security-policy.md)

### Playbooks
- [ExploitMitigations](../playbooks/ExploitMitigations.md)
- [Mitigations](../playbooks/Mitigations.md)
- [ProcessProtection](../playbooks/ProcessProtection.md)

### Examples
- [code-integrity](../examples/code-integrity.md)
- [mitigations](../examples/mitigations.md)
- [protected-process](../examples/protected-process.md)

### References
- [references](../references/references.md)

### Rules
- [mitigation-guidelines](../rules/mitigation-guidelines.md)

### Prompts
- [code-integrity-analysis](../prompts/code-integrity-analysis.md)
- [mitigations-analysis](../prompts/mitigations-analysis.md)
- [protected-process-analysis](../prompts/protected-process-analysis.md)

### Checklists
- [checklist](../checklists/checklist.md)

