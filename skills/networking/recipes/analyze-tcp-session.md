# Analyze TCP Session Recipe

## Purpose
Analyze a TCP session to understand connection setup, reliability, congestion control, and application data flow.

## Prerequisites
- packet capture of the TCP flow.
- familiarity with TCP state machine and headers.

## Inputs
- SYN/SYN-ACK/ACK handshake packets.
- sequence and acknowledgment values.
- retransmission and window size behavior.

## Steps
1. Verify the TCP three-way handshake.
2. Track sequence and acknowledgment progression.
3. Identify retransmissions, duplicate acknowledgments, and window updates.
4. Inspect payload boundaries and application-layer data.
5. Analyze congestion control or flow control behavior.

## Verification
- Confirm the connection established successfully.
- Identify any performance issues due to loss or window throttling.
- Verify payload ordering and reliability.

## Notes
- TCP session analysis requires careful tracking of sequence numbers and segment boundaries.
- retransmissions may be caused by packet loss or delayed acknowledgments.

## References
- RFC 793

## Cross-links
- `../patterns/packet-parsing.md`
- `../examples/tcp-session-analysis.md`

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
- [analyze-packets](analyze-packets.md)
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

