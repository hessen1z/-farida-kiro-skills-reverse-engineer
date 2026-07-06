---
title: Memory Guidance
skill: agent
category: 
difficulty: intermediate
tags: [pe, gui]
updated: 2026-07-05
---
# Memory Guidance

## Purpose
This document defines how an agent should manage temporary and durable state while operating on the repository. The goal is to preserve useful context without turning memory into an unstructured archive.

## Core Guidelines
- Store only non-sensitive metadata in persistent memory, such as task state, plan progress, and review notes.
- Use ephemeral memory for intermediate artifacts, scratch reasoning, and temporary evidence caches.
- Record provenance for persistent memory entries, including the relevant file, command, or source artifact.

## Retention Guidance
- Short-lived session memory should be pruned after the task completes or when it becomes obsolete.
- Repository-scoped memory may persist across sessions when it helps with indexing, review, and repeatability.

## Practical Guidance
- Keep memory entries concise and specific so they remain easy to audit later.
- Avoid storing large binaries, raw tool output, or duplicate evidence when a pointer to the source artifact is enough.
- When a decision is revisited, use the stored context to explain why the earlier conclusion was made.

## Related Guidance
- See [planner.md](planner.md) for how plans are formed from stored context.
- See [validator.md](validator.md) for how outputs and evidence are checked.
