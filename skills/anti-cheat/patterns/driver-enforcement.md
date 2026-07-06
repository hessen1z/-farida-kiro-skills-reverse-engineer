---
title: Driver Enforcement Pattern
skill: anti-cheat
category: patterns
difficulty: intermediate
tags: [pe, windows, anti-cheat, driver, kernel]
updated: 2026-07-05
---
# Driver Enforcement Pattern

## Pattern Name
Kernel-mode enforcement driver

## Problem
Detect kernel drivers that enforce anti-cheat policies by monitoring or controlling processes and memory.

## Context
Anti-cheat drivers can perform low-level monitoring and response actions that are impossible in user-mode.

## Recognition
- driver object creation and device dispatch routines
- process callback registration (`PsSetCreateProcessNotifyRoutine`)
- memory and handle inspection APIs
- kernel communication interfaces with the user-mode client

## Evidence
- driver entry points and IRP handlers for security operations
- callback functions associated with process or thread events
- data structures that store process or module state

## Resolution / Action
- trace enforcement logic from kernel callbacks to user-mode signals
- determine whether the driver blocks or reports suspicious activity
- identify protected device interfaces used by the client

## Notes
- Kernel-mode drivers require signed drivers on modern Windows builds.
- Driver enforcement may include secure communications with a user-mode service.

## References
- Windows kernel driver development and security documentation

## Related Material

### Knowledge
- [architecture](../knowledge/architecture.md)

### Patterns
- [hook-detection](hook-detection.md)
- [memory-scan](memory-scan.md)

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

