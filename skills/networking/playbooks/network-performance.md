# Network Performance Playbook

## Goal
Evaluate performance bottlenecks in networked systems and optimize throughput, latency, and reliability.

## Steps
1. Identify the transport protocol and connection patterns.
2. Measure round-trip latency and packet loss rates.
3. Inspect retransmission behavior and congestion control responses.
4. Review buffer usage, packet batching, and serialization overhead.
5. Analyze server-side throughput and thread or IO scheduling behavior.

## Focus Areas
- TCP windowing and congestion control.
- UDP packet size, fragmentation, and path MTU issues.
- Application-level update frequency and bandwidth usage.
- Endpoint CPU and memory usage for packet parsing.

## Actions
- Use packet captures to calculate delays and retransmits.
- Validate whether receive and send buffers are sized for workload.
- Identify expensive packet parsing or protocol deserialization hotspots.
- Confirm quality of service priorities and traffic shaping expectations.

## Cross References
- `../knowledge/transport-protocols.md`
- `../patterns/socket-initialization.md`
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
- [analyze-multiplayer-game](../recipes/analyze-multiplayer-game.md)
- [analyze-packets](../recipes/analyze-packets.md)
- [analyze-tcp-session](../recipes/analyze-tcp-session.md)

### Playbooks
- [analyze-network-stack](analyze-network-stack.md)
- [multiplayer-network-playbook](multiplayer-network-playbook.md)
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

