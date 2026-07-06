---
title: Binary Checklist
skill: checklists
category: 
difficulty: intermediate
tags: [pe, driver, gui, kernel, dll]
updated: 2026-07-05
---
# Binary Checklist

## Objective
Use this checklist for a concise but reliable initial triage of a binary before deeper analysis.

## Preparation
- Capture the file hash and obtain the target architecture and build metadata.
- Identify the expected file format and packaging context.
- Note the environment or tools that will be used for the first pass.

## Execution Checklist
- [ ] Review the headers and section layout.
- [ ] Extract imports, exports, and strings.
- [ ] Note any obfuscation, packing, or anti-analysis indicators.
- [ ] Capture initial behavior observations in a controlled environment.
- [ ] Record any obvious anomalies that may require a closer look.

## Validation Checklist
- [ ] Findings are supported by evidence.
- [ ] The analysis notes are clear enough for handoff or further review.
- [ ] Any unresolved questions are explicitly called out.

## Documentation Checklist
- [ ] Record the tools and environment used.
- [ ] Note any caveats or unresolved questions.
- [ ] Link the notes to the relevant skills or examples when helpful.

## Completion Criteria
- The analyst has enough evidence to move to deeper static or dynamic analysis with a clear plan.

## Related Guidance
- See [dll.md](dll.md) for module-specific analysis.
- See [driver.md](driver.md) for kernel-mode-specific follow-up checks.
