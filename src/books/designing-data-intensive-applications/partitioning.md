---
title: partitioning
---

Prev: [replication](replication.md) Next:
[transactions](transactions.md)

# Partitioning

Partitions (also known as shards) occur when you break up a database
over multiple nodes. We have to shard instances when the data becomes
too large for one node to handle -- but we lose the ability to do joins
on one instance, so the data schema becomes harder to manage.

## Partitioning and Replication

Partitions are normally combined with replication, so copies of each
partition is stored on multiple nodes. This means that we have to update
copies too when we're updating one part of the data.

## Partitioning of Key-Value Data

How do you decide which records to store on which nodes? We want an
evenly distributed algorithm to distribute data, because otherwise some
nodes will take more of the data, or become **skewed**.

We could assign data to nodes randomly, but that has a downfall; we now
have to query all partitions to get one row.

We can do better.

### Partitioning by Key Range

One way is to split the data into a sorted range of keys. Assume you're
sorting alphabetical data into 5 partitions. Sorting by letter can lead
to hotspots (vowels are more common first characters than consonants) so
we'll have to try to evenly distribute by range.

One pitfall of this approach is that partitioning across time series
data can lead to hotspots. You can avoid this by allowing time series
data to go to a set of nodes, so writes could go from 1 - n nodes, and
all queries have to query those 1 - n nodes.

### Partitioning by Hash of Key

Because partitioning by Key Range can lead to skew, it is common to use
a hash of a key. This hash doesn't have to be cryptographically secure;
MD5 and FNV are commonly used. You assign each partition a range of
hashes and every key whose hash falls within that partition's range is
stored there.

Consistent hashing is commonly cited in the literature, but not commonly
used, so we should call it hash partitioning.

This, however, has the con that range queries now have to query all
partitions.

Cassandra compromises this by allowing **compound primary keys**. The
first part of the key is hashed to determine the partition, but the
other columns are used to sort the data in the SSTable in the partition.

### Skewed Workloads and Relieving Hot Spots

Hashing a key to determine its partition can help reduce hot spots; but
in the extreme case that one key contributes a lot of read/write volume
(like a celebrity tweeting and people retweeting in response) it's up
to the developer to reduce pressure. One way might be to add a random
number to the beginning or end of the key, and directing the read/write
to that partition.

Of course, this makes reads less efficient, since they now have to query
all partitions.

## Partitioning and Secondary Indexes

We've talked about a simple key-value model (just an indexed primary
key). But in RDBMS', it is common to have a more than one index.
Unfortunately, this doesn't map neatly to partitions.

### Partitioning Secondary Indexes by Document

Imagine you are operating a website for selling used cars. Each car has
a unique ID, and you partition by document ID. Let's say you want to
allow users to search for cars by color and make, and you have a
secondary index for both. Each partition can maintain a copy of
secondary indexes for color and make, and when a read query is issued,
the query can quickly resolve. (This is called scatter/gather).
Unfortunately, this has high tail latencies in practice, because of
network latency.

Writes can go directly to the partition that contain the document ID you
are writing to.

This strategy is sometimes called a local index, since each partition
has a copy of its own index.

### Partitioning Secondary Indexes by Term

We can somewhat combat this by having a global index that is replicated
and partitioned to store all secondary indexes.

We can imagine that this global index either contains a term or a hash
of the term. Partitioning by term makes range scans more efficient,
whereas partitioning based on hash gives a more even distribution of
load.

This allows us to query one node when doing reads to our global index,
but writes are slower and more complicated, because they might affect
multiple partitions of the index. This is extremely slow (and prone to
tail latency amplification) when doing synchronously, so this is
commonly done asynchronously. But if done asynchronously, we lose the
ability to read our writes. DynamoDB normally updates secondary indexes
within a second, but sometimes can take much longer due to this issue.

## Rebalancing Partitions

We may need to rebalance a partition because the query throughput
increases, the dataset size increases, or a machine fails.

Rebalancing should meet these criteria:

1.  The load should be shared fairly
2.  The database should accept reads/writes while rebalancing
3.  No more data should be moved than necessary, to make rebalancing
    fast and simple.

### Strategies for Rebalancing

Don't do hash mod N -> When adding new nodes to the system, most
records will have to find a new node, which makes rebalancing slow and
error-prone (due to replication lag).

#### Fixed number of partitions

Instead, create more partitions than there are nodes, and assign several
partitions to each node. If a node is added to a cluster, the new node
can take a few partitions from every existing node until partitions are
evenly distributed again. If a node is removed, that node gives each
other node an even distribution of its records.

This greatly reduces the amount of data that moves to n / m.

It is generally hard to create more partitions (there is ops load) so
you'll want to rarely do this.

#### Dynamic Partitioning

For databases with key range partitioning, like HBase, partitions are
dynamically generated; when they exceed a certain size, they are split
into two. Conversely, if a partition becomes too small, it can be joined
with a neighboring partition. If a node has too many partitions after a
split, partitions can be sent over the network using HDFS. This strategy
has the pro of less ops load, since the database automatically
partitions data.

#### Partitioning proportionally to Nodes

Cassandra has a fixed number of partitions per node. There's a fixed
number of partitions, which are evenly distributed per node. When more
nodes enter, partitions are evenly distributed and given to the new
node. This can lead to unfair splits when there's a smaller number of
partitions per node, but with 256 per node, this is rarer (by the law of
large numbers).

## Operations: Automatic or Manual Rebalancing

Automatic seems like a no-brainer, since it should require less ops load
than manual rebalancing; however, if rebalancing is done at an
inopportune time by the database, it can cause network overload and harm
system performance. Even worse, a node that's reachable might be
labeled as unreachable, skewing load to nodes that are thought to be
alive, which can crash the cluster. It's generally good for this reason
to have an operator commit rebalancing operations when prudent.

## Request Routing

Now that we have more than one database and computer, how do we reach
our databases? This is an instance of service discovery. There's a few
different approaches:

1.  Allow clients to contact any node through a load balancer. If the
    node doesn't contain the required data, that node can forward the
    request to the appropriate node, receive the reply, and return it to
    the client.

2.  Send all requests to a routing tier, which finds the applicable
    partition and queries that node before returning the response to the
    user.

3.  Allow clients to keep a list of all nodes, and directly query nodes.

We can defer this to a consensus algorithm load balancer (like etcd,
which uses raft, or zookeeper, which uses ZAB). Each node is required to
register with etcd/zk and zk manages consensus on all nodes.

Cassandra and Riak use a gossip protocol; requests can be sent to any
node, and that node forwards them to the appropriate node. This doesn't
require an intermediary like ZK or etcd.

## Parallel Query Execution

Some queries may be executed in parallel across the cluster. Massively
parallel processing (MPP) relational database products support a lot of
sophisticated queries that can be optimized in this fashion.

Prev: [replication](replication.md) Next:
[transactions](transactions.md)
