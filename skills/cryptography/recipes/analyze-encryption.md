---
title: Analyze Encryption Recipe
skill: cryptography
category: recipes
difficulty: intermediate
tags: [pe, cryptography, gui]
updated: 2026-07-05
---
# Analyze Encryption Recipe

## Goal
Review encryption use and verify that the algorithm, mode, and key management align with security requirements.

## Steps
1. Identify whether symmetric or asymmetric encryption is used.
2. Confirm algorithm details: AES, ChaCha20, RSA, ECC.
3. Check mode of operation and padding.
4. Verify key length, randomness, and derivation process.
5. Look for hard-coded keys, weak entropy, or reuse of IVs.

## Focus Areas
- key generation and storage
- algorithm selection and mode
- initialization vector / nonce handling
- encryption boundaries and authenticated encryption

## Cross References
- `../patterns/crypto-initialization.md`
- `../patterns/key-management.md`

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
- [analyze-certificate-chain](analyze-certificate-chain.md)
- [analyze-hash](analyze-hash.md)
- [analyze-key-management](analyze-key-management.md)

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

### Checklists
- [cryptography-audit-checklist](../checklists/cryptography-audit-checklist.md)
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
