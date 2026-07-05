# Winsock Server/Client Example

## Scenario
A simple TCP server and client pair on Windows using Winsock demonstrates socket setup, binding, listening, and data transfer.

## Server Behavior
1. Initialize Winsock (`WSAStartup`).
2. Create a socket with `AF_INET`, `SOCK_STREAM`, `IPPROTO_TCP`.
3. Bind to a port and call `listen`.
4. Accept incoming connections and receive data.
5. Send responses and close sockets cleanly.

## Client Behavior
1. Initialize Winsock and resolve the server address.
2. Create a TCP socket and connect to the server.
3. Send request payload and read the response.
4. Shutdown and close sockets.

## Notes
- Use non-blocking mode or I/O completion ports for scalable servers.
- Confirm error codes from `WSAGetLastError` when socket calls fail.
- Validate the protocol state machine: connect, send, receive, close.

## Cross References
- `../patterns/socket-initialization.md`
- `../snippets/tcp-server.cpp`
- `../snippets/udp-client.cpp`

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
- [http-tls-analysis](http-tls-analysis.md)
- [packet-parser](packet-parser.md)

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

