---
title: Network Protocols
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Sunday, July 6th 2025, 8:41:39 pm
---

# Network Protocols

- We\'ll look at IP, TCP and HTTP.

## IP - Internet Protocol

- An IP packet consists of a header and data.

- The header contains (20 - 60 bytes):

  - The source IP address.
  - Destination IP address.
  - Size of packet
  - Version of the IP packet (IPv4, IPv6)

- The data contains:

  - The body can only be 2\^16 bytes (65536 bytes)
  - IP does not guarantee that the server receives packets
  - or that packets are received in order.

## TCP - Transmission Control Protocol

- Built on top of IP
- Packets are guaranteed to be in order, and all sent, or an error is
  sent back to client.
- This lets you send arbitrarily long packets of data.
- The TCP header takes up more of the data part of the IP packet.
- This contains information about the ordering of the packets.

TCP starts out with a handshake.

- the client sends the server a metadata packet
- the server sends one back
- the client says ok
- Connection opens.
- Connections can be timed out.

## HTTP - HyperText Transfer Protocol

- HTTP is built on top of TCP.
- this creates a request - response paradigm or client - server model.
- an HTTP request has a host, port, method, headers, and a body.
- responses have a status code, headers, and a body.

Prev:
\[client-server-model](client-server-model.md)
Next: \[storage](storage.md)
