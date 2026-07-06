---
title: Driver Checklist
skill: checklists
category: 
difficulty: intermediate
tags: [pe, driver, gui, kernel, dll]
updated: 2026-07-05
---
# Driver Checklist

## Purpose
Use this checklist when analyzing a kernel-mode driver or related subsystem component.

## Preparation
- Record the driver name, service information, and target platform.
- Identify the expected execution context and any relevant OS or hardware dependencies.

## Review Checklist
- [ ] Review the PE structure and driver-specific metadata.
- [ ] Identify major entry points and dispatch routines.
- [ ] Check for IRP handling, device object setup, and callback registration.
- [ ] Note any suspicious or unusual kernel interactions.
- [ ] Capture the findings in a way that supports later handoff or deeper analysis.

## Validation Checklist
- [ ] Findings are supported by direct evidence.
- [ ] Any assumptions are clearly marked as provisional.

## Related Guidance
- See [dll.md](dll.md) for module-oriented analysis patterns.
- See [binary.md](binary.md) for general binary triage.
