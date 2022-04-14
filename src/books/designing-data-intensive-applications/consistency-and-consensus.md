---
title: consistency-and-consensus
---

Prev: [distributed-systems-trouble](distributed-systems-trouble.md)
Next: [batch-processing](batch-processing.md)

## Consistency Guarantees

Most replicated databases provided eventual consistency, where if you
stop writing to the database and wait some amount of time, eventually
reads to all nodes will return the same value.

That means no Reading your Writes.

## Linearizability

Linearizability means that a system appears as if there is only one copy
of the data, and all operations are atomic.

As soon as one client successfully completes a write, all clients see
the value written.

Linearizability is kind of like having a switch that flips a write to
display to all clients at once.

Serializability != Linearizability. Serializability is for transactions,
meaning that transactions behave as if they were executed in a serial
order, whereas linearizability is for consistency.

## Relying on Linearizability

### Locking and leader election

A system that uses single-leader replication needs to ensure that there
is one leader. To do this, linearizable locks are required. All nodes
must agree who owns the lock.

### Constraints and uniqueness guarantees

Uniqueness constraints are common in databases. To implement this,
you'll need linearizability (without a switch of when a write succeeds,
two clients could write to different nodes and claim the same resource,
which would be an error).

This also happens for bank balances in transfers, selling more items
than you have in stock at a warehouse, or two processes write to the
same file.

### Cross-channel timing dependencies

In the example provided (Bob refreshes his page to find Germany won the
world cup, Alice refreshes her page, and doesn't see the same result),
linearizability is violated because Bob can see the result but Alice
cannot. This might happen in an image resizing service, where a client
may upload an image, then receive a message that it was properly
resized, then try to get that resized image and get nothing, because the
image resizer is still resizing the image.

## Implementing Linearizable Systems

1. Single Leader (potentially linearizable)

- If reads go through the leader, and the leader is correct, the system
  is linearizable. However, if the system is in a split-brain phase,
  then it will not be.

2. Consensus algorithms (linearizable)

- Consensus algorithms use locks to implement linearizable storage
  safely, which allows for leader election (how etcd and zookeeper
  work).

3. Multi-leader replication (not linearizable)

- Because multi-leader replication concurrently process writes and
  asynchronously replicate, they can produce writes that require
  resolution, and are thus not linearizable.

4. Leaderless replication (not linearizable)

- leaderless systems, like dynamo, aren't linearizable, because quorom
  reads may be configured to not be. Last write wins, like Cassandra,
  which uses clocks, are also not linearizable.

### Linearizability and Quorums

Dynamodb style quorums are linearizable if a reader performs read repair
synchronously, before returning results to the application.

### The Cost of Linearizability

Let's discuss two datacenters that are connected. Generally a
multi-leader setup is preferred, because if there's a network partition
between data centers, reads and writes can process as normal inside of
each data center.

If single-leader replication is used, then clients connected to follower
datacenters cannot contact the leader, so they cannot make _any_ writes
to the database, nor any _linearizable_ reads (i.e. data may be stale).

So, linearizability sacrifices availability for a consistent view of the
data.

### The CAP theorem

- An application that requires linearizability cannot make progress
  during a network partition.
- An application that does not require linearizability can make
  progress, but its behavior is not linearizable.

### Linearizability and network delays

Linearizability has a significant performance penalty. Even RAM on a
multi-core CPU is not linearizable for performance reasons, values are
not linearizable unless fenced (synced).

## Ordering Guarantees

### Ordering and Causality

Ordering is useful because it imposes causality (A came before B, so A
cannot rely on B).

A system that obeys an ordering imposed by causality is _causally
consistent_.

A total ordering allows any two elements to be compared - given two
items, you can always say which one is greater and which one is smaller.

A partial ordering, like sets, is where some items are incomparable
(floats and sets follow this property).

Causality defines a partial order -- some operations are concurrent, and
therefore happen at the same time, but some events happen before and
some events happen after.

For a linearizable system, which has a total ordering, there can be no
concurrent operations.

### Linearizability is stronger than causal consistency

Linearizability implies causality, but not all applications require it.
To determine causality, all reads must be versioned. This can be
captured with a version vector.

### Sequence Number Ordering

We can use _sequence numbers_ or _timestamps_ to order events -- a
logical clock can provide numbers to generate a total ordering. We can
use a lamport timestamp for this. Lamport timestamps work for partial
ordering, and are much more compact than version vectors.

### Timestamp ordering is not sufficient

Lamport timestamps aren't sufficient enough to guarantee uniqueness --
imagine two clients trying to reserve the same username. You can only
disambiguate the earlier call after the fact. We need total order
broadcast.

## Total Order Broadcast

This requires two properties:

1. Reliable delivery (a message delivered to one node is delivered to
   all)
2. Totally ordered delivery (messages are delivered to every node in the
   same order).

### Using total order broadcast

Total order broadcast is implemented by appending to a write-ahead log
in an order, where every node must process each message in order.

Prev: [distributed-systems-trouble](distributed-systems-trouble.md)
Next: [batch-processing](batch-processing.md)
