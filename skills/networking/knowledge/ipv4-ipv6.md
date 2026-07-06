---
title: IPv4 and IPv6 Knowledge
skill: networking
category: knowledge
difficulty: intermediate
tags: [pe, networking, gui]
updated: 2026-07-05
---
# IPv4 and IPv6 Knowledge

## Overview
IPv4 and IPv6 are the primary network-layer protocols that define address formats and packet forwarding behavior.

## IPv4
- 32-bit addresses
- header includes version, IHL, total length, TTL, protocol, checksum
- supports fragmentation and options

## IPv6
- 128-bit addresses
- simplified header with fixed size
- extension headers replace IPv4 options
- built-in multicast and improved routing

## Routing and Addressing
- IPv4 uses subnet masks and CIDR notation.
- IPv6 uses prefix lengths and scoped addresses.
- Routing decisions are made at the network layer by inspecting destination addresses.

## Packet Processing
- IPv4 packets require header checksum verification.
- IPv6 packets omit the checksum but may include extension headers.
- fragmentation in IPv6 is handled by the source node.

## Practical Workflows
- compare IPv4 and IPv6 packet structures in a trace.
- validate address scopes and gateway configuration.
- inspect neighbor discovery and ARP/ND behavior.

## Common Mistakes
- confusing IPv4 and IPv6 header lengths.
- assuming IPv6 supports broadcast addresses.
- neglecting extension header order and processing rules.

## References
- RFC 791, 2460

## Cross-links
- `../patterns/packet-parsing.md`
- `../examples/packet-parser.md`

## Related Material

### Knowledge
- [application-protocols](application-protocols.md)
- [multiplayer-networking](multiplayer-networking.md)
- [networking-overview](networking-overview.md)

### Patterns
- [packet-parsing](../patterns/packet-parsing.md)
- [replication-patterns](../patterns/replication-patterns.md)
- [socket-initialization](../patterns/socket-initialization.md)

### Recipes
- [analyze-multiplayer-game](../recipes/analyze-multiplayer-game.md)
- [analyze-packets](../recipes/analyze-packets.md)
- [analyze-tcp-session](../recipes/analyze-tcp-session.md)

### Playbooks
- [analyze-network-stack](../playbooks/analyze-network-stack.md)
- [multiplayer-network-playbook](../playbooks/multiplayer-network-playbook.md)
- [network-performance](../playbooks/network-performance.md)

### Examples
- [http-tls-analysis](../examples/http-tls-analysis.md)
- [packet-parser](../examples/packet-parser.md)
- [winsock-server-client](../examples/winsock-server-client.md)

### References
- [references](../references/references.md)

### Rules
- [networking-guidelines](../rules/networking-guidelines.md)

### Prompts
- [multiplayer-networking-review](../prompts/multiplayer-networking-review.md)
- [network-protocol-analysis](../prompts/network-protocol-analysis.md)
- [secure-transport-review](../prompts/secure-transport-review.md)

### Checklists
- [networking-analysis-checklist](../checklists/networking-analysis-checklist.md)

## Practical Guidance

- When analyzing captures, normalize capture timestamps and reassemble higher-level streams for protocol-specific inspection.
- Pay attention to fragmentation and extension header ordering when reconstructing payloads.

## Tools & Commands

- `tshark`/`Wireshark` for packet decoding, `scapy` for crafting and testing packets.

## Validation Checklist

- Confirm address scopes, routing, and MTU are correctly configured for expected traffic flows.
- Validate neighbor discovery/ARP behavior and confirm no duplicate addresses or misconfigured gateways.

