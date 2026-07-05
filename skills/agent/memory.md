Memory Guidance

Purpose: Define how agents should use ephemeral and persistent memory when operating on the library.

Guidelines
- Store only non-sensitive metadata in persistent memory (task state, plan progress).
- Use ephemeral memory for intermediate artifacts and temporary evidence caches.
- Always record provenance (file paths, timestamps, commands) for persistent memory entries.

Retention
- Short-lived session memory should prune after task completion.
- Repository-scoped memory may persist across sessions for indexing and review.
