---
title: Cryptography Audit Checklist
skill: cryptography
category: checklists
difficulty: intermediate
tags: [pe, cryptography, gui]
updated: 2026-07-05
---
# Cryptography Audit Checklist

- [ ] Identify all cryptographic primitives used by the system.
- [ ] Confirm secure algorithm selection and key lengths.
- [ ] Validate key storage and lifecycle management.
- [ ] Check signature and certificate verification logic.
- [ ] Verify authenticated encryption or MAC usage for integrity.
- [ ] Ensure sensitive data is not leaked through logs or error messages.
- [ ] Confirm error handling does not bypass security checks.

## Related Material

### Knowledge
- [asymmetric-cryptography](../knowledge/asymmetric-cryptography.md)
- [certificate-pki](../knowledge/certificate-pki.md)
- [cryptography-fundamentals](../knowledge/cryptography-fundamentals.md)

### Patterns
- [certificate-validation](../patterns/certificate-validation.md)
- [crypto-initialization](../patterns/crypto-initialization.md)
- [crypto-patterns](../patterns/crypto-patterns.md)

### Recipes
- [analyze-certificate-chain](../recipes/analyze-certificate-chain.md)
- [analyze-encryption](../recipes/analyze-encryption.md)
- [analyze-hash](../recipes/analyze-hash.md)

### Playbooks
- [analyze-secure-protocol](../playbooks/analyze-secure-protocol.md)
- [crypto-system-review](../playbooks/crypto-system-review.md)
- [developer-crypto-audit](../playbooks/developer-crypto-audit.md)

### Examples
- [cng-aes-encrypt](../examples/cng-aes-encrypt.md)
- [cryptoapi-hash-sign](../examples/cryptoapi-hash-sign.md)

### References
- [references](../references/references.md)

### Rules
- [cryptography-guidelines](../rules/cryptography-guidelines.md)

### Prompts
- [crypto-analysis](../prompts/crypto-analysis.md)
- [secure-implementation-checklist](../prompts/secure-implementation-checklist.md)
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
