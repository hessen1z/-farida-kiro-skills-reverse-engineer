---
title: checklists
skill: analysis-engine
category: 
difficulty: intermediate
tags: [pe, gui, elf]
updated: 2026-07-05
---
Reusable Checklists

Provide compact, actionable checklists for common analysis tasks. Use these as pre-flight checks before producing conclusions.

Binary Analysis
- [ ] Confirm file integrity and basic PE metadata recorded.
- [ ] Enumerate imports/exports and record suspicious families.
- [ ] Scan for RTTI/strings/known patterns.
- [ ] Produce initial hypotheses and evidence list.

Crash Analysis
- [ ] Reproduce crash with controlled input.
- [ ] Collect crash dump and stack trace.
- [ ] Record register state and memory around instruction pointer.
- [ ] Generate hypotheses on root cause and verify with minimal test.

Memory Analysis
- [ ] Identify target process and module bases.
- [ ] Enumerate writable/executable pages.
- [ ] Locate candidate pointers and validate dereferences.
- [ ] Record provenance for each read.

Class Recovery
- [ ] Scan for COL / RTTI entries.
- [ ] Map vtables to TypeDescriptor names when possible.
- [ ] Group methods by vtable slot and cross-check calls.
- [ ] Verify using small unit tests or runtime checks.

RTTI Recovery
- [ ] List candidate COLs and validate pSelf values.
- [ ] Extract TypeDescriptor names and demangle.
- [ ] Reconstruct class hierarchy and record inheritance offsets.

SDK Generation
- [ ] Confirm recovered types are internally consistent.
- [ ] Generate headers with comment blocks listing evidence and confidence.
- [ ] Run a compile test if possible.
- [ ] Document unresolved ambiguities.

## Related Material

- Skill overview: [skill.md](skill.md)

