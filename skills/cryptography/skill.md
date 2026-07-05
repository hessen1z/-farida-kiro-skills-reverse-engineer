---
name: Cryptography
version: 1.0
priority: critical
requires:
  - shared
  - windows-internals
  - cpp
tags:
  - crypto
  - security
  - encryption
description: Core cryptography skill covering symmetric and asymmetric algorithms, hashing, digital signatures, Windows CryptoAPI/CNG, and secure communication.
---

# Cryptography Skill

## Purpose
Provide an operational reference for cryptographic systems, secure storage, authentication, and Windows crypto APIs. This skill focuses on correct algorithm usage, key management, integrity verification, and secure communication.

## What this skill provides
- Knowledge of symmetric and asymmetric encryption, block and stream ciphers, hashes, certificates, PKI, and secure protocols.
- Patterns for cryptographic initialization, key derivation, signature verification, certificate validation, and secure messaging.
- Recipes for analyzing encryptions, hashing, certificate chains, secure communications, and integrity verification.
- Playbooks for cryptographic system review, authentication analysis, secure protocol design, and certificate validation.
- Examples for C++ CryptoAPI/CNG usage, encryption, hashing, and secure communication.

## Prerequisites
- `shared` for documentation conventions.
- `windows-internals` for API and system security context.
- `cpp` for implementation examples.

## Used by
- `networking`
- `system-design`
- `hypervisor`

## Related Skills
- `networking` — secure transport and protocol encryption.
- `system-design` — secure architecture and key management.
- `windows-internals` — platform crypto services and trusted execution.

## Entry Conditions
- Cryptographic algorithms, certificates, or secure channels require analysis.
- Protocols and data storage depend on encryption, hashing, or authentication.
- Secure software design must be evaluated.

## Exit Conditions
- Cryptographic primitives and protections are mapped to implementation and threat models.
- Key management and certificate validation behavior are understood.
- Secure communication and integrity workflows are documented.

## Typical Workflow
1. Identify the cryptographic primitives and API surfaces in use.
2. Map data flow through encryption, hashing, and signing operations.
3. Evaluate key lifecycle, entropy sources, and algorithm choice.
4. Verify certificate chains, signature checks, and secure channel setup.
5. Document cryptographic evidence and recommend correct usage.

## Notes
- Emphasize defensive engineering and correct algorithm selection.
- Avoid promoting bypass or offensive misuse of cryptography.

## Related Material

- Knowledge: [asymmetric-cryptography](knowledge/asymmetric-cryptography.md)
- Patterns: [certificate-validation](patterns/certificate-validation.md)
- Recipes: [analyze-certificate-chain](recipes/analyze-certificate-chain.md)
- Playbooks: [analyze-secure-protocol](playbooks/analyze-secure-protocol.md)
- Examples: [cng-aes-encrypt](examples/cng-aes-encrypt.md)
- References: [references](references/references.md)
- Rules: [cryptography-guidelines](rules/cryptography-guidelines.md)
- Prompts: [crypto-analysis](prompts/crypto-analysis.md)
- Checklists: [cryptography-audit-checklist](checklists/cryptography-audit-checklist.md)

