---
title: Playbook: Unreal Engine Analysis
skill: playbooks
category: 
difficulty: intermediate
tags: [pe, unreal]
updated: 2026-07-05
---
# Playbook: Unreal Engine Analysis

Objective: Recover core Unreal Engine runtime structures, enable object inspection, and generate an SDK for analysis and tooling.

## Steps

1. Find `GWorld`, `GNames`, and `GUObjectArray` via string references, pattern-scans, or exported symbols.
2. Validate object enumeration by iterating `GUObjectArray` and reading object names through `GNames`.
3. Recover `UObject` layout by observing offsets for `Name`, `Class`, and object properties.
4. Locate `ProcessEvent` and confirm signature to intercept events safely.
5. Generate SDK headers for `UObject` and frequently-used engine types.
6. Identify gameplay-relevant objects (e.g., `PlayerController`) and validate offsets.

## Tools

- IDA/Ghidra with UE plugins, runtime dumping and pattern-scanning tools.

## Verification Checklist

- [ ] `GWorld`/`GNames` located and validated.
- [ ] `UObject` layout matches runtime enumeration.
- [ ] `ProcessEvent` signature validated.

