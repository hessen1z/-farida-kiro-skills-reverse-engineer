---
title: VBS Analysis Prompt
skill: hypervisor
category: prompts
difficulty: intermediate
tags: [pe, gui, kernel]
updated: 2026-07-05
---
# VBS Analysis Prompt

- Determine whether Virtualization-Based Security is active and how the secure kernel is isolated.
- Identify secure memory regions and verify that normal kernel code cannot access them.
- Explain how Credential Guard or other VBS features interact with Hyper-V.
- List the evidence and tools required to validate VBS policy enforcement.

## Related Material

### Knowledge
- [hyper-v-vbs](../knowledge/hyper-v-vbs.md)
- [hypervisor-architecture](../knowledge/hypervisor-architecture.md)
- [virtualization-fundamentals](../knowledge/virtualization-fundamentals.md)

### Patterns
- [ept-management](../patterns/ept-management.md)
- [hypervisor-patterns](../patterns/hypervisor-patterns.md)

### Recipes
- [analyze-ept](../recipes/analyze-ept.md)
- [analyze-hypervisor](../recipes/analyze-hypervisor.md)
- [analyze-vbs](../recipes/analyze-vbs.md)

### Playbooks
- [analyze-hyper-v](../playbooks/analyze-hyper-v.md)
- [analyze-hypervisor](../playbooks/analyze-hypervisor.md)
- [analyze-vbs](../playbooks/analyze-vbs.md)

### Examples
- [ept-layout](../examples/ept-layout.md)
- [vm-entry-exit](../examples/vm-entry-exit.md)

### References
- [references](../references/references.md)

### Rules
- [hypervisor-guidelines](../rules/hypervisor-guidelines.md)

### Prompts
- [hypervisor-analysis](hypervisor-analysis.md)
- [vmcs-analysis](vmcs-analysis.md)

### Checklists
- [checklist](../checklists/checklist.md)
## Practical Guidance

- Start from the core objective and define the expected outcome before applying the workflow.
- Use the related examples, recipes, and playbooks as the first implementation reference.
- Keep the advice grounded in the surrounding skill context and verify the result against the available evidence.
- Favor practical, maintainable steps over abstract theory when this document is used in real work.
## Verification Checklist

- Confirm that the main objective is clear and the workflow is actionable.
- Ensure the document points to the most relevant examples, recipes, or playbooks.
- Validate that the terminology is consistent with the rest of the skill.
- Check that the practical guidance is specific enough to be used without further interpretation.
