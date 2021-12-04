---
title: replication-and-sharding
---

And Sharding

# Replication and Sharding

## Replication

    Main Database          Replica
             synchronous updates
    [           ]         [       ]
    [           ] ----->  [       ]
    [           ] ----->  [       ]
    [           ] ----->  [       ]
    [           ]         [       ]
             asynchronous updates

- When you write to the main database, you write to the replica as
  well.

- If writes fail to the replica, then rollback the transaction.

- This improves availability in some ways, but lowers performance.

- Asynchonous updates are more performant, but lower consistency, and
  have more difficult failure modes.

## Sharding

- Split up the database into different servers.

Strategies:

- Location based sharding:

- Table based sharding:

- Row-based sharding:

  - Split some rows into some computers.

- Some shards might get more traffic because of this.

- You can use hashing to write and read to databases.

- You can use a reverse proxy to hash data to find the location of
  where to shard.

Prev:
\[replication-and-sharding](replication-and-sharding.md)
Next: \[leader-election](leader-election.md)
