# Networking Knowledge

## Overview
Networking is the set of protocols, software stacks, and runtime behaviors that enable systems to exchange data. On Windows, networking spans from low-level packet handling through the TCP/IP stack to application-layer protocols such as HTTP and TLS.

This document describes the OSI and TCP/IP models, packet structure, Windows stack internals, socket programming, and multiplayer networking concepts.

## OSI and TCP/IP Models

### OSI Model
The OSI model divides networking into seven layers:
1. Physical
2. Data Link
3. Network
4. Transport
5. Session
6. Presentation
7. Application

### TCP/IP Model
The TCP/IP model condenses the stack into four layers:
- Link layer
- Internet layer
- Transport layer
- Application layer

Windows primarily exposes the TCP/IP stack and Winsock API at the transport and application layers, while the kernel manages link and network layer behavior.

## IPv4 and IPv6

### IPv4
IPv4 uses 32-bit addresses and supports fragmentation, header checksums, and network classes. Core protocols include:
- ICMP for diagnostics and error reporting
- ARP for address resolution
- DHCP for dynamic address assignment

### IPv6
IPv6 uses 128-bit addresses, simplified headers, and built-in support for extension headers and multicast. Its packet format eliminates IPv4 fragmentation in favor of path MTU discovery.

## UDP and TCP

### UDP
UDP is connectionless and provides minimal transport services. It is useful for low-latency or real-time applications where packet loss is acceptable.

### TCP
TCP is connection-oriented and provides reliable, ordered delivery. It includes sequence numbers, acknowledgments, congestion control, and flow control.

### Packet Structure
Key packet headers:
- Ethernet frame header
- IPv4/IPv6 network header
- TCP/UDP transport header
- Application payload

A typical packet inspection workflow reconstructs these headers and validates checksums, lengths, and protocol fields.

## ICMP, DNS, DHCP, HTTP, HTTPS, TLS, SSL

### ICMP
ICMP provides network diagnostics such as ping and path discovery. It also reports unreachable destinations and TTL expiry.

### DNS
DNS resolves hostnames to IP addresses and supports query/response messaging, recursion, and caching.

### DHCP
DHCP automates IP address assignment and network configuration for hosts.

### HTTP and HTTPS
HTTP is an application-layer protocol for resource retrieval. HTTPS adds TLS encryption for confidentiality and integrity.

### TLS/SSL
TLS provides secure communication with handshake negotiation, certificate validation, encryption, and integrity protection.

## Winsock and Windows Networking Stack

### Winsock API
Winsock provides socket abstractions for TCP, UDP, and raw packet access. Core functions include:
- `socket`
- `bind`
- `listen`
- `connect`
- `send` / `recv`
- `WSAStartup`

### Windows Networking Stack
The Windows kernel implements the transport stack with components such as:
- TDI/NDIS and network drivers
- IP stack and routing table management
- TCP connection state and congestion control
- Winsock kernel services for user-mode interaction

## Socket Programming

### Socket Lifecycle
A socket transitions through:
- creation
- binding or connecting
- listening or sending
- shutdown and closure

### Non-blocking and asynchronous I/O
Winsock supports overlapped I/O, completion ports, and event-based notifications. These mechanisms are essential for high-performance server and multiplayer game architectures.

## Packet Parsing and Routing

### Packet Parsing
Packet parsing reconstructs each protocol layer and validates fields. A robust parser checks packet boundaries, header lengths, and protocol-specific semantics.

### Routing and NAT
Routing determines packet forwarding across networks. NAT translates internal private addresses to public addresses and modifies transport endpoints as needed.

## Firewalls and Secure Networking

### Firewalls
Firewalls enforce access control based on addresses, ports, and protocol state. Stateful firewalls track connection state for TCP flows.

### Secure Networking
Secure networking uses authentication, encryption, packet validation, and replay protection. TLS and secure sockets are common mechanisms for confidentiality.

## Multiplayer Networking

### Replication and Prediction
Multiplayer systems replicate game state, synchronize clients, and use client-side prediction to mask latency.

### Lag Compensation
Lag compensation techniques adjust game state history and reconcile delayed inputs.

### Packet Validation
Multiplayer networking requires validating packet contents, sequence numbers, and authentication tokens to prevent cheating and corruption.

## Protocol Design and Performance

### Protocol Design
Protocol design balances reliability, latency, bandwidth, and complexity. UDP is often preferred for fast-paced games, while TCP is used for reliable control channels.

### Performance Optimization
Performance depends on batching, minimizing system calls, reducing packet overhead, and using efficient serialization.

## Practical Workflows

### Analyze Network Protocol
1. Identify the transport and application protocols.
2. Capture packets and decode headers.
3. Reconstruct session state and validate protocol semantics.
4. Evaluate error handling and security assumptions.

### Analyze Multiplayer Game
1. Map client/server messages and update frequencies.
2. Assess prediction and reconciliation strategies.
3. Validate authentication and packet validation logic.
4. Measure latency, jitter, and loss sensitivity.

## Common Mistakes
- Treating network byte order as host byte order.
- Assuming packet arrival order for UDP protocols.
- Overlooking secure handshake validation.
- Using blocking sockets in high-performance loops.

## References
- RFC 791, 2460, 793, 768
- RFC 5246 (TLS)
- Winsock Programmer’s FAQ
- Windows Networking documentation
- High Performance Browser Networking

## Cross-links
- `../patterns/packet-parsing.md`
- `../recipes/analyze-packets.md`
- `../playbooks/multiplayer-network-playbook.md`

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

