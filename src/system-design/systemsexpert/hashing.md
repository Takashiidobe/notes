---
title: hashing
---

# Hashing

- Turning anything into an integer value:

```{=html}
<!-- -->
```

    Clients Load Balancer Servers
    [ ] 11 % 4 = 3 -->[ ]-----------> []
    [ ] 12 % 4 = 0 -->[ ]-----------> []
    [ ] 13 % 4 = 1 -->[ ]-----------> []
    [ ] 14 % 4 = 2 -->[ ]-----------> []

If you don\'t send requests to the same server, we get cache misses.

- We want a hash function which uniformly/evenly distributes traffic
  to our servers.

- This maximizes cache hits.

- What happens if we need to add a server?

```{=html}
<!-- -->
```

    [ ] 11 % 5 = 1 -->[ ]-----------> []
    [ ] 12 % 5 = 2 -->[ ]-----------> []
    [ ] 13 % 5 = 3 -->[ ]-----------> []
    [ ] 14 % 5 = 4 -->[ ]-----------> []
    [ ] 15 % 5 = 0 -->[ ]-----------> []

- Now we get a bunch of cache misses, which will reduce performance.

- We can fix this with consistent caching:

- This is best imagined as a circle:

- the Clients have numbers, and the Servers are just uppercase
  letters.

- Each client is assigned to the next server it can find clockwise.

```{=html}
<!-- -->
```

                D  C1
            , - ~ ~ ~ - ,
         , '               ' , C4
       ,                       , A
      ,                         ,
     ,                           ,
     ,                           , C3
     ,                           ,
      ,                         ,
       ,                       ,
         ,                  , '
     C     ' - , _ _ _ ,  ' B
                 C2

- Let\'s add a new server (E):
  - If you ever add or remove a server, we only lose (log n) of our
    cache misses.

```{=html}
<!-- -->
```

                D  C1    E
            , - ~ ~ ~ - ,
         , '               ' , C4
       ,                       , A
      ,                         ,
     ,                           ,
     ,                           , C3
     ,                           ,
      ,                         ,
       ,                       ,
         ,                  , '
     C     ' - , _ _ _ ,  ' B
                 C2

- You can also hash multiple times, which helps with uneven hashing
  functions.

## Rendezvous Hashing

- We can use Rendezvous hashing in order to fix this problem as well.

- In Rendezvous hashing, each client lists a priority of servers it
  would like to get assigned to.

- On a Server insertion or Deletion, then the server picks its second
  priority pick.

This is a generalized for of Consistent Hashing, which can deal with the
range of N = 1 to Infinity.

Prev: \[load-balancers](load-balancers.md) Next:
\[relational-databases](relational-databases.md)
