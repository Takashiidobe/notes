---
title: Load Balancers
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Sunday, July 6th 2025, 8:41:48 pm
---

# Load Balancers

- Load Balancers reduce the one point of failure problem.

- To deal with increased traffic, we can vertically scale our server
  (add more hardware to our one machine)

- we can horizontally scale -\> add more machines.

```{=html}
<!-- -->
```

    Clients  LB         Servers
    [] ----> [ ]--------> [ ]
    [] ----> [ ]--------> [ ]
    [] ----> [ ]--------> [ ]

At the DNS level, a strategy called Round Robin is used.

- if you run `dig google.com`, you get different IP addresses for
  google.com.

- The same domain name has different IP addresses.

- Load Balancing Strategies:

- Purely random:

  - Pros: simple:
  - Cons: could randomly overload a server.

- Round Robin:

  - Pros: simple:
  - Cons: heavy/blocking requests may overload a server.

- Weighted Round Robin:

  - Pros: has weight, so maybe you want to route more traffic.
  - Cons: Complicated

- IP based:

  - Hashes the IP address and then sends the requests to that
    server.
  - Great for caching. Computer will always be rerouted to the
    correct server.

- Path based:

  - Route requests to a server based to the resource they want to
    access.
  - eg. /code, /payments go to their own servers.
  - less downtime when updating.

You may want to mix and match load balancing strategies based on parts
of the services. You also need more than one load balancers, to reroute
traffic to destinations.

Nginx allows for setting a weight parameter, which lets you route
traffic to different servers at different rates..

Prev: \[proxies](proxies.md) Next:
\[hashing](hashing.md)
