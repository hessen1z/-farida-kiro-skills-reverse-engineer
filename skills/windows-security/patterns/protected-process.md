# Protected Process Pattern

## Pattern Name
Protected Process / Protected Process Light (PPL)

## Problem
Detect processes that enforce kernel-enforced protection and deny unauthenticated or untrusted access.

## Context
Windows enforces protected process semantics to prevent debugging, dumping, and tampering for security-sensitive processes.

## Recognition
- process names indicating security services or anti-malware engines.
- denied `DEBUG_PROCESS` or `PROCESS_VM_READ` access attempts.
- `Procexp`, `Taskmgr`, or other tools identify process protection levels.

## Evidence
- `STATUS_ACCESS_DENIED` from handle open attempts.
- protected process object attributes in OS structures.
- absence of standard debugger attachments and memory enumeration.

## Resolution / Action
- analyze process protection attributes rather than trying direct debugging.
- use inspection of loaded modules, IPC, and kernel-side enforcement paths.
- treat protected processes as guarded runtime components with restricted interfaces.

## Notes
- PPL may allow restricted access to trusted signed processes only.
- Protected process restrictions are enforced by the kernel, not by the process itself.

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

