---
title: CryptoAPI Hash and Sign Example
skill: cryptography
category: examples
difficulty: intermediate
tags: [pe, cryptography, gui]
updated: 2026-07-05
---
# CryptoAPI Hash and Sign Example

## Overview
This example shows hashing a message and signing it with a CAPI private key.

## Steps
1. Acquire a cryptographic provider context.
2. Create a hash object for a secure digest algorithm.
3. Hash the input message and sign the digest.
4. Verify or export the signed data.

## Notes
- Use `CALG_SHA_256` or stronger, not MD5 or SHA1.
- Keep private keys protected and avoid exporting them when possible.
- Treat signature failures as critical validation errors.

## Cross References
- `../patterns/signature-verification.md`
- `../recipes/analyze-signature.md`

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
- [cng-aes-encrypt](cng-aes-encrypt.md)

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
