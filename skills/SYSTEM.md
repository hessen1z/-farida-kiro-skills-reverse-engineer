---
title: System Overview
skill: root
category: 
difficulty: intermediate
tags: [pe, loader, gui]
updated: 2026-07-05
---
# System Overview

## Philosophy
This library is designed to separate domain knowledge from reasoning. Agents should prefer explicit evidence and verification over inference without provenance.

## Goals
- Provide a machine-readable index of capabilities, workflows, and patterns.
- Offer a single canonical source of truth for agent orchestration and policies.
- Ensure reproducible, auditable analysis outputs.

## Scope
- Includes skills, patterns, recipes, playbooks, examples, and documentation required for reverse engineering and allied analysis tasks.
- Does not include external tool binaries, private data, or unrelated domain knowledge.

## Core Operating Rules
- Read this file before loading any domain skill.
- Record provenance for every evidence item, including the file, command, and timestamp where it was obtained.
- Do not rename symbols or rewrite documentation without evidence and a verification plan.
- Prefer the smallest reasonable skill set that can support the task reliably.

## Skill Loading Order
1. Read this file and the metadata under [meta](meta).
2. Select skills using [skill-selection.md](skill-selection.md).
3. Load core skills such as [analysis-engine](analysis-engine/skill.md), [shared](shared/skill.md), and [reverse-engineering](reverse-engineering/skill.md) first, then add secondary skills as needed.
4. Use [skill-map.md](skill-map.md) and [skill-priority.md](skill-priority.md) to keep the plan scoped and consistent.

## Reasoning Process
Use the [analysis-engine](analysis-engine/skill.md) workflow: Observe → Hypothesize → Score Evidence → Verify → Conclude.
Maintain multiple hypotheses until verification sufficiently narrows the possibilities.

## Evidence Policy
- Classify evidence as direct, indirect, or inferred.
- Prefer independent corroboration before high-confidence claims.
- When evidence conflicts, validate both sources and record the discrepancy rather than silently discarding it.

## Naming and Documentation Policy
- Use semantic, descriptive names and avoid ambiguous temporary identifiers in final outputs.
- Record earlier names and rationale when changes are made.
- Reports should include a summary, evidence list, hypotheses considered, verification steps executed, confidence, and next actions.

## Verification Policy
- Every actionable recommendation should include at least one independent verification step.
- Prioritize verification methods by expected information gain and cost.
- If a conclusion cannot be verified, mark it as provisional rather than presenting it as fact.

## Reading Order for Agents
1. [SYSTEM.md](SYSTEM.md)
2. [meta](meta)
3. [skill-selection.md](skill-selection.md) and [skill-priority.md](skill-priority.md)
4. The relevant skill manifest files for the selected skills

## Appendix
- [meta](meta) contains machine-readable indexes for skills, workflows, patterns, and examples.
- [agent](agent) contains guidance for building loaders, planners, routers, validators, and reviewers.

## Practical Guidance
- Start from the specific question or failure mode and avoid broadening the scope prematurely.
- Prefer structured outputs that make the evidence trail visible to later reviewers.
- Use the repository’s support documents to keep content consistent and reusable.
