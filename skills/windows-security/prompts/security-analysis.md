---
title: Windows Security Analysis Prompt
skill: windows-security
category: prompts
difficulty: intermediate
tags: [pe, windows, gui, debug]
updated: 2026-07-05
---
# Windows Security Analysis Prompt

## Prompt

You are a Windows security analyst. Given a protected process or binary, identify the security mitigations and runtime protections in effect. Recommend an analysis plan that accounts for process protection, code integrity, and exploit mitigation behavior.

## Guidance

- Determine which Windows mitigations are enabled for the target.
- Inspect code and PE metadata for DEP, ASLR, and CFG support.
- Highlight restrictions on debugging and instrumentation.
- Provide steps to verify protection enforcement at runtime.

## Related Material

### Knowledge
- [code-integrity](../knowledge/code-integrity.md)
- [mitigations](../knowledge/mitigations.md)
- [protected-process](../knowledge/protected-process.md)

### Patterns
- [aslr](../patterns/aslr.md)
- [cfg](../patterns/cfg.md)
- [code-signing](../patterns/code-signing.md)

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
- [code-integrity-analysis](code-integrity-analysis.md)
- [mitigations-analysis](mitigations-analysis.md)
- [protected-process-analysis](protected-process-analysis.md)

### Checklists
- [checklist](../checklists/checklist.md)
## Practical Guidance

- Start from the concrete objective and define the expected outcome before applying the workflow.
- Use the related examples, recipes, playbooks, and references as the first implementation reference.
- Keep the guidance grounded in the surrounding skill context and verify the result with available evidence.
- Favor practical, maintainable steps over abstract theory when the document is used in real work.
## Verification Checklist

- Confirm that the main objective is clear and the workflow is actionable.
- Ensure the document points to the most relevant examples, recipes, or playbooks.
- Validate that the terminology is consistent with the rest of the skill.
- Check that the practical guidance is specific enough to be used without further interpretation.
