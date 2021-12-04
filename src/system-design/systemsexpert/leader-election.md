---
title: leader-election
---

Election

# Leader Election

- Imagine a situation where we might want our database to connect to a
  third party service (stripe, plaid, youtube, Google Analytics, etc.)

- That would look like this:

```{=html}
<!-- -->
```

    Third Party Service             Database
    [                 ]<-------->[   Master   ]

- This isn\'t ideal: so we\'ll put our own service which gates out
  certain functionality.

```{=html}
<!-- -->
```

    Third Party Service           Your Service           Database
    [                 ]<-------->[   Leader   ]<------->[        ]

- But here, we only have server that is a single point of failure.
- Let\'s make it more redundant by adding more servers.

```{=html}
<!-- -->
```

    Third Party Service           Your Service           Database
    [                 ]<-------->[   Leader   ]<------->[        ]
    [                 ]<-------->[   Leader   ]<------->[        ]
    [                 ]<-------->[   Leader   ]<------->[        ]
    [                 ]<-------->[   Leader   ]<------->[        ]
    [                 ]<-------->[   Leader   ]<------->[        ]

- But now, we want every operation to only occur once.

- We can\'t charge a person twice for the same invoice.

- Leader Election has a server elect one of the servers as a `leader`,
  which is the only server that connects to the database.

```{=html}
<!-- -->
```

    Third Party Service           Your Service           Database
    [                 ]<-------->[   Leader   ]<------->[        ]
    [                 ]--------->[  Follower  ]<------->[        ]
    [                 ]--------->[  Follower  ]<------->[        ]
    [                 ]--------->[  Follower  ]<------->[        ]

- Now, all writes to the leader have to propogate to the followers in
  case of failure, and when the leader dies, then the followers have
  to relect a new leader.

- Consensus building (Leader Election) is actually quite hard.

- It\'s hard to share some state.

- We need a Consensus Algorithm to achieve this leader election.

## Consensus Algorithms

- Paxos

- Raft

- Two tools that implement Leader Election:

  - Zookeeper
  - Etcd

- Etcd is a key-value store that is highly available and strongly
  consistent.

  - Etcd uses Raft for leader election

- Have Etcd use a key value that has a `leader` key set to a value of
  the leader server.

- Then, all the servers are strongly consistent and synced to a
  leader.

Prev:
\[replication-and-sharding](replication-and-sharding.md)
Next:
\[peer-to-peer-networks](peer-to-peer-networks.md)
