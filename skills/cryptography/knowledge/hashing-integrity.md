# Hashing and Integrity Knowledge

## Overview
Hash functions map data to fixed-size digests. They are widely used for integrity checks, password hashing, and as components of digital signatures.

## Common Hash Algorithms
- SHA-256 / SHA-384 / SHA-512
- SHA-3 family
- BLAKE2

## Integrity vs Authentication
- hashes alone provide integrity detection but not authentication.
- use HMAC or authenticated encryption for message authentication.
- avoid using raw hashes for password storage or authorization decisions.

## Password and Key Derivation
- use PBKDF2, bcrypt, scrypt, or Argon2 for password hashing.
- use HKDF for key derivation from shared secrets.

## Practical Workflows
- compute digests over canonicalized data.
- compare digests in constant time when resisting timing attacks.
- include salts in password hashing to avoid dictionary precomputation.

## Common Mistakes
- treating MD5 or SHA1 as secure.
- using unsalted hashes for secrets.
- comparing digests with naive string equality in sensitive contexts.

## Cross-links
- `../recipes/analyze-hash.md`
- `../rules/cryptography-guidelines.md`

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

