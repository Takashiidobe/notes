---
title: peer-to-peer-networks
---

To Peer Networks

# Peer-to-Peer Networks

- Imagine you are designing a system where you would like to send
  large files to a thousand machines.

Assume we have one leader that propagates files.

- with 40 Gbps (5GBps) network throughput
- and 5GB files to 1000 machines:
- It would take about \~17 minutes.
- Now, have the machine clone the file to 10 machines, and have all
  reads off of that, like this:

```{=html}
<!-- -->
```

                            [ ]
                             ^
                             |
    [ ]<->[ ]<->[ ]<->[ ]<->[ ]<->[ ]<->[ ]<->[ ]<->[ ]<->[ ]
     ^     ^     ^     ^     ^     ^     ^     ^     ^     ^
     |     |     |     |     |     |     |     |     |     |
    [ ]   [ ]   [ ]   [ ]   [ ]   [ ]   [ ]   [ ]   [ ]   [ ]
     ^     ^     ^     ^     ^     ^     ^     ^     ^     ^
     |     |     |     |     |     |     |     |     |     |
    [ ]   [ ]   [ ]   [ ]   [ ]   [ ]   [ ]   [ ]   [ ]   [ ]
     ^     ^     ^     ^     ^     ^     ^     ^     ^     ^
     |     |     |     |     |     |     |     |     |     |
    [ ]   [ ]   [ ]   [ ]   [ ]   [ ]   [ ]   [ ]   [ ]   [ ]
     ^     ^     ^     ^     ^     ^     ^     ^     ^     ^
     |     |     |     |     |     |     |     |     |     |
    [ ]   [ ]   [ ]   [ ]   [ ]   [ ]   [ ]   [ ]   [ ]   [ ]

- Still, this is about 1.5 minutes, and this takes 10x more memory
  (40GB extra memory).

- Sharding doesn\'t solve our problem either.

## Fundamentals

- We can split our 5GB file into small chunks, and then send chunks of
  the file to each other, and then have all the machines communicate
  with each other to get the missing pieces.

```{=html}
<!-- -->
```

                            [ ]
                             ^
                             |
    [ ]<->[ ]<->[ ]<->[ ]<->[ ]<->[ ]<->[ ]<->[ ]<->[ ]<->[ ]
     ^     ^     ^     ^     ^     ^     ^     ^     ^     ^
     |     |     |     |     |     |     |     |     |     |
     v     v     v     v     v     v     v     v     v     v
    [ ]<->[ ]<->[ ]<->[ ]<->[ ]<->[ ]<->[ ]<->[ ]<->[ ]<->[ ]
     ^     ^     ^     ^     ^     ^     ^     ^     ^     ^
     |     |     |     |     |     |     |     |     |     |
     v     v     v     v     v     v     v     v     v     v
    [ ]<->[ ]<->[ ]<->[ ]<->[ ]<->[ ]<->[ ]<->[ ]<->[ ]<->[ ]
     ^     ^     ^     ^     ^     ^     ^     ^     ^     ^
     |     |     |     |     |     |     |     |     |     |
     v     v     v     v     v     v     v     v     v     v
    [ ]<->[ ]<->[ ]<->[ ]<->[ ]<->[ ]<->[ ]<->[ ]<->[ ]<->[ ]
     ^     ^     ^     ^     ^     ^     ^     ^     ^     ^
     |     |     |     |     |     |     |     |     |     |
     v     v     v     v     v     v     v     v     v     v
    [ ]   [ ]   [ ]   [ ]   [ ]   [ ]   [ ]   [ ]   [ ]   [ ]

- Now all of our nodes can communicate with each other.

  - Split our 5GB file into 1000 5MB files,
  - Then send each node one of our chunks.

- Then, all the other files can talk to each other to get all the rest
  of the chunks needed to create the 5GB file.

- Technologies used:

- [Kraken](https://github.com/uber/kraken)

- Open source project for P2P distribution.

Prev: \[leader-election](leader-election.md) Next:
\[polling-and-streaming](polling-and-streaming.md)
