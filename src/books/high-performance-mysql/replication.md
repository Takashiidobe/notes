---
title: "Replication"
---

# Replication

Prev: [query-performance-optimization](query-performance-optimization.md)
Next: [backup-and-recovery](backup-and-recovery.md)

Replication allows MySQL to be used for higher scale applications. The
documentation is a good source of information for this.

## Replication overview

Replication keeps data synchronized among database instances within the
same topology. A newer server can usually be a replica of an older
version, but newer servers can't be leaders for older servers.

Replication is good for scaling reads, because reads can be directed to
replicas, but doesn't scale with writes, because writes have to be
propagated through the system.

Some usages for replication involve:

1. Data distribution
2. Scaling read traffic
3. Backups
4. Analytics
5. High Availability
6. Testing MySQL upgrades

## How Replication Works

Replication is a three-part process:

1. The source changes its data in its Write-Ahead Log (binlog)
2. The replica copies the source's binlog to its own relay log.
3. The replica replays the events in the relay log, applying the changes
   to its own data.

This allows for the replication architecture to be asynchronous.

## Replication Under the Hood

### Choosing Replication Format

MySQL offers three different binary log formats for replication:

1. Statement-based,
2. Row-based,
3. Mixed.

This is controlled by the `binlog_format` configuration parameter.

Statement-based replication works by recording the query that changed
the data on the source.

The main draw is this is very small to replicate, but this also only
works on _pure_ functions. Imagine if you delete 1000 rows from a query,
but the query might return the rows in a random order. This will lead to
inconsistencies on the leaders and followers.

Row-based replication writes events to the binary log that indicate how
the row has changed. This is larger over the wire, but is deterministic.

Mixed tries its best to check when the query can be served by statement
based replication to maximize gain, but it doesn't always work. Stick to
Row-based replication.

### Global Transaction Identifiers

Until MySQL 5.6, a replica would keep track of what binary logfile and
position it was reading from when connected to a leader. But if the
leader disappears, or binlogs become unreadable, this fails.

Later on, MySQL added an alternate method for tracking replication with
global transaction identifiers (GTIDs).

This solves this problem. Enable this feature always.

### Making Replication Crash Safe

Replication can break in other ways. Here are some settings that are
recommended:

`innodb_flush_log_at_trx_commit = 1`
This ensures that every write to the bin log flushes the write buffer, which
writes to disk. This makes each transaction durable.

`sync_binlog = 1`
This variable controls how often MySQL synchronizes the binary log data
to disk. When this value is 1, this means before every transaction.

`relay_log_info_repository = TABLE`
This setting puts binlog information in InnoDB tables instead of on
disk.

`relay_log_recovery = ON`
This setting throws away all local relay logs when a crash is detected
and fetches the missing data from the source. This makes data in a crash
recoverable.

### Delayed Replication

You can have a delayed replica in your topology by having data online
and running but keeping it consistently behind real time by hours or
days.

Configure this by `CHANGE REPLICA SOURCE TO` and `SOURCE_DELAY`.

This can be useful where if you need to rollback to a previous state,
you can stop replication on a delayed replica to the GTID where the bad
change occurred (table dropped, corrupted data inserted).

If you do use this topology, remember that this node can never become a
leader, otherwise data loss will occur.

### Multithreaded Replication

MySQL used to apply replication in a single threaded mode only.

Nowadays, it can be done multithreaded, which is faster. There are two
modes, `DATABASE` and `LOGICAL_CLOCK`. The database option uses multiple
threads to update different databases. This is good if you have many
tables and one of them doesn't take a lot of updates. `LOGICAL_CLOCK`
allows for parallel updates against the same database as long as they
are part of the same binlog group commit.

You can set an artificial delay for `LOGICAL_CLOCK` replication with
`binlog_group_commit_sync_delay` (in microseconds) and
`binlog_group_commit_sync_no_delay_count`.

`replica_parallel_workers` should be turned to a non-zero value and
`replica_parallel_type` should be set to `LOGICAL_CLOCK`. As well, make
sure to set `replica_preserve_commit_order` so committing out of order
won't cause issues.

To measure how long a thread should wait:

```sql
UPDATE performance_schema.setup_consumers SET ENABLED = 'YES'
WHERE NAME LIKE 'events_transactions%';
UPDATE performance_schema.setup_instruments SET ENABLED = 'YES', TIMED = 'YES'
WHERE NAME = 'transaction';
```

Allow replication to process events for a time period and run this
query:

```sql
mysql> USE performance_schema;
events_transactions_summary_by_thread_by_event_name.thread_id AS THREAD_ID,
events_transactions_summary_by_thread_by_event_name.count_star AS COUNT_STAR
FROM events_transactions_summary_by_thread_by_event_name
WHERE
events_transactions_summary_by_thread_by_event_name.thread_id IN (SELECT
replication_applier_status_by_worker.thread_id
FROM replication_applier_status_by_worker);
+-----------+------------+
| THREAD_ID | COUNT_STAR |
+-----------+------------+
|   1692957 |      23413 |
|   1692958 |       7150 |
|   1692959 |       1568 |
|   1692960 |        291 |
|   1692961 |         46 |
|   1692962 |          9 |
+-----------+------------+
6 rows in set (0.00 sec)
```

As we can see, three or four threads is the best point. The fifth thread
only processes < 0.02% of the transactions.

### Semisynchronous Replication

In semisynchronous replication, every transaction that the leader
commits must be acknowledged by at least one replica.

This feature adds additional latency.

However, in MySQL, if no replicas acknowledge the transaction during the
time frame, MySQL goes back to Asynchronous replication, so this isn't
recommended.

Don't enable this.

### Replication Filters

Replication filters let you replicate just part of a server's data.

Don't enable this. It causes Data loss.

They also break point-in-time recovery.

## Replication Failover

There are ways to promote a replica from follower to leader.

### Planned Promotions

This can be done like so:

1. Choose the new Leader
2. Check the lag to make sure you are within a few seconds.
3. Stop taking writes on the leader by setting `super_read_only`.
4. Wait until replication is in sync by comparing GTIDs.
5. Unset `read_only` on target.
6. Switch application traffic to the target.
7. Repoint all replicas to the new source, using GTIDs and
   `AUTO_POSITION=1`

### Unplanned Promotions

If you don't have a live source to check:

1. Choose the replica
2. Unset `read_only` on the target.
3. Switch application traffic to the target.
4. Repoint all replicas to the new source.

Make sure when the former leader comes back online, it defaults to
`super_read_only` enabled, to prevent accidental writes to the node.

### Trade-Offs of Promotion

Maybe you may choose just to let your system stay down for a bit.

## Replication Topologies

MySQL can be set up for many replication topologies that we go over
here:

### Active/Passive

In Active/Passive, all reads and writes are sent to a single leader,
which then replicates to replicas (these do not serve reads).

#### Configuration

In this topology, the source and replicas should have similar hardware
characteristics.

#### Redundancy

You will want at least n + 2 servers (n being the number of active
servers), so 1 active server = 3 servers total. This lets you easily
provide updates.

#### Caveats

Your reads and writes cannot scale past one node worth of reads and
writes. Once you have more than that, you'll need to evolve out of this
topology.

### Active/Read Pool

In Active/Read Pool, all writes go to the leader, but reads can be
served from the leader or followers.

#### Configuration

The Leader and at least one or two of the replicas should have similar
performance characteristics for failover.

#### Redundancy

At least one server should have a setup that can read.

#### Caveats

Your application must have a tolerance for stale reads. You can never
guarantee a strongly consistent read, unless you force some reads to go
to the leader.

### Discouraged Topologies

#### Dual leader in active-active mode

Instead of having two passive servers, you have two active ones that
handle reads and writes, and they each propagate to each other. There's
no way to make this work without leader election. Avoid.

#### Dual leader in active-passive

Replication has been set up back to the active server in this case. This
adds complexity. Avoid.

#### Dual leaders with Replicas

Each leader has its own replicas that it maintains, while also
replicating between leaders. This is roughly the same as active-active.

#### Ring Replication

Ring replication is when 3 or more leaders are hooked together, where
each server is a replica of the server before it in the ring, and a
leader for the one after it.

If any server goes offline, this topology breaks. There's no advantages
to this topology.

#### Multisource replication

Mutli source replication involves putting two leaders updates into one
replication. This can be used to merge the data on two nodes into one
replica.

This can be useful for one off tasks like the above, but is generally
not recommended.

## Replication Administration and Maintenance

### Monitoring Replication

Replication increases the complexity of monitoring. You'll want to
monitor how long it takes for replicas to apply updates, and if the
replicas have had any errors.

You should monitor the following:

1. Disk space on leader and followers
2. State and errors should be monitored.
3. If using delayed replication, the delay is correct.

### Measuring Replication Lag

You can measure the replication lag in MySQL by looking at the
`Seconds_behind_source` column in `SHOW REPLICA STATUS`, but it's not
100% accurate for a few reasons:

1. This compares timestamps, which can be faulty.
2. The replica will report NULL if threads aren't running
3. Replication might've run into an error. If so, this column returns 0
   instead of an error.
4. The replica sometimes can't calculate lag. In this case it
   unhelpfully returns 0 or NULL.
5. Very long transactions can cause reported lag to fluctuate.

Instead, we recommend using a heartbeat record to check the lag between
the leader and replicas.

### Determining Whether Replicas are consistent with leaders

A replica would have an exact copy of its source in a perfect world. But
this can break in many ways. Here are some strategies:

1. Always run your replicas with `super_read_only` enabled.
2. Use row-based replication
3. Don't write to multiple servers in a topology at the same time.

## Replication Problems and Solutions

Replication is easy to set up on MySQL but confusing to debug. Here are
some problems:

### Binary Logs corrupted on Leader

If binary logs are corrupted on the leader, you'll also have to rebuild
your replicas.

### Non-unique Server IDs

If you set up your topology without unique server ids, you might notice
them working properly, or only one replica working properly.

### Undefined Server IDs

If you don't define the server ID, MySQL will appear to set up
replication for you but will not let you start the replica.

### Missing Temporary Tables

Temporary tables aren't replicated in statement-based replication. Use
row based replication.

### Not Replicating All Updates

If `SET SQL_LOG_BIN=0` is set, or bin log filtering is set, then you
might notice some updates not being propagated. Avoid Binlog filtering.

### Excessive Replication Lag

Excessive Replication lag can happen in many ways. To combat this, use
the following:

1. Multithreaded replication
2. Sharding
3. Temporarily lower durability

To lower durability, you can change the settings for `sync_binlog` and
`innodb_flush_log_at_trx_commit` to reduce write operations.

### Oversized Packets from the Source

If the leader's `max_allowed_packet` size doesn't match the replica's,
the leader can log a packet the replica considers oversized, which can
cause errors on the replica. Make sure to set them to the same number.

### No Disk Space

Make sure to keep an eye out for disk usage and setting the
`relay_log_space` configuration variable.

### Replication Limitations

MySQL server can have errors itself in replication, and these have
historically shipped on the first version of MySQL mainly.

Prev: [query-performance-optimization](query-performance-optimization.md)
Next: [backup-and-recovery](backup-and-recovery.md)
