---
title: Asymmetric Cryptography Knowledge
skill: cryptography
category: knowledge
difficulty: intermediate
tags: [pe, cryptography, gui, elf]
updated: 2026-07-05
---
# Asymmetric Cryptography Knowledge

## Overview
Asymmetric cryptography uses key pairs: a public key for verification or encryption and a private key for decryption or signing.

## Core Algorithms
- RSA
- ECC (Elliptic Curve Cryptography)
- DSA
- Diffie-Hellman key exchange

## Use Cases
- digital signatures
- key agreement and exchange
- certificate-based authentication
- encrypting small payloads or session keys

## Properties
- more computationally expensive than symmetric algorithms
- public/private separation enables secure key distribution
- requires strong randomness for key generation and nonces

## Practical Guidance
- use RSA for legacy compatibility, ECC for modern efficiency
- protect private keys with hardware or OS protection
- verify public keys from trusted sources rather than accepting arbitrary values

## Common Mistakes
- using short key lengths or weak curves
- encrypting large payloads directly with asymmetric keys
- failing to validate public key legitimacy in certificates

## Cross-links
- `../patterns/certificate-validation.md`
- `../recipes/analyze-signature.md`

## Related Material

### Knowledge
- [certificate-pki](certificate-pki.md)
- [cryptography-fundamentals](cryptography-fundamentals.md)
- [hashing-integrity](hashing-integrity.md)

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

## Practical Guidance

- Prefer established libraries and avoid implementing crypto primitives yourself.
- Use strong curves (e.g., Curve25519, P-256) and recommend key sizes per current guidelines.

## Tools & Validation

- Use OpenSSL or OS crypto APIs for interoperability and testing.
- Validate keys and signatures with test vectors and known-good implementations.

## Validation Checklist

- Ensure private keys are stored and accessed securely (HSM or OS-protected stores).
- Verify signature algorithms and key sizes meet current security requirements.

## Tools & Commands

- OpenSSL: `openssl genpkey`, `openssl pkey`, `openssl dgst -sign` for key and signature operations.
- Use `ssh-keygen` or platform key tooling to generate and inspect public/private key pairs.

## Validation Checklist (Detailed)

- Confirm keys validate against standard test vectors and interoperate with OpenSSL/OS APIs.
- Ensure key lifecycle policies (rotation, revocation) are documented and followed.

