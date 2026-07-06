---
title: reasoning
skill: analysis-engine
category: 
difficulty: intermediate
tags: [pe, gui, debug]
updated: 2026-07-05
---
Reasoning Methodologies

Purpose: Define clear, reusable reasoning techniques an analysis agent must apply before drawing conclusions. Each technique includes when to use it, steps, and quick heuristics for application.

Bottom-up reasoning
- Description: Build conclusions from observed data and low-level facts upward to generalizations.
- When to use: Raw observations, sensor data, logs, and when verifying hypotheses emergently.
- Steps:
  1. Collect atomic observations.
  2. Aggregate related observations.
  3. Form intermediate patterns.
  4. Generalize to a higher-level claim with stated assumptions.
- Heuristics: prefer direct evidence; annotate uncertainty at each aggregation step.

Top-down reasoning
- Description: Start with a hypothesis or desired goal and derive what observations would support or refute it.
- When to use: Goal-driven tasks, planning, narrow-scope verification.
- Steps:
  1. State hypothesis precisely.
  2. Derive observable consequences and required evidence.
  3. Test for those consequences; revise hypothesis if absent.
- Heuristics: limit branching by focusing on high-impact consequences first.

Evidence-driven reasoning
- Description: Center reasoning on evidence quality; adjust conclusion strength by evidence ranking.
- When to use: Any analytic workflow; always prefer evidence-driven over intuition.
- Steps:
  1. Catalog evidence with provenance and type (direct/indirect).
  2. Score evidence strength and conflicts.
  3. Weight hypotheses by cumulative evidence score.
- Heuristics: mark inference steps where evidence is missing or weak.

Constraint solving
- Description: Treat analysis as a constraint satisfaction problem where observations impose constraints on possible explanations.
- When to use: Structural recovery tasks, parameter estimation, feasibility checks.
- Steps:
  1. Translate observations into constraints.
  2. Apply constraint propagation and pruning.
  3. Enumerate solutions consistent with all constraints; rank by simplicity and evidence.
- Heuristics: detect unsatisfiable constraints early and report contradictions explicitly.

Elimination (abductive and deductive exclusion)
- Description: Remove explanations that are inconsistent with established facts; prefer minimal remaining explanations.
- When to use: Narrowing hypothesis spaces, debugging.
- Steps:
  1. For each candidate, check for contradictions with strong evidence.
  2. Eliminate inconsistent candidates.
  3. Re-evaluate remaining candidates and iterate.
- Heuristics: track which evidence caused an elimination to maintain auditability.

Pattern matching
- Description: Recognize recurring structures in observations and map them to known templates.
- When to use: Fast identification, classification, triage.
- Steps:
  1. Normalize observed data.
  2. Match against a curated pattern library with exact and fuzzy matching.
  3. Report matches with confidence and variation notes.
- Heuristics: distinguish exact matches from heuristic matches; require verification for heuristic matches.

Bayesian thinking
- Description: Represent belief states numerically and update them with new evidence using probability rules.
- When to use: Probabilistic fusion of uncertain evidence, combining weak signals.
- Steps:
  1. Initialize priors for hypotheses.
  2. For each evidence piece, compute likelihood ratios and update posterior probabilities.
  3. Normalize and interpret posteriors; use thresholds for decisions.
- Heuristics: record priors and likelihood assumptions; avoid overconfident priors without justification.

Multi-hypothesis analysis
- Description: Maintain multiple competing hypotheses in parallel, comparing evidence for and against each.
- When to use: Ambiguous situations, early-stage investigations.
- Steps:
  1. Enumerate plausible hypotheses explicitly.
  2. For each, list expected evidence and contradictions.
  3. Score and rank hypotheses; schedule verification steps for the highest-ranking ones.
- Heuristics: never collapse to a single hypothesis prematurely; keep at least two alternatives while evidence is insufficient.

## Related Material

- Skill overview: [skill.md](skill.md)

