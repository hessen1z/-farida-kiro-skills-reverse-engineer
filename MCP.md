# MCP Readiness

## How to load skills
- Skills are organized under `skills/` by domain.
- Skill metadata is stored in each `skill.md` file.
- Use the `skills/meta` indexes to map knowledge, examples, playbooks, patterns, and recipes.

## How to query
- Query by task domain first (e.g. `reverse-engineering`, `anti-cheat`, `drivers`).
- Use playbooks as workflow entry points.
- Use recipes for concrete procedural steps.
- Use patterns for recurring problem structures.
- Use knowledge docs for foundational understanding.

## How routing works
- Router should match user intent to domain skills and cross-skill dependencies.
- Load only the skills needed for the task, not the whole repository.
- Prefer specialized skills over broad skills when possible.

## Priority
- Top priority: Stability, correctness, and minimal scope.
- Secondary priority: discoverability and relevance.
- Tertiary priority: examples and practical scenarios.

## Caching
- Cache parsed skill metadata and module indexes.
- Cache task-to-skill mappings for repeat queries.
- Cache recently used playbooks and recipes.
