---
title: replication
---

# Replication

Prev:
[encoding-and-evolution](encoding-and-evolution.md)
Next: [partitioning](partitioning.md)

Replicating data keeps a copy of the same data on multiple machines that
are connected via a network.

You may do this for the following reasons:

1.  To keep data geographically close to your users (reduce latency)
2.  To allow the system to continue to work even if parts have failed
    (increase availability)
3.  To scale out the number of machines (improve read throughput).

We're assuming that the dataset can fit on a single machine, and talk
about single-leader, multi-leader, and leaderless replication.

## Leaders and Followers

Each node that stores a copy of the database is sometimes called a
`replica`. Reads can be served by any one of the nodes, while writes
have to be served by all of the nodes. One way is through leader-based
replication.

1.  One of the replicas is designated as the leader. All writes go to
    the leader, and the leader first writes new data to its storage.
2.  The leader sends the data change to all of its followers as part of
    a replication log. Each leader takes the log and updates its local
    copy of the database to match the leader's.
3.  When a client wants to read from the database, it can read from any
    of them.

### Synchronous vs Asynchronous Replication

#### Synchronous

There are two ways to replicate, either asynchronously or synchronously.
Assuming a 3 node quorum, with synchronous replication, writes are first
processed on the writer, and sent to a follower. When that follower has
acknowledged the write, the leader replies back to the client saying
that the write is processed.

Synchronous replication can take a very long time, since networks can
have exponential delay, or the follower node may have fallen behind on
replication.

As well, if (n / 2) + 1 writes are not processed, the write cannot
succeed.

However, in exchange for this, you are guaranteed that at least one
follower is up to date with the leader should the leader fail.

#### Semi-synchronous

You may choose to implement a semi-synchronous approach, where one node
is synchronous and the other is asynchronous. This has the advantage of
having some extra availability and consistency in-exchange for medium
performance.

#### Asynchronous

An Asynchronous approach is when only the leader needs to process writes
before acknowledgement that the write was successful is sent to the
user. This has the advantage of the best performance and write
availability, but the lowest durability. If the leader fails after the
leader acknowledged a write to a client but before the write was
propagated to the followers, the write is lost. As well, clients lose
the ability to read their writes, because it is possible to make a read
request before the write has propagated to all followers.

### Setting Up New Followers

We want to get a copy of the consistent state of the database onto a new
copy. But since we're serving writes while we're doing so, we can't
do a simple file copy. What do we do?

1.  Take a consistent snapshot of the leader's database at some point
    in time.
2.  Copy the snapshot to the follower node.
3.  When copying the snapshot has finished, the follower requests the
    leader for all changes since the snapshot, using the log sequence
    number/binlog.
4.  The follower is ready to take writes from the leader.

### Handling Node Outages

Our goal is to be able to reboot machines without downtime (maybe
because of a kernel security patch).

#### Follower failure: Catch-up recovery

Followers persist writes to their WAL, so if a follower crashes, it can
ask the leader for writes after that point and request those changes.
When it catches up, it can serve reads and writes again.

#### Leader failure: Failover

What do we do if the leader fails?

1.  Determine that the leader has failed: if the leader doesn't respond
    to a heartbeat (maybe in 15 seconds) we can assume it is dead.
2.  Choosing a new leader: The followers go through an election process
    and elect the follower with the most up-to-date changes from the
    leader.
3.  Reconfiguring the system to use the new leader: Clients send write
    requests to the new leader, and when the previous leader comes back,
    it must know it has become a follower, and not serve writes.

There are lots of problems:

- If using asynchronous replication: what happens to writes that were
  acknowledged by the old leader but not propagated to the followers?
  The most common is to get rid of those writes, which can violate
  client's durability guarantees.
- Discarding writes is dangerous if other systems rely on the
  database. For example, at github, an out-of-date mysql follower was
  promoted to leader. The follower reused some primary keys that were
  used by the previous leader, while a redis service relied on the
  primary keys being monotonic from mysql. This caused some data to be
  disclosed to the wrong users.
- In certain situations, two nodes might both believe they are the
  leader, and both try to serve writes. If so, there's no easy way to
  reconcile the writes.
- Be careful about setting the right timeout; if the timeout is too
  short, there might be unnecessary failovers, which would increase
  load on the rest of the system.

## Implementation of Replication Logs

### Statement-based replication

Statement-based replication involves logging every write request
(statement) and then sending that log to followers.

This sounds reasonable except for these caveats:

1.  Any statement that isn't deterministic (e.g. `NOW()` or `RAND()`)
    will generate a different value on each replica
2.  If statements use an autoincrementing column, they must be executed
    in the same order on the follower as the leader.
3.  Statements that have side effects (triggers, stored procs,
    functions) will cause followers to be out of sync with the leader.

### Write-ahead log (WAL) shipping

If using SSTables and LSM-Trees, a log is the main place for storage. If
using B-Trees, a modification is written to a write-ahead log.

A WAL contains details of which bytes were changed in which disk blocks.
This makes it so replication is closely coupled to the storage engine.
If the storage format changes from one version to another, it is not
possible to replicate from leader to follower without downtime (as both
need to be upgraded to a consistent version in tandem). If the formats
are compatible, this can be done without downtime (upgrade a node, sync
both, upgrade the other node, sync them).

#### Logical (row-based) log replication

To decouple the WAL from the storage format, we can employ a logical log
(like MySQL's binlog). A logical log is a sequence of records
describing writes to database tables per row:

For an inserted row, the log contains the new values of the columns. For
a delete, it contains information that uniquely identifies the row. For
an update, the log contains information to uniquely identify the updated
row and new values of all columns.

#### Trigger-based replication

If you only want to replicate a certain table or a section of a table,
you might resort to a trigger. A trigger listens to reads and writes on
a table and executes a specific action.

You may want to replicate a specific table's updates, so when an update
comes to that table, you might write a trigger to propagate that update
to another table.

This is error-prone and comes with more overhead than previous
approaches, but can be useful for its flexibility.

## Problems with Replication lag

Most workflows are read-heavy, so the most common option is to increase
the number of followers that contain a copy of the data to serve reads.
This is attractive, because it increases availability and throughput,
but is only achievable with asynchronous replication. Asynchronous
replication allows for `eventual consistency`, which means that writes
propagate to followers at some later time, a weaker form of consistency
than `strong consistency`. Thus, if a client reads from an Asynchronous
follower after doing a write, it cannot `read its writes`, and gets
conflicting information (the write succeeds, but reading that same data
does not).

### Reading Your Own Writes

Many applications allow a user to `Read their own writes`, where they
can submit a write and then immediately verify it was correctly
persisted. If a client does this on an asynchronously replicated system,
the read may fail, which would make them unhappy.

How do we solve this?

- When reading something that the user may have modified, read it from
  the leader, otherwise, read it from the follower. This requires that
  there is some way to quickly distinguish what is "yours", possibly
  through user id or other primary key.
- If a user can update almost anything on the system, you may choose
  to use a timestamp based strategy instead. Track the last update of
  the row we're trying to read. If it's been less than a minute, for
  example, the leader should serve that read. Otherwise, a follower
  can.
- The client can remember the timestamp of its most recent write.
  Then, the system can ensure that the replica serving reads is
  updated to that point. If not, serve the read from the leader.

What happens if this is done from multiple devices?

- You'll want to read your writes across devices. You also can't
  trust timestamps across devices, so you'll need to find another way
  (possibly using a centralized server).

## Monotonic Reads

It is also possible to see reads go back in time with asynchronous
replication. Imagine you make one read to two different databases, one
which has replicated and another which hasn't fully replicated. If you
get back the read from the replicated node first, you'll see that the
write has processed and read the value. If you then get the query from
the node which hasn't fully replicated, the read will return nothing.
Thus, it seems like the write succeeded at t1 and then disappeared by
t2.

- One way to combat this is making sure that reads from a user always
  goes through the same replica, so this stops becoming an issue.

### Consistent Prefix Reads

Another anomaly is when causal violations occur. Let's say w1 must come
before w2, because w1 creates a row and w2 updates it.

Imagine these statements:

1.  CREATE person with name Joe and age 22
2.  SET age to 23 where name = Joe.

Result: Joe is a person with age 23.

We create and then update. However, if the second query is processed
before the first, this happens:

1.  SET age to 23 where name = Joe. (_No rows are updated here_)
2.  Create person with name Joe and age 22.

Result: Joe is a person with age 22.

It is difficult to solve this, since different partitions operate
independently, and there is no global ordering of writes. We can force
an ordering, but that comes at some performance cost.

### Solutions for Replication Lag

If the system you're working on can function with replication lag and
weaker consistency guarantees, that's good. If not, you may want to
pursue distributed transactions or use multi-leader or leaderless
strategies.

## Multi-leader Replication

Instead of having just one leader, have multiple.

### Use Cases for Multi-Leader Replication

#### Multi-datacenter operation

If you have multiple datacenters, you may want multiple leaders, one for
each data-center.

This involves:

1.  Better performance: Since writes can go through the local datacenter
    and be replicated asynchronously later on.
2.  Tolerance of datacenter outages: if the datacenter with the leader
    fails, another follower in a datacenter can be promoted.
3.  Tolerance of network problems: Inside the datacenter, there is
    better internet than between datacenters. Also, with multiple
    leaders, writes can be processed even if the leader fails.

#### Clients with offline operations

Applications like a calendar app which serve writes from multiple
devices (phone, computer, tablet, etc) per user and reads from all of
those devices while offline is a good example. The device should be able
to persist offline changes and sync them when going online. As well, it
should be able to resolve conflicting events.

#### Collaborative editing

Applications like google docs allows multiple people to concurrently
edit a document. Our normal single-leader approach is far too slow,
since each user would need to get a lock on the document before making
an edit.

### Handling Write Conflicts

Consider two users edit the title of a document locally. When changes
are synced upstream, there are conflicts.

#### Synchronous vs asynchronous conflict detection

If conflict detection is synchronous, there would be no point in having
a multi-leader setup. Writes would need to propagate to all followers
before being accepted, which is moot for a multi-leader setup.

#### Conflict avoidance

You can try for a strategy where writes for a record go to a particular
leader, and you must obtain a lock from the leader to write to said row.
This allows a simple setup, but when a datacenter goes down, this might
fail later on.

#### Converging toward a consistent state

A single-leader database applies writes in a sequential order. With a
multi-leader database that's impossible, because in the case above,
with editing the wiki title, the writes look like A -> B for node 1 and
A -> C for node 2. Which write wins? To deal with that, here are some
ways to achieve convergent conflict resolution:

- Give each write a unique ID, and pick the write with the highest ID.
  This is called Last Write Wins (LWW) and is popular, but prone to
  data loss.
- Give each replica a unique ID and let writes that originated at a
  higher number replica the win. This also causes data loss.
- Merge the values together, using an operational transform or a CRDT.
- Prompt the user to resolve the conflict at a later time.

#### Custom conflict resolution logic

You can execute conflict resolution logic on read or on write.

- On write: When there's a conflict in the log of replicated changes,
  call the conflict handler. (Bucardo) does this.

- On read: Conflicting writes are stored, and when read, calls the
  conflict handler. (CouchDB) does this.

Automatic Conflict Resolution:

- CRDTs (Conflict-free replicated datatypes) are data structures that
  can be concurrently edited by multiple users, and automatically
  resolve conflicts in sensible ways. Riak uses them.
- Mergeable persistent data structures track history explicitly, and
  use a three-way merge function. Git uses this.
- Operational Transformation is a conflict resolution algorithm behind
  microsoft word and google docs. It is used to resolve conflicts in
  an ordered list of items, like text in a document.

#### What is a conflict?

Imagine booking a meeting room; if two groups simultaneously book the
meeting room, only one can win. Who should win?

## Multi-leader replication topologies

With two leaders, replication requires bidirectional synchronization
between two nodes. However, with 3 nodes, there can be more popular
setups.

Circular:

write -> n1 -> n2 -> n3 -> n1

Writes are propagated from node to node in order. If the write has been
serviced (e.g. the write is back at node 1) the write is deemed
successful and stops here.

Star Topology:

write -> n1 <-> n2 ^ | v n3

Writes are served to one root node, where it is pushed to all other
nodes. If the write comes back to the root node, the write is
successful.

All to all topology:

         n2
         ^
         |
         v

write -> n1 <-> n3

Writes are served to all other leaders.

The circular and star topologies perform the best, but have no
redundancy. If one node fails, the system can fail.

As well, there is poor support for multi-leader setups in databases like
MySQL and Postgres

## Leaderless Replication

DynamoDB is a popular database that has a leaderless replication scheme;
clients send writes to multiple replicas, without enforcing a particular
ordering of said writes.

### Writing to the Database When a Node Is Down

Imagine a leaderless replication setup with 3 nodes. A client issues a
write request to all three nodes, but one is down, so two writes
succeed. That is good enough for quorum, and so the write is considered
successful. Let's say you issue reads to only one replica; you may get
stale data since one node didn't accept the write. Thus, in order to
have consistent reads and writes, you must read from all the nodes as
well, and version numbers are used to determine newer values.

### Read repair and anti-entropy

If a node is down, there should be a way of bringing it in sync. How is
that done?

- Read Repair

When a client makes a read from several nodes in parallel, it can detect
stale responses. Let's say one node gives a value from version 6, but
all other nodes give a value from version 7. The client can write the
newer value back to that replica. This is good for maintaining consensus
for values that are frequently read.

- Anti-entropy process

A background process checks for differences in data between replicas and
syncs them together.

#### Quoroms for reading and writing

If there are n replicas, every write must be confirmed by w replicas and
we must query r replicas. As long as `w + r > n`, we will get an
up-to-date value when reading. In this case, w = 2 and r = 2.

In dynamo style DBs, these parameters are configurable. Normally, we'll
calculate w and r as w = r = (n + 1) / 2 (rounded up).

Thus, if n = 3, w = 2, and r = 2, we can tolerate one unavailable node.
With n = 5, w = 3, and r = 3, we can tolerate two unavailable nodes.

#### Limitations of Quorom Consistency

If we follow the rule w + r > n, every read should return the most
recent value written. Often, r and w are chosen to be a majority of
nodes, but quorums aren't always majorities. As long as they overlap in
at least one node, our guarantees are kept. However, there are edge
cases where stale values are returned:

- If a sloppy quorum is used, the w writes may end up on different
  nodes than the r reads, which can return stale values.
- If two writes occur concurrently, the only safe solution is to
  merge. If we choose LWW, we'll have data loss.
- If a write happens concurrently with a read, should we return the
  new value or the old value?
- If a write succeeded on some replicas but failed on others, and
  isn't rolled back, subsequent reads may or may not return the value
  from that write.
- If a node carrying a new value fails, and its data is restored from
  a replica carrying an old value, it may break the quorum condition.
- There are other edge cases where the write may not propagate as
  expected.

#### Monitoring Staleness

Staleness in a leaderless replication setup is harder to measure than in
one with a leader. Since a leader based system has a replication log on
the leader and followers, we know how far behind each follower is. If we
use read repair, if a value isn't frequently read, it may be far behind
on some replicas. With anti-entropy, if the background job hasn't run
in a while, it may also be out of date.

### Sloppy Quorums and Hinted Handoff

Databases with properly configured quorums can tolerate node failures
without failover. However, if a network connection cuts off a client
from a lot of database nodes.

There are times when we can connect to some database nodes during a
network partition, just not the number required to build a quorum. If
so, what do we do?

- Return an error
- Accept reads and writes anyway, and have writes go to as many
  reachable nodes as possible and reach the rest later.

The second is a `sloppy quorum`. writes and reads can be successful even
without a quorum. But by accepting this tradeoff (for greater
availability and less latency), you cannot be sure to read the latest
value for a key, because even if w + r > n, the latest value may have
been written outside of n.

When the value is eventually written, to the nodes it needs to go to,
this is called hinted handoff.

#### Multi-datacenter operations

Leaderless replication is also suitable for multi-datacenter oepration,
since it is designed to tolerate conflicting concurrent writes.

Cassandra and Voldemort allow you to specify how many n replicas are in
each data center, and writes can succeed when a quorum is built in each
datacenter.

## Detecting Concurrent Writes

Dynamo-style databases allow several clients to concurrently write to
the same key. Events may arrive in a different order at different nodes
due to network delays and other failures.

Nodes should become eventually consistent, so they should converge
towards the same value.

### Last Write Wins

One approach is only storing the most recent value for a key,
determining this via a timestamp. However, there are many cases when a
write may make it to one node first, another node second, and not make
it to the third node. How do we determine order then?

LWW achieves the goal of eventual convergence, but at the cost of data
loss. Some writes that were acknowledged will be lost.

### The "happens-before" relationship and concurrency

- If A creates a value and B updates that value, then B is dependent
  on A.
- If A and B update a previously created value, C, then there is no
  causal dependency.

If B relies on A, we know A must come before B even if they come in the
wrong order. If A relies on B, the inverse is true. Or A and B have no
relation.

How do we tell the order of A and B?

### Capturing the happens-before relationship

We can create an algorithm to capture correctly merging values:

- The server maintains a version number for every key, and increments
  the version number every time that key is written, and stores the
  new version number with it.
- When a client reads a key, the server returns all values that
  haven't been overwritten, and the latest version number. A client
  must read a key before writing.
- When a client writes a key, it must include a version number from
  the prior read, and merge together all values it received in the
  prior read.
- When the server receives a write with a particular version number,
  it can overwrite all values with that version number or below, but
  it must keep all values with a higher verison number.

#### Merging Concurrently written values

With a write only configuration,we have to merge siblings by taking the
union. The two final siblings of a grocery cart example are [milk,
flour, eggs, bacon] and [eggs, milk, ham]. The union is [milk,
flour, eggs, bacon, ham], which is the correct answer.

However, if we support deletions, we need a version vector to make sure
that we can delete a particular item, which can be done with a
tombstone.

#### Version Vectors

We've assumed the above with one node. What happens when there are
multiple nodes? Then each node is required to keep a version vector, or
a version number per replica as well as per key, which can be diffed to
process a write.

Prev:
[encoding-and-evolution](encoding-and-evolution.md)
Next: [partitioning](partitioning.md)
