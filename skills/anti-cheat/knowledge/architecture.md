# Anti-Cheat Architecture

## Overview

Anti-cheat systems combine detection, enforcement, and integrity monitoring to protect game clients from unauthorized modification. They often span user-mode clients, kernel-mode drivers, and cloud-based services.

## Core components

- user-mode monitors and injected DLLs
- kernel-mode drivers for process and memory observation
- secure launchers and bootstrapping code
- communication with game servers or anti-cheat services

## Runtime flow

Typical anti-cheat flow:
1. secure game launch and process validation
2. module and memory scanning for injected code
3. hook installation or behavior monitoring
4. cheat detection and response action

## Notes

- Modern anti-cheat often uses kernel drivers to bypass user-mode limitations.
- Many systems also validate game assets and process state before allowing gameplay.

## References

- Anti-cheat system design papers
- Windows kernel security documentation

## Related Material

### Patterns
- [driver-enforcement](../patterns/driver-enforcement.md)
- [hook-detection](../patterns/hook-detection.md)
- [memory-scan](../patterns/memory-scan.md)

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
