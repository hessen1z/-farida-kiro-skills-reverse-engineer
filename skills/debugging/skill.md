---
name: Debugging
version: 1.0
priority: critical
requires:
  - shared
  - analysis-engine
  - windows-internals
  - assembly
  - cpp
tags:
  - debugging
  - crash
  - win32
  - kernel
  - diagnostics
description: Core debugging skill covering Windows and game debugging, crash dump analysis, kernel and driver debugging, remote tracing, and debug metadata recovery.
---

# Debugging Skill

## Purpose
Provide comprehensive guidance for debugging native Windows applications, games, and drivers. This skill covers tools, breakpoints, memory inspection, crash dumps, symbols, kernel debugging, and defensive debug engineering.

## What this skill provides
- Deep debugging architecture and memory layout knowledge.
- Workflows for analyzing crashes, exceptions, dumps, and protected processes.
- Patterns for recognizing breakpoint, exception, and stack corruption artifacts.
- Recipes for recovering call stacks, analyzing dumps, and debugging drivers.
- Examples for WinDbg, x64dbg, IDA Debugger, Visual Studio, and scripting.

## Prerequisites
- `shared` for documentation templates.
- `analysis-engine` for evidence-driven analysis.
- `windows-internals` for OS loader and debugging semantics.
- `assembly` for instruction-level patterns.
- `cpp` for practical examples and tool integration.

## Used by
- `reverse-engineering`
- `binary-analysis`
- `game-security`
- `anti-cheat`

## Related Skills
- `windows-internals` — OS-level debug behavior and kernel interaction.
- `reverse-engineering` — function recovery, symbols, and crash analysis.
- `binary-analysis` — PE and runtime metadata examination.

## Entry Conditions
- A native Windows process or dump needs debugging.
- A crash, exception, or protected process behavior requires analysis.
- Kernel debugging and driver diagnosis are required.

## Exit Conditions
- The root cause of a crash or hang is identified.
- Call stacks are recovered and validated.
- Debugger workflows are documented for application, game, or driver scenarios.
- Evidence is preserved and debugging artifacts are cataloged.

## Typical Workflow
1. Identify the target: user-mode process, game client, or kernel/driver.
2. Collect symbols, configure the debugger, and attach or load a dump.
3. Set breakpoints, inspect memory, and recover call stacks.
4. Analyze exceptions, thread states, and protection mechanisms.
5. Capture or analyze dumps and document findings.

## Notes
- This skill focuses on defensive and diagnostic debugging, not exploit development.
- Maintain production-quality documentation and cross-link to related skills.
- Use isolated test environments for live debugging of games, drivers, and security-sensitive code.

## Related Material

- Knowledge: [anti-debugging](knowledge/anti-debugging.md)
- Patterns: [breakpoint](patterns/breakpoint.md)
- Recipes: [analyze-crash](recipes/analyze-crash.md)
- Playbooks: [Crash](playbooks/Crash.md)
- Examples: [kernel-debugging](examples/kernel-debugging.md)
- References: [references](references/references.md)
- Rules: [debugging-principles](rules/debugging-principles.md)
- Prompts: [debug-process](prompts/debug-process.md)
- Checklists: [checklist](checklists/checklist.md)

