---
title: Playbook: Crash Analysis
skill: playbooks
category: 
difficulty: intermediate
tags: [pe, pdb, debug]
updated: 2026-07-05
---
# Playbook: Crash Analysis

Objective: Reproduce crashes reliably, obtain actionable crash dumps, and determine root cause with reproducible steps.

## Steps

1. Reproduce: capture exact steps, inputs, and environment needed to trigger the crash.
2. Capture dump: use ProcDump, Task Manager, or WinDbg to capture a full or triage dump.
3. Symbol setup: ensure PDBs or symbol server access for accurate stack traces.
4. Analyze stack: open dump in WinDbg, run `!analyze -v`, inspect call stacks and module offsets.
5. Inspect memory: examine local variables, heap, and object state at crash time.
6. Identify root cause: correlate instruction causing fault with source-level logic or data corruption.
7. Mitigate: prepare a fix or workaround; verify with regression tests.

## Tools

- WinDbg, ProcDump, Visual Studio debugger

## Verification Checklist

- [ ] Reproduction steps documented.
- [ ] Crash dump contains sufficient memory (full vs triage) to diagnose.
- [ ] Root cause identified and verified in a test harness.
