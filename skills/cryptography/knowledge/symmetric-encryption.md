# Symmetric Encryption Knowledge

## Overview
Symmetric encryption uses the same secret key for encryption and decryption. It is the primary method for protecting data confidentiality in high-throughput systems.

## Common Algorithms
- AES (Advanced Encryption Standard)
- 3DES (deprecated)
- ChaCha20
- Salsa20

## Modes of Operation
- ECB: insecure due to deterministic blocks.
- CBC: requires IVs and padding.
- GCM: authenticated encryption with associated data.
- CTR: stream-like mode, requires unique nonces.

## Key Management
- Use random keys generated from secure entropy.
- Avoid key reuse across different contexts.
- Protect keys in memory and consider OS key stores or hardware-backed storage.

## Practical Applications
- encrypting files and data at rest
- securing transport payloads with TLS or VPN tunnels
- creating fast message encryption for games and network channels

## Common Mistakes
- reusing IVs or nonces with the same key
- using ECB mode for sensitive data
- relying on encryption without integrity checks

## Cross-links
- `../patterns/crypto-initialization.md`
- `../recipes/analyze-encryption.md`

## Related Material

### Knowledge
- [asymmetric-cryptography](asymmetric-cryptography.md)
- [certificate-pki](certificate-pki.md)
- [cryptography-fundamentals](cryptography-fundamentals.md)

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

### Checklists
- [cryptography-audit-checklist](../checklists/cryptography-audit-checklist.md)

