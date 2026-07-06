---
title: Developer Crypto Audit Playbook
skill: cryptography
category: playbooks
difficulty: intermediate
tags: [pe, cryptography, gui]
updated: 2026-07-05
---
# Developer Crypto Audit Playbook

## Goal
Provide a developer-focused audit for crypto usage in code, libraries, and system components.

## Steps
1. Inventory all cryptographic APIs and algorithms in the codebase.
2. Identify hard-coded keys, salts, or protocol parameters.
3. Validate correct use of modern primitives and avoid deprecated algorithms.
4. Check for secure error handling and side-channel protections.
5. Document recommendations for replacing insecure constructs.

## Focus Areas
- deprecated algorithms and insecure modes
- hard-coded secrets
- error handling and side channels
- safe API usage

## Actions
- Search for inline keys, salts, and algorithm selections.
- Review code paths where untrusted data is hashed or signed.
- Ensure random values use secure entropy sources.
- Recommend stronger defaults for algorithm and key sizes.

## Cross References
- `../patterns/crypto-initialization.md`
- `../patterns/signature-verification.md`
- `../rules/cryptography-guidelines.md`

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
- [analyze-secure-protocol](analyze-secure-protocol.md)
- [crypto-system-review](crypto-system-review.md)
- [secure-transport-playbook](secure-transport-playbook.md)

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

