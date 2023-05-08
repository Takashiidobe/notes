# TCP vs UDP

TCP is a connection oriented stream over IP. It guarantees that all sent packets will reach the destination in order.

It has a handshake, where it negotiates a connection before sending packets.

UDP is connectionless. Communication is datagram oriented, and integrity is guaranteed for a single datagram.

UDP is generally used for streaming/high performance applications, where there is less cost to reordered packets.

TCP is used for lower performance applications where ordered packets are preferred.
