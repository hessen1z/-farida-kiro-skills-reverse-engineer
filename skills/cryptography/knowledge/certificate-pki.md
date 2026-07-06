---
title: Certificates and PKI Knowledge
skill: cryptography
category: knowledge
difficulty: intermediate
tags: [pe, cryptography, gui, elf]
updated: 2026-07-05
---
# Certificates and PKI Knowledge

## Overview
Public Key Infrastructure (PKI) provides the framework for certificate issuance, validation, and trust in digital communications.

## Certificate Components
- subject and issuer names
- public key and algorithm
- validity period
- extensions such as key usage and subject alternative names

## Trust Model
- trust is anchored at root certificates.
- intermediate issuers chain trust from leaf certificates to roots.
- revocation mechanisms such as OCSP and CRL validate current status.

## Practical Workflows
- inspect certificate chains in secure sessions.
- confirm the certificate matches the requested hostname or service.
- validate extension constraints and intended purpose.

## Common Mistakes
- accepting self-signed or expired certificates without warning.
- ignoring revocation checks for high-value sessions.
- using certificates with weak signature algorithms.

## Cross-links
- `../patterns/certificate-validation.md`
- `../recipes/analyze-certificate-chain.md`

## Related Material

### Knowledge
- [asymmetric-cryptography](asymmetric-cryptography.md)
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

- Always validate full certificate chains and consider OCSP stapling or CRL checks for critical paths.
- Verify certificate extensions and intended key usages before trusting a certificate for a purpose.

## Tools & Commands

- `openssl s_client -connect host:port -showcerts` to inspect TLS chains.
- Use certificate parsers (`certutil`, `openssl`) to examine extensions and validity.

## Validation Checklist

- Confirm the certificate chain roots to a trusted CA and that no intermediate is revoked.
- Verify hostnames and SAN entries match service expectations.

