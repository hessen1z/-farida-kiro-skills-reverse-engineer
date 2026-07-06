---
title: Cryptography Guidelines
skill: cryptography
category: rules
difficulty: intermediate
tags: [pe, cryptography, gui]
updated: 2026-07-05
---
# Cryptography Guidelines

## Principles
- Use well-vetted algorithms and avoid custom cryptography.
- Apply the right primitive for the right task: encryption for confidentiality, MACs for integrity, signatures for authenticity.
- Keep keys and secrets out of source code.

## Rules
- Do not use broken algorithms like MD5, SHA1, or RC4 in new designs.
- Enforce minimum key sizes: AES-128+ for symmetric, RSA-2048+/ECC-256+ for asymmetric.
- Use authenticated encryption modes such as AES-GCM or ChaCha20-Poly1305.
- Validate certificates, chains, and revocation status in secure channel setups.

## Analysis Rules
- Treat missing or invalid signature verification as a security failure.
- Confirm that key material is generated from secure entropy and not derived from predictable inputs.
- Require explicit error handling for cryptographic operations.

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

### Prompts
- [crypto-analysis](../prompts/crypto-analysis.md)
- [secure-implementation-checklist](../prompts/secure-implementation-checklist.md)

### Checklists
- [cryptography-audit-checklist](../checklists/cryptography-audit-checklist.md)

