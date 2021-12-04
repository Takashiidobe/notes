---
title: proxies
---

# Proxies

## Forward Proxies

A client issues a request to a Forward Proxy, which then forwards the
request to the server. The server then responds to the client from the
server.

    Client   Forward Proxy    Server
    [ C ]<------>[ F ]<------->[ S ]

This is basically how VPNs work. This way, the client\'s IP address is
only known by the Forward Proxy, and the Server only knows the Forward
Proxy\'s request.

## Reverse Proxies

Reverse proxies work similarly, but for the server.

The client\'s request is sent to the Reverse Proxy, and the Reverse
Proxy returns the response to the client.

The client thinks it\'s interacting with the server. The server has no
idea of the client.

This is useful \-- Reverse Proxies can be used to cache requests, log
requests, or as a Load Balancer.

Nginx can be used to add or remove headers from requests, if you use it
as a reverse proxy, to filter requests and send them to the right place.

    Client   Reverse Proxy    Server
    [ C ]<------>[ R ]<------->[ S ]

Prev: \[caching](caching.md) Next:
\[hashing](hashing.md)
