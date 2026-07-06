# Retrieval Report

Generated from repository analysis and search-index verification.

- search-index documents: 502
- markdown files found: 504
- missing from index: 2
- extra in index: 0

## Missing from index
- METADATA_REPORT.md
- SEARCH_INDEX_REPORT.md

## Discoverability issues
- documents with no tags: 6
- documents with fewer than 2 tags: 18
- documents with no summary: 154
- documents with fewer than 5 keywords: 30
- documents with no explicitly linked related_documents: 42
- isolated documents (no inbound or outbound md links): 34

## Ambiguous titles
- "References" appears in 3 documents:
  - detection-engineering/references/references.md
  - malware-analysis/references/references.md
  - reverse-engineering/references.md
- "Content Template Skill" appears in 2 documents:
  - content-template/README.md
  - content-template/skill.md
- "Kernel Debugging Example" appears in 2 documents:
  - debugging/examples/kernel-debugging.md
  - kernel/examples/kernel-debugging.md
- "Debug Driver Recipe" appears in 2 documents:
  - debugging/recipes/debug-driver.md
  - drivers/recipes/debug-driver.md
- "Writing Guidelines Skill" appears in 2 documents:
  - writing-guidelines/README.md
  - writing-guidelines/skill.md

## Important validation
- search-index document paths were verified against disk files.
- Frontmatter metadata was verified for repository documents, excluding generated reports and .venv files.
- Related documents were inferred for docs missing explicit outbound links within the same skill.

## Recommendations
- Add explicit `Related Documents` sections to isolated documents in their Markdown content, especially root README/ARCHITECTURE and skill landing pages.
- Standardize document titles in duplicate title groups to reduce ambiguity for retrieval agents.
- Keep `tags` small and consistent by using the repository keyword set across skills.
- Use cross-skill references for shared concepts such as PE analysis, kernel debugging, anti-cheat, and Dear ImGui.