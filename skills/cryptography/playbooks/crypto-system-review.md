---
title: Cryptographic System Review Playbook
skill: cryptography
category: playbooks
difficulty: intermediate
tags: [pe, cryptography, gui]
updated: 2026-07-05
---
# Cryptographic System Review Playbook

## Goal
Review cryptographic subsystems for correct algorithm choice, key management, and trust boundaries.

## Steps
1. Identify cryptographic primitives and APIs in use.
2. Review key generation, storage, and lifecycle handling.
3. Inspect signature and certificate validation paths.
4. Verify secure channel establishment and handshake behavior.
5. Validate hash usage and integrity checks.

## Focus Areas
- algorithm selection and key size
- key lifecycle and storage
- signature/certificate handling
- secure channel termination

## Actions
- Trace data flows through encryption and signing operations.
- Compare actual implementation against algorithm best practices.
- Identify misuse of cryptographic primitives or weak defaults.
- Ensure error handling does not bypass validation.

## Cross References
- `../recipes/analyze-encryption.md`
- `../recipes/analyze-certificate-chain.md`
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
- [analyze-certificate-chain](../recipes/analyze-certificate-chain.md)
- [analyze-encryption](../recipes/analyze-encryption.md)
- [analyze-hash](../recipes/analyze-hash.md)

### Playbooks
- [analyze-secure-protocol](analyze-secure-protocol.md)
- [developer-crypto-audit](developer-crypto-audit.md)
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

