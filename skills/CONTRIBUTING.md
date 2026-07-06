---
title: Contributing to AI Security Library
skill: root
category: 
difficulty: intermediate
tags: [pe, gui]
updated: 2026-07-05
---
# Contributing to AI Security Library

## Overview
This document describes how to contribute safely and consistently to the repository while preserving the separation between domain skills, shared infrastructure, and release outputs.

## Repository Structure
- Skill folders contain domain-specific knowledge and supporting assets.
- Shared infrastructure folders such as [shared](shared), [content-template](content-template), [templates](templates), [patterns](patterns), [playbooks](playbooks), [snippets](snippets), and [tools](tools) provide reusable support content.
- Release artifacts, if present, should remain outside the library content tree.

## Contribution Workflow
1. Open or update an issue for the change you intend to make.
2. Create a branch or work from the current repository state.
3. Implement the change in the appropriate folder and keep it scoped to the intended purpose.
4. Verify that the documentation, examples, or cross-links are updated as needed.
5. Submit a pull request with a concise summary and references to affected files.

## Adding New Skills
- Create a new top-level skill folder only when it represents a distinct domain of knowledge.
- Each new skill should include a skill manifest and supporting content directories.
- Do not add infrastructure folders as new skills.

## Documentation Standards
- Use [content-template](content-template) and [writing-guidelines](writing-guidelines) as the starting point for new content.
- Prefer clarity, precision, and practical guidance over filler text.
- Keep terminology consistent with the surrounding skill and the repository conventions.

## Review Checklist
- Confirm the change is placed in the right content category.
- Verify that any new or modified skill includes the expected supporting folders.
- Check that links and references still resolve sensibly.
- Ensure the update does not blur the boundary between a skill and shared infrastructure.
- Preserve repository organization unless the change explicitly improves it.

## Communication Expectations
- When a change is structural or cross-cutting, describe the rationale clearly.
- Avoid broad reorganization without a clear benefit to maintainability or clarity.