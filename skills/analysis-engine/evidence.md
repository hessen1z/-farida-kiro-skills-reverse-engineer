Evidence Handling and Scoring

Evidence taxonomy
- Direct evidence: observation that directly demonstrates a fact (e.g., a memory read showing a value).
- Indirect evidence: supports a fact through inference (e.g., correlated logs, heuristics).
- Strong evidence: high-fidelity, low-noise, independent source.
- Weak evidence: noisy, easily confounded, or from a single low-trust source.
- Conflicting evidence: mutually incompatible facts; treat as a sign of error or additional complexity.
- Missing evidence: when a key expected observation is absent; record explicitly.

Evidence ranking and scoring
- Attributes to record per evidence item: type, source, timestamp, confidence, independence (is it independent from other evidence?), and relevance.
- Scoring heuristic (0–1): start with base trust (source reliability), multiply by signal quality, multiply by independence factor.
- Aggregation: for a hypothesis, combine evidence scores using a weighted sum or Bayesian update; record the method used.

Conflicts and reconciliation
- When evidence conflicts, do not discard either item. Instead:
  1. Re-validate both sources.
  2. Check for contextual explanations (time variance, sampling error).
  3. If irreconcilable, prefer direct over indirect, stronger over weaker, and explicitly note the contradiction in the report.

Provenance and auditability
- For every evidence item, record where it came from (file, API, command, timestamp, user). This allows later verification and error analysis.

Evidence scoring example
- Direct memory read of pointer to function: base trust 0.9, quality 0.95, independence 1.0 → score 0.855
- Heuristic match to pattern in disassembly: base trust 0.6, quality 0.7, independence 0.8 → score 0.336

Use cases
- Ranking competing hypotheses: sum evidence scores supporting each, penalize for contradictory evidence.
- Prioritizing verification steps: choose actions that most increase total evidence score per unit cost.

## Related Material

- Skill overview: [skill.md](skill.md)

