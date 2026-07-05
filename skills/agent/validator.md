Validator

Purpose: Validate outputs, evidence, and naming decisions produced by skills.

Checks
- Evidence provenance exists and matches entries in `meta/knowledge-index.json` when referenced.
- Confidence scores accompany conclusions and include justification.
- Renaming follows `renaming.md` rules and includes verification steps.

Actions
- Reject outputs that lack provenance or required verification steps.
- Suggest minimal verification actions to raise confidence.
