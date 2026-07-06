---
title: Repository Architecture
skill: root
category: 
difficulty: intermediate
tags: [pe, loader, malware, networking, gui, kernel]
updated: 2026-07-05
---
# Repository Architecture

## Purpose
This repository separates domain expertise from shared infrastructure so that knowledge can be browsed, maintained, and extended without mixing content types or responsibilities.

## Architectural Layers

### 1. Domain Skills
A domain skill is a top-level folder that contains a skill manifest and domain-specific content. These folders are the primary units of knowledge and should remain focused on a specific technical area such as binary analysis, networking, malware analysis, or kernel internals.

### 2. Shared Infrastructure
Shared infrastructure contains reusable repository assets such as templates, editorial guidance, cross-domain patterns, and support tooling. These folders are not standalone domain skills and should not be treated as such by loaders or selection logic.

### 3. Release Outputs
Release artifacts, if present, should be kept outside the library content tree. This preserves the content layout for authors and keeps packaging output separate from the knowledge base.

## Separation Rules
- A skill must be domain-oriented and should include a skill manifest.
- Shared infrastructure may contain reusable content and templates, but it should not claim domain expertise on its own.
- Release outputs should remain isolated from day-to-day content editing.

## Content Model
Each skill typically uses a consistent content model:
- knowledge for concepts and architecture
- patterns for recurring technical signatures
- recipes for task-oriented procedures
- playbooks for operational workflows
- examples and snippets for practical implementation
- prompts, rules, and checklists for review and quality control

## Editorial Expectations
- Documents should be specific, well-structured, and actionable.
- Practical guidance and validation steps should be present where they improve usability.
- Cross-links should point to the most relevant neighboring content rather than duplicating it.

## Agent Loading Guidance
Agents should use the repository metadata in [skill-selection.md](skill-selection.md), [skill-priority.md](skill-priority.md), and [skill-map.md](skill-map.md) to identify appropriate skills rather than infer structure from folder names alone.

## Stability Principles
The repository structure is intended to stay stable as new topics are added. New content should preserve the boundary between domain skills and shared support assets, and it should fit the existing documentation conventions.