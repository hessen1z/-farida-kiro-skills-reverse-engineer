# Socket Initialization Pattern

## Pattern Name
Socket Initialization

## Problem
Identify the setup and configuration of network sockets in Windows applications.

## Context
Winsock applications initialize sockets before binding, listening, or connecting. The initialization phase determines protocol family, socket type, and blocking behavior.

## Recognition
- calls to `WSAStartup`, `socket`, `setsockopt`, `bind`, `listen`, `connect`
- use of `AF_INET`, `AF_INET6`, `SOCK_STREAM`, `SOCK_DGRAM`
- non-blocking or overlapped mode setup via `ioctlsocket`, `WSAEventSelect`, `WSARecv`, `WSASend`

## Evidence
- socket descriptors and address family mapping in code or memory.
- error handling around `WSAStartup` and `socket` creation.
- configuration of timeouts and reuse options with `setsockopt`.

## Resolution / Action
- map socket lifecycle from creation to closure.
- verify whether the application is using TCP, UDP, or raw sockets.
- check whether sockets are configured for asynchronous I/O or event-driven handling.

## Notes
- socket initialization mistakes often cause connection failures or unexpected blocking.
- Winsock must be initialized before any socket calls.

## References
- Winsock documentation

## See Also
- `../recipes/analyze-tcp-session.md`
- `../examples/winsock-server-client.md`

## Related Material

### Knowledge
- [application-protocols](../knowledge/application-protocols.md)
- [ipv4-ipv6](../knowledge/ipv4-ipv6.md)
- [multiplayer-networking](../knowledge/multiplayer-networking.md)

### Patterns
- [packet-parsing](packet-parsing.md)
- [replication-patterns](replication-patterns.md)

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

