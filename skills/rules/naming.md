---
title: Naming Rules
skill: rules
category: 
difficulty: intermediate
tags: [pe, gui]
updated: 2026-07-05
---
# Naming Rules

## Purpose
These rules define how recovered symbols and structures should be named once the surrounding evidence is strong enough to support a meaningful identifier.

## Expectations
- Prefer descriptive, domain-specific names that communicate intent.
- Rename symbols only when the recovered context supports the new name.
- Preserve the original identifier in notes or provenance when a rename is performed.

## Practical Guidance
- Use a pattern such as `PlayerController_Update` for functions when the role is clear.
- Avoid vague names such as `tempvar1` or `sub_14001` in final documentation unless they are preserved for provenance.
- Keep naming consistent across similar code paths, classes, and modules.

## Related Guidance
- See [style.md](style.md) for broader writing and clarity expectations.
- See [documentation.md](documentation.md) for how renamed symbols should be described in notes.
