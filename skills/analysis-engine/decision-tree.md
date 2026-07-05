Decision Trees for Analysis

Purpose: Provide clear, structured decision paths to guide verification and action choices.

Structure
- Nodes: questions or checks (binary or multi-way).
- Edges: actions or next checks depending on node outcome.
- Leaves: recommended action or conclusion with required evidence and confidence level.

Design principles
- Keep nodes atomic and testable (yes/no or small enumerations).
- Prefer high-impact, low-cost checks earlier in the tree.
- For each leaf, list required evidence and an explicit rollback or mitigation plan.

Example template
If X (observation)
  ↓
  Check A (testable)
    If true → Do B (action) and collect evidence E1
    Else → Do C and collect evidence E2

Application
- Build decision trees for common tasks (triage, verification, renaming decisions).
- Use decision-tree nodes to schedule verification steps by priority.

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
