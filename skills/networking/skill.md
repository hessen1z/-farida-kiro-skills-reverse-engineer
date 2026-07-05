---
name: Networking
version: 1.0
priority: critical
requires:
  - shared
  - windows-internals
  - cpp
tags:
  - networking
  - protocol
  - transport
description: Core networking skill covering OSI and TCP/IP models, Windows networking stack, socket programming, protocols, and multiplayer network analysis.
---

# Networking Skill

## Purpose
Provide a production-grade reference for networking protocols, Windows network stack internals, packet flow, and secure networking. This skill supports protocol analysis, performance optimization, and multiplayer network engineering.

## What this skill provides
- Knowledge of OSI model, TCP/IP, IPv4/IPv6, UDP, TCP, DNS, DHCP, HTTP, TLS, and Windows socket API.
- Patterns for socket initialization, packet parsing, protocol handlers, serialization, encryption handshakes, and replication.
- Recipes for analyzing network protocols, TCP/UDP session behavior, packet validation, and secure networking.
- Playbooks for multiplayer networking, packet flow analysis, replication systems, and secure protocol review.
- Examples for Winsock programming, packet parsers, network protocol implementations, and middleware.

## Prerequisites
- `shared` for documentation conventions.
- `windows-internals` for network stack and socket behavior.
- `cpp` for implementation and performance examples.

## Used by
- `game-engines`
- `game-security`
- `system-design`

## Related Skills
- `windows-internals` — networking APIs and kernel-mode stack behavior.
- `cpp` — packet parsing, serialization, and protocol implementation.
- `system-design` — architecture of scalable networked systems.

## Entry Conditions
- A networking protocol or socket-based system needs analysis.
- Packet flow, latency, replication, or secure network behavior is relevant.
- Multiplayer synchronization or protocol design decisions must be evaluated.

## Exit Conditions
- Protocol semantics and packet structures are documented.
- Network flows, validation checks, and security boundaries are understood.
- Performance and reliability considerations are mapped.

## Typical Workflow
1. Identify the protocol stack and packet formats in use.
2. Inspect socket or transport initialization and connection state.
3. Analyze packet parsing, session handling, and error recovery.
4. Verify security, encryption, and handshake behavior.
5. Document preferred network architectures and cross-link to patterns.

## Notes
- Networking analysis spans both packet-level protocol details and system-level architecture.
- Focus on secure and robust design while avoiding unsafe parsing or protocol assumptions.

## Related Material

- Knowledge: [application-protocols](knowledge/application-protocols.md)
- Patterns: [packet-parsing](patterns/packet-parsing.md)
- Recipes: [analyze-multiplayer-game](recipes/analyze-multiplayer-game.md)
- Playbooks: [analyze-network-stack](playbooks/analyze-network-stack.md)
- Examples: [http-tls-analysis](examples/http-tls-analysis.md)
- References: [references](references/references.md)
- Rules: [networking-guidelines](rules/networking-guidelines.md)
- Prompts: [multiplayer-networking-review](prompts/multiplayer-networking-review.md)
- Checklists: [networking-analysis-checklist](checklists/networking-analysis-checklist.md)

