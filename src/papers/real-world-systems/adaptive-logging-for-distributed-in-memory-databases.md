---
title: "Adaptive Logging For Distributed In Memory Databases"
pdf_url: "[[adaptive-logging-for-distributed-in-memory-databases.pdf]]"
---
This paper suggests a new adaptive scheme for main memory databases. Normally, databases use ARIES to persist changes to a WAL. This works for normal databases that persist to disk, but is slow for main-memory databases, and distributed dbs.

The paper combines two different mechanisms for logging transactions:

1. ARIES, which persists the tuples that have changed
2. Command logging, which only logs transactions and their parameters -- note that this only works for updates that are pure (that rely only on their parameters). e.g. `set updated_at = CURRENT_TIMESTAMP` is not pure.

Both have a major con:

1. ARIES is slow for in-memory DBs in general
2. Command logging makes recovery serial for distributed settings.
## Distributed Command Logging

- First, build a dependency graph over logged transactions to tuples that they affect
- Transactions are grouped into processing groups -- different groups can be replayed in parallel since they don't affect the same tuples.
- This increases throughput, unless some tuples are hot, which have to be put in the same group.

## Adaptive Logging

- Most transactions use cheap command logs -- if a transaction is thought to cause a bottleneck/go to a bottleneck tuple(s), then ARIES style data-logging records are emitted.
- ARIES style data logging breaks up long transaction chains by materializing transactions, so any consumers of the transaction log can materialize and continue from this point, unlike command logs, which require applying one by one.
- So, if a transaction is in a critical part of the dependency graph, which affect hot tuples or have many dependents, log it in ARIES form.

## Results

The team tried it out on H-Store, which is an in-memory OLTP engine that has in-memory. They had in-memory indexes of transaction footprints to help with online decision logic and recovery scheduling.

- **Adaptive logging** had similar throughput to **command logging**.
- Recovery was **10x** as fast as **command logging** in a distributed setting.
- **Adaptive logging** scales better by leveraging parallelism.