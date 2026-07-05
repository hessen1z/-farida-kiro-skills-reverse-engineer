# Networking Guidelines

## Principles
- Validate packet formats strictly before processing.
- Treat UDP payloads as unreliable and maintain sequence or timestamp checks.
- Use secure transports for authentication, state sync, and sensitive data.
- Do not assume network packets arrive in order or only once.

## Design Rules
- Separate connection management, packet parsing, and application logic.
- Prefer established protocols and avoid custom insecure handshakes.
- Document port usage and protocol expectations explicitly.

## Analysis Rules
- Start from the lowest layer that can explain the issue.
- Map each observed packet to its likely sender and intended listener.
- Flag any unencrypted credentials or protocol downgrade attempts.

## Security Rules
- Verify authentication and integrity before accepting client state.
- Ensure replay protection for any state-changing messages.
- Validate that any encryption keys or certificates come from trusted sources.

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
- [analyze-network-stack](../playbooks/analyze-network-stack.md)
- [multiplayer-network-playbook](../playbooks/multiplayer-network-playbook.md)
- [network-performance](../playbooks/network-performance.md)

### Examples
- [http-tls-analysis](../examples/http-tls-analysis.md)
- [packet-parser](../examples/packet-parser.md)
- [winsock-server-client](../examples/winsock-server-client.md)

### References
- [references](../references/references.md)

### Prompts
- [multiplayer-networking-review](../prompts/multiplayer-networking-review.md)
- [network-protocol-analysis](../prompts/network-protocol-analysis.md)
- [secure-transport-review](../prompts/secure-transport-review.md)

### Checklists
- [networking-analysis-checklist](../checklists/networking-analysis-checklist.md)

