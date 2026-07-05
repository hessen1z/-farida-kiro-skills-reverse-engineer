Hypothesis-Driven Analysis

Principles
- Do not assume without stating the assumption explicitly.
- Structure analysis as a pipeline: Observation → Explanations → Evidence for/against → Confidence → Next verification.

Required output format for any hypothesis evaluation:
1. Observation: precise, timestamped, and sourced.
2. Possible explanations: enumerate discrete, testable hypotheses.
3. Evidence supporting each: list direct and indirect evidence with provenance.
4. Evidence against each: explicitly record disconfirming facts.
5. Confidence: numeric or categorical score with reasoning about sources of uncertainty.
6. Next verification step: an action that will increase or decrease confidence measurably.

Operational rules
- Every hypothesis must include a falsification plan (what would disprove it).
- Prefer hypotheses that make specific, testable predictions over vague explanations.
- When multiple hypotheses tie, prefer the one with the least assumptions (Occam's Razor), but list assumptions explicitly.

Example template (to be used in reports):
Observation: <concise fact with source>
Hypotheses:
- H1: <statement>
  - Evidence for: <list>
  - Evidence against: <list>
  - Confidence: <%> (rationale)
  - Next step: <verification action>
- H2: ...

## Related Material

- Skill overview: [skill.md](skill.md)
## Practical Guidance

- Start from the concrete objective and define the expected outcome before applying the workflow.
- Use the related examples, recipes, playbooks, and references as the first implementation reference.
- Keep the guidance grounded in the surrounding skill context and verify the result with available evidence.
- Favor practical, maintainable steps over abstract theory when the document is used in real work.
## Verification Checklist

- Confirm that the main objective is clear and the workflow is actionable.
- Ensure the document points to the most relevant examples, recipes, or playbooks.
- Validate that the terminology is consistent with the rest of the skill.
- Check that the practical guidance is specific enough to be used without further interpretation.
