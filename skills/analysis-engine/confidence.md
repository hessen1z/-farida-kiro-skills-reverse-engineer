---
title: confidence
skill: analysis-engine
category: 
difficulty: intermediate
tags: [pe, gui]
updated: 2026-07-05
---
Confidence Scoring Guidelines

Purpose: Provide a consistent interpretation of confidence levels for analysis outputs and recommended actions.

Confidence levels (examples and appropriate use)
- 99% — Near-certain: direct, high-quality evidence with independent corroboration. Use when action is urgent and low risk of false positive.
- 95% — Very high: strong direct evidence or multiple independent indirect items. Use for confident recommendations with minor verification.
- 80% — High: good evidence but with limited independence or potential confounders. Use for operational suggestions that should be briefly verified.
- 60% — Moderate: plausible but significant uncertainty; requires deliberate verification before important actions.
- 30% — Low: weak or ambiguous evidence; use for exploratory suggestions only, not decisions.
- 10–15% — Very low: near-random or speculative; flag as hypothesis for further data collection.

Scoring guidance
- Base score derived from aggregated evidence score (see `evidence.md`).
- Adjust for model/analyst bias and prior probability (document priors and adjustment rationale).
- Provide explicit rationale alongside numeric score: list the top 3 contributing evidence items and top 2 uncertainties.

Usage in reports
- Always publish confidence alongside conclusions.
- When confidence < 60%, include a short verification plan before taking irreversible actions.

## Related Material

- Skill overview: [skill.md](skill.md)

