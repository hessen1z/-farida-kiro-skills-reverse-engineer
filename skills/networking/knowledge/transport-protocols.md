# Transport Protocols Knowledge

## Overview
Transport protocols provide host-to-host communication and reliability guarantees. On Windows, TCP and UDP are the most commonly used transport protocols.

## TCP
- connection-oriented and reliable
- supports flow control, congestion control, and retransmission
- uses sequence numbers, acknowledgments, and windowing

## UDP
- connectionless and unreliable
- minimal overhead for low-latency applications
- suitable for real-time audio/video and game state updates

## Protocol Behavior
- TCP sessions begin with a three-way handshake and end with a four-way teardown.
- UDP messages are independent datagrams and may arrive out of order.
- both protocols use port numbers to identify endpoints.

## Practical Workflows
- inspect TCP handshake and session state from packet captures.
- identify UDP-based protocol semantics through payload structure.
- validate checksum and port number consistency.

## Common Mistakes
- treating UDP as reliable.
- assuming TCP always delivers packets in the same send order under retransmission.
- ignoring path MTU and segmentation effects.

## References
- RFC 793, 768

## Cross-links
- `../recipes/analyze-tcp-session.md`
- `../recipes/analyze-udp-protocol.md`

## Related Material

### Knowledge
- [application-protocols](application-protocols.md)
- [ipv4-ipv6](ipv4-ipv6.md)
- [multiplayer-networking](multiplayer-networking.md)

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

