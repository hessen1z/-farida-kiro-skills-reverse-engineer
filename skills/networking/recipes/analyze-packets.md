# Analyze Packets Recipe

## Purpose
Analyze captured network packets to reconstruct protocol behavior, identify malformed traffic, and verify packet integrity.

## Prerequisites
- packet capture or network trace data.
- knowledge of protocol header formats.
- tools for inspecting packet bytes.

## Inputs
- raw packet data.
- expected protocol stack.
- endpoint addresses and ports.

## Steps
1. Disassemble packet layers: Ethernet, IP, transport, and application.
2. Validate header lengths and checksums.
3. Identify packet direction and session context.
4. Check for fragmentation, retransmissions, or malformed fields.
5. Map packets to application-level actions.

## Verification
- Confirm the packet conforms to the expected protocol.
- Identify negotiation or handshake messages.
- Document any invalid or suspicious packet contents.

## Notes
- packet analysis is often iterative: reconstruct one flow, then expand to related traffic.
- malformed packets may indicate bugs, protocol version mismatch, or attack attempts.

## References
- RFC 791, 793, 768, 2460
- Wireshark documentation

## Cross-links
- `../patterns/packet-parsing.md`
- `../examples/packet-parser.md`

## Related Material

### Knowledge
- [application-protocols](../knowledge/application-protocols.md)
- [ipv4-ipv6](../knowledge/ipv4-ipv6.md)
- [multiplayer-networking](../knowledge/multiplayer-networking.md)

### Patterns
- [packet-parsing](../patterns/packet-parsing.md)
- [replication-patterns](../patterns/replication-patterns.md)
- [socket-initialization](../patterns/socket-initialization.md)

### Recipes
- [analyze-multiplayer-game](analyze-multiplayer-game.md)
- [analyze-tcp-session](analyze-tcp-session.md)
- [analyze-udp-protocol](analyze-udp-protocol.md)

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

