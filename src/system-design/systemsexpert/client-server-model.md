---
title: Client Server Model
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Sunday, July 6th 2025, 8:42:20 pm
---

# Client Server Model

## Clients

- A client is something that queries servers.
- e.g. A browser, or mobile device

## Servers

- A server is something that responds to requests.
- e.g. a Website backend

## Networking

### Making a GET Request

- When a browser looks up a website, it does a DNS lookup of the URL
  to find its IP Address
- a DNS query goes to a set of servers, and the server returns the IP
  address.
- an IP address is a unique id for public computers.
- an IP address is like a mailbox for a computer.
- `dig domain` makes a DNS query.

### Server Response

- With the IP address, the HTTP server knows where to send its
  request.
- The client can then send messages to it, and the server can respond
  to those messages with its own messages.
- HTTP is over TCP/IP, which is normally on port 80.
- HTTPS is over TCP/IP with TLS, which is normally on port 443.

## Exercise

- Use `nc -l 8081`
  - This listens on port 8081
- Use `nc 127.0.0.1 8081` to connect to port 8001.
  - This connects to the client on port 8081.
    - Send messages to see them on both terminals.

Prev:
\[what-are-design-fundamentals](what-are-design-fundamentals.md)
Next: \[network-protocols](network-protocols.md)
