---
title: Cryptography Fundamentals
skill: cryptography
category: knowledge
difficulty: intermediate
tags: [pe, windows, cryptography, gui]
updated: 2026-07-05
---
# Cryptography Fundamentals

## Overview
Cryptography is the science of securing information through mathematical transformations. Effective engineering uses standard algorithms, strong keys, proper randomness, and careful protocol implementation.

This document covers symmetric and asymmetric encryption, hashing, digital signatures, certificates, PKI, key management, entropy, Windows cryptographic APIs, and secure communication.

## Cryptography Fundamentals

### Confidentiality, Integrity, Authentication
Cryptography supports three main goals:
- **Confidentiality**: prevent unauthorized disclosure of data
- **Integrity**: ensure data has not been altered
- **Authentication**: verify identities of parties and data origin

### Symmetric vs Asymmetric
- **Symmetric encryption** uses the same key for encryption and decryption. Examples: AES, 3DES.
- **Asymmetric encryption** uses public/private key pairs. Examples: RSA, ECC.

## Block Ciphers and Stream Ciphers

### Block Ciphers
Block ciphers operate on fixed-size blocks. Popular modes include:
- CBC (Cipher Block Chaining)
- GCM (Galois/Counter Mode)
- CTR (Counter Mode)

### Stream Ciphers
Stream ciphers generate a key stream to XOR with plaintext. They are useful for lightweight or streaming data, but require careful nonce and key management.

### AES
AES is the standard block cipher used in modern protocols. It supports 128, 192, and 256-bit keys and is widely supported in hardware and software.

## RSA, ECC, and Diffie-Hellman

### RSA
RSA is a public-key algorithm used for encryption and digital signatures. Security depends on large prime factorization and proper padding (PKCS#1 v2.2 / OAEP / PSS).

### ECC
Elliptic Curve Cryptography uses curves over finite fields to provide equivalent security with smaller keys. Common curves include P-256 and Curve25519.

### Diffie-Hellman
DH enables two parties to derive a shared secret over an insecure channel. Elliptic Curve Diffie-Hellman (ECDH) is the modern variant.

## Hash Functions and HMAC

### SHA Family
SHA-1, SHA-256, SHA-384, and SHA-512 are cryptographic hash functions. SHA-1 is deprecated for security-sensitive uses.

### HMAC
HMAC combines a hash function with a secret key to provide message authentication. It is widely used in TLS, APIs, and token signing.

## Digital Signatures and Certificates

### Digital Signatures
Digital signatures prove authenticity and integrity. RSA and ECDSA are common signature algorithms.

### Certificates and PKI
Certificates bind public keys to identities using a chain of trust. PKI includes root CAs, intermediate CAs, revocation mechanisms, and validation rules.

### Certificate Validation
Validation includes chain building, expiry checks, revocation status, and verifying the signature against trusted roots.

## Key Management and Entropy

### Key Management
Key management covers generation, storage, rotation, usage, and destruction. Good practices include:
- limiting key lifetime
- using hardware-protected key storage
- separating key usage roles

### Entropy and RNG
Secure random numbers are foundational. Entropy sources should be robust and should not rely on predictable values.

## Windows CryptoAPI and CNG

### CryptoAPI
CryptoAPI provides legacy encryption and signature services through `CryptAcquireContext`, `CryptEncrypt`, `CryptVerifySignature`, and certificate stores.

### CNG
Cryptography Next Generation (CNG) offers modern primitives, key storage, and algorithm agility with `BCryptOpenAlgorithmProvider`, `BCryptCreateHash`, and `BCryptGenRandom`.

## TLS Handshake and Secure Storage

### TLS Handshake
TLS negotiates protocols, ciphers, and keys. A typical handshake includes:
1. ClientHello
2. ServerHello
3. Certificate exchange
4. Key exchange
5. Finished messages

### Secure Storage
Secure storage protects secrets at rest. This can use encrypted files, OS protected storage, or hardware-backed key storage.

## Integrity Verification

### Data Integrity
Integrity checks may use hashes, MACs, or authenticated encryption. Authenticated encryption modes such as AES-GCM combine confidentiality with integrity.

### Secure Communication
Secure communication requires correct handshake validation, protocol version negotiation, and consistent use of authenticated encryption.

## Practical Workflows

### Analyze Encryption
1. Identify the algorithm and mode in use.
2. Verify key length, padding, and initialization vectors.
3. Assess whether randomness and key generation are secure.

### Analyze Certificates
1. Extract certificate chain and trust anchors.
2. Validate issuer signatures, validity period, and revocation state.
3. Confirm the subject and extended key usage.

## Common Mistakes
- Reusing IVs or nonces with AES-GCM or CTR.
- Using deprecated algorithms such as MD5 or SHA-1.
- Failing to verify certificate chains or hostnames.
- Storing keys in plaintext or predictable memory.

## References
- NIST SP 800-38A, SP 800-57
- RFC 5246 (TLS 1.2), RFC 8446 (TLS 1.3)
- Microsoft CryptoAPI and CNG documentation
- Applied Cryptography by Bruce Schneier
- Cryptography Engineering by Ferguson, Schneier, and Kohno

## Cross-links
- `../patterns/crypto-patterns.md`
- `../recipes/analyze-encryption.md`
- `../playbooks/analyze-secure-protocol.md`

## Related Material

### Knowledge
- [asymmetric-cryptography](asymmetric-cryptography.md)
- [certificate-pki](certificate-pki.md)
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

- Use well-vetted libraries and avoid implementing primitives. Prefer AEAD ciphers and modern key derivation functions.
- Record and enforce key lifecycles, including rotation and revocation policies.

## Tools & Commands

- OpenSSL and libsodium for testing algorithms and verifying interoperability.
- Use `openssl` test vectors and NIST resources for algorithm validation.

## Validation Checklist

- Confirm deprecated algorithms are not used in security-sensitive flows.
- Verify key storage practices and entropy sources meet platform standards.

