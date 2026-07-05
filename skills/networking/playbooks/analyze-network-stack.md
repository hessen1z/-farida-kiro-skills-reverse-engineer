# Analyze Network Stack Playbook

## Goal
Review network stack behavior end-to-end, identify protocol mismatches, and validate transport to application flow.

## Steps
1. Identify the network layers in use: link, internet, transport, application.
2. Collect packet traces and map each header against expected protocol syntax.
3. Use `networking-overview` and `tcp-ip-model` knowledge to classify packets.
4. Confirm socket creation, binding, and connection semantics in application logs.
5. Compare packet timing and retransmission behavior with TCP and UDP expectations.
6. Verify application payload format and handshake completion.

## Focus Areas
- TCP state transitions and handshake completion.
- UDP message integrity and expected sequence semantics.
- IPv4/IPv6 addressing and routing assumptions.
- Application protocol negotiation (`HTTP`, `TLS`, `DNS`).

## Actions
- Trace packet exchanges across clients and servers.
- Validate port numbers and payload boundaries.
- Inspect firewall/NAT behavior when packets are dropped.
- Ensure reliable channels use retransmission and timeouts appropriately.

## Cross References
- `../knowledge/tcp-ip-model.md`
- `../patterns/packet-parsing.md`
- `../recipes/analyze-packets.md`

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
- [analyze-multiplayer-game](../recipes/analyze-multiplayer-game.md)
- [analyze-packets](../recipes/analyze-packets.md)
- [analyze-tcp-session](../recipes/analyze-tcp-session.md)

### Playbooks
- [multiplayer-network-playbook](multiplayer-network-playbook.md)
- [network-performance](network-performance.md)
- [secure-protocol-review](secure-protocol-review.md)

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

