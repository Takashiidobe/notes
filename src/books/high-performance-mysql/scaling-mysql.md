---
title: "Scaling MySQL"
---

# Scaling MySQL

Prev: [backup-and-recovery](backup-and-recovery.md)
Next: [mysql-in-the-cloud](mysql-in-the-cloud.md)

This chapter walks us through ProxySQL and Vitess, accepted solutions to
scale writes.

## What is Scaling?

Scaling is the system's ability to support growing traffic.

Capability is the amount of work it can perform in a given amount of
time.

Scalability is the ability to add capacity by adding resources: It's
important to think of it in terms of:

1. Quantity of data
2. Number of users
3. User activity
4. Size of related data sets

## Read Versus Write-Bound Workloads

To scale, first figure out your workload. Is it primarily writes
(INSERT, UPDATE, DELETE) or reads (SELECT)?

Don't fall into the trap of analyzing QPS only.

### Read-Bound Workloads

If you start off with one leader, you can optimize indexes, queries, and
caching data. But eventually you'll have to add replicas to scale read
traffic.

### Write-Bound Workloads

When the bottleneck is write-bound, it's a bit more difficult. You can
scale vertically for a while, but once that hits its limit, you have to
think about how to split your data so that you can accept writes in
parallel on separate subsets. Sharding data means that joins become a
lot more problematic though, as they have to go to another node.

## Functional Sharding

Splitting your data is context dependent.

1. Split tables based on business function, like separating account
   signups from customer settings.
2. Split up data that has been intermingled that can be separated.

### Scaling Reads with Read Pools

Since Read Pools are replicated, you just need to stick a load balancer
in front of them. HAProxy is a hardware load balancer that works for
this, or Nginx also works.

Here's a sample HAProxy file that maps one virtual IP to two different
servers.

```conf
global
 log 127.0.0.1 local0 notice
 user haproxy
 group haproxy
defaults
 log global
 retries 2
 timeout connect 3000
 timeout server 5000
 timeout client 5000
listen mysql-readpool
 bind 127.0.0.1:3306
 mode tcp
 option mysql-check user haproxy_check
 balance leastconn
 server mysql-1 10.0.0.1:3306 check
 server mysql-2 10.0.0.2:3306 check
```

Balancing with `leastconn` is recommended in MySQL. `roundrobin` is
another setting, but it might leave some nodes overloaded.

### Managing Configuration for Read Pools

Now that we have a gate, we need a herder. Service discovery is a good
option to automatically discover what hosts can be on the list.

Keep the following in mind for service discovery:

1. How soon can it detect the failure of a host?
2. How fast does that data propagate?
3. When there is a database instance failure, how does configuration
   refresh on your load balancer?
4. Does the change of database members happen as a background process,
   or does it require severing existing connections?
5. What happens if service discovery itself is down?

### Health Checks for Read Pools

How do you check if a replica is healthy? You can use a heartbeat, but
keep in mind while adjusting it:

1. How much data staleness is acceptable?
2. What is the maximum acceptable query latency?
3. What retry logic exists for read queries?
4. How does the system behave in absence of data? Is this acceptable?

You should build a heartbeat endpoint for each of your MySQL servers.

### Choosing a Load-Balancing Algorithm

1. Random (A C B C B B)
2. Round-robin (A B C A B C)
3. Fewest connections
4. Fastest response
5. Hashed
6. Weighted

These all have their pros and cons. You might be tempted to disregard
random, but since it comes with little overhead, it actually works out
pretty well.

### Queueing

Scaling your application layer becomes more complex with write
transactions that favors consistency over availability.

More nodes results in more timeouts and retries. Before sharding the
data, we can use queues.

With a queue, the web server places a request on a queue, which is then
picked up by a server and then returned. Thus, the server has to poll
for the response and give it back to the client or the client can come
back later to see their response.

### Scaling Writes with Sharding

Sharding means to split your data into different, smaller database
clusters so that writes can be executed on more writes on moer source
hosts. There are two types.

Functional Partitioning divides different nodes to different tasks.

Data sharding splits the data into smaller pieces, and stores them on
different nodes.

Most applications have some logical data set that could be sharded. For
example, if an account should be able to query a set of data, you can
place an account and all its relevant data on a shard.

### Choosing a Partitioning Scheme

Sharding by a hash of each table's primary key scales poorly, because
you have to check other shards for data you need.

All queries should be localized to one shard if possible.

Try to find a partition key that lets you avoid cross-shard queries as
much as possible.

### Multiple Partition keys

If you have data that touches multiple partitions (like user id -> book
id) then you can shard users and books together.

### Querying Across Shards

Most sharded applications have at least some queries that need to
aggregate or join data from multiple shards. These queries are slow, and
difficult to implement. You'll need to aggressively cache, and use
summary tables, which traverse all shards and store results redundantly
on each shard.

Maintaining data consistency is also harder. Foreign keys don't work
across shards.

### Vitess

Vitess is a database-clustering system for MySQL.

It does the following:

1. Horizontal Sharding support
2. Topology management
3. Leader node failover management
4. Schema change management
5. Connection Pooling
6. Query Rewriting

Vitess has the following perks:

1. Preference for using smaller instances, to reduce blast radius.
2. Replication and automated write failover to increase resilience
3. Durability using semisynchronous replication.

### ProxySQL

ProxySQL is similar, and provides a layer between application code and
the database to increase consistency and availability.

Prev: [backup-and-recovery](backup-and-recovery.md)
Next: [mysql-in-the-cloud](mysql-in-the-cloud.md)
