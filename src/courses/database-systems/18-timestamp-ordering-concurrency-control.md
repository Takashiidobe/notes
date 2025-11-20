---
title: "Timestamp Ordering Concurrency Control"
pdf: "[[18-timestamp-ordering-concurrency-control.pdf]]"
---

# Timestamp Ordering Concurrency Control

Prev: [[17-two-phase-locking-concurrency-control]]
Next: [[19-multi-version-concurrency-control]]

## Timestamp Ordering Concurrency Control

Timestamp ordering (T/O) Concurrency Control is an optimistic concurrency control protocol, where the DBMS assumes that transaction conflicts are rare. Instead of using locks, the DBMS uses timestamps to determine the serializability order of transactions.

Each transaction $T_i$ is assigned a unique fixed timestamp that is monotonically increasing. Set $TS(T_i)$ to be the timestamp for transaction $T_i$, and let timestamps be assigned at different times during the transaction.

Thus, if $TS(T_i) \lt TS(T_j)$, then the DBMS must ensure that the execution schedule is equivalent to a serial schedule where $T_i$ appears before $T_j$.

There are a few implementation strategies including:

- System clock
- Logical counter
- Hybrid

## Basic Timestamp Ordering (Basic T/O)

Every database object, $X$ is tagged with the timestamp of the last transaction that successfully executed a read or write.
Thus, $W-TS(X)$ is the write timestamp of object $X$, and $R-TS(X)$ is the read timestamp of object $X$.

The DBMS checks timestamps for each operation, and if a transaction tries to access an object from the future, the DBMS aborts that transaction and restarts it.

**Read Operations**:
- If $TS(T_i) \lt W-TS(X)$ this violates the timestamp order of $T_i$ with regard to the writer of $X$. Thus, it is restarted.
- Else:
    - Allow $T_i$ to read $X$.
    - Update $R-TS(X)$ to $max(R-TS(X), TS(T_i))$.
    - Optional: Make a local copy of $X$ to ensure repeatable reads for $T_i$.

**Write Operations**:
- If $TS(T_i) \lt R-TS(X)$ or $TS(T_i) \lt W-TS(X)$, abort and restart $T_i$.
- Else:
    - Allow $T_i$ to write $X$ and update $W-TS(X)$ to $T_i$.
    - Create a local copy of $X$ to ensure repeatable reads for $T_i$.

This basic protocol is conflict serializable. It cannot have deadlocks because no transaction ever waits. However, long transactions can starve if short transactions keep causing conflicts.

As well, schedules are not recoverable in this case.

## Optimistic Concurrency Control (OCC)

For transactions where conflicts are rare, and transactions are short lived, it makes sense to optimize for that case. Optimistic Concurrency Control does that.

The DBMS creates an **exclusive area** for each transaction, where:

- All modifications are applied to the workspace
- Any object read is copied into the workspace
- No other transactions can read the changes made by another transaction in its private workspace.

When a transaction commits, the DBMS compares the transactions' workspace write set to see whether it conflicts with other transactions. If there are no conflicts, it is committed.

There are three phases:

- Read Phase: Track the reads + writes of the transaction.
- Validation Phase: When a transaction commits, check whether it conflicts with other transactions.
- Write Phase: If validation succeeds, commit the changes. Otherwise, abort and restart.

### Validation

Validation makes sure at least one of these three cases hold:

Assuming $TS(T_i) \lt TS(T_j)$:

1. $T_i$ completes before $T_j$ begins
2. $T_i$ completes before $T_j$ starts its write phase, and $T_i$ does not write to any object read by $T_j$
3. $T_i$ completes its Read phase before $T_j$ completes its Read phase, and $T_i$ does not write to any object that is either read or written by $T_j$.

Issues:
- High overhead for copying data locally per transaction.
- Aborts are more wasteful, due to occuring after a transaction was executed.
- Suffers from timestamp allocation bottlenecks.

## Partition-Based Timestamp Ordering

In OCC, the database needs to check the entire database for conflicts across transactions. This can be made more efficient if it is done for partitions, as long as transactions are not cross-partition.

In this case, the database chops up databases into disjoint subsets called partitions, and only checks for conflicts between transactions that are running in the same partition.

This can only really work for local databases, since distributed transactions are slower than local transactions.


Prev: [[17-two-phase-locking-concurrency-control]]
Next: [[19-multi-version-concurrency-control]]
