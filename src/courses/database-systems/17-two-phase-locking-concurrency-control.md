---
title: "Two-Phase Locking Concurrency Control"
pdf: "[[17-two-phase-locking-concurrency-control.pdf]]"
---

# Two-Phase Locking Concurrency Control

Prev: [[16-concurrency-control-theory]]
Next: [[18-timestamp-ordering-concurrency-control]]

## Transaction Locks

The DBMS has a centralized lock manager that decides whether a transaction can have a lock or not. There are two main kinds of locks:

- **Shared Locks (S-LOCK)**: A lock that allows multiple transactions to read the same object at the same time.
- **Exclusive Lock (X-LOCK)**: A lock that allows a transaction to modify an object. Only one transaction can hold an exclusive lock.

Transactions can be executed in the following fashion:

1. Transaction requests locks from the lock manager.
2. The lock manager grants or blocks requests based on what locks are being held by transactions.
3. Transactions release locks when they no longer need them.
4. The lock manager updates its internal lock-table and then gives locks to the requesting transaction.

## Two-Phase Locking

2PL is a pessimistic concurrency control protocol that determines whether a transaction is allowed to acces an object in the DB.

There are two phases:

**Growing**: The transaction requests a lock, and that request is either granted or denied.
**Shrinking**: The transaction enters this phase after releasing its first lock. It can only release locks previously acquired, and cannot acquire new locks.

2PL is sufficient to guarantee conflict serializability, but is susceptible to *cascading aborts*, where a transaction aborts which causes other transactions to be rolled back after the abort.

## Strong Strict Two-Phase Locking

Strong Strict 2PL, is a variant where transactions only release locks when finished. A schedule is strict if a value written bya  transaction is not read or overwritten by other transactions until that transaction finished. There is no shrinking like in regular 2PL.

This is better because there are no cascading aborts, and changes can be reversed by restoring the original values of modified tuples.

## 2PL Deadlock Handling

There are two main ways that 2PL handles deadlocks:

**Deadlock Detection**: The DBMS creates a waits-for graph. Nodes are transactions, and edge from $T_i$ to $T_j$, if transaction $T_i$ is waiting for transaction $T_j$ to release a lock. The system periodically checks for cycles in graphs and then makes a decision to break them.

- When the DBMS detects a deadlock, it will select a "victim" transaction to rollback and break the cycle.
- The victim transaction will either restart or abort.
- Some criteria to choose a victim include:
    1. By age (newest or oldest)
    2. By progress (least or most queries executed)
    3. By # of locked items (fewer or more)
    4. By the # of transactions that have to be rolled back for it
    5. # of times restarted in the past.
- The DBMS can also choose to rollback either the entire transaction or just enough queries to break the deadlock.

**DeadLock Prevention**: When a transaction tries to acquire a lock, if another transaction already holds the lock, do something to prevent contention.
- **Wait-Die** (Old waits for Young): If $T_1$ has a higher priority, then $T_1$ waits for $T_2$. Otherwise, $T_1$ aborts.
- **Wound-Wait** (Young waits for old): If $T_1$ has a higher priority, $T_2$ aborts. Otherwise, $T_1$ waits.

## Lock Granularities

If a transaction wants to update one billion tuples, it would have to ask the DBMS for a billion locks. That's expensive.
Instead, the DBMS can use a lock hierarchy that allows a transaction to take more coarse-grained locks in the system. If there's a large number of tuples that need to be mutated, instead of taking a billion locks, one table lock for exclusive access would suffice.

When a transaction acquires a lock for an object in this way, it implicitly acquires locks for all its children. For example, an exclusive lock on a table precludes any other readers or writers for that specific table.

**Intention Locks** allow a higher level node to be locked in shared or exclusive mode without having to check child locks.

- **Intention-Shared(IS)**: Indicates explicit locking at a lower level with shared locks
- **Intention-Exclusive(IX)**: Indicates explicit locking at a lower level with exclusive or shared locks
- **Shared+Intention-Exclusive(SIX)**: The subtree is locked explicitly in shared mode and explicit locking is done at a lower level with exclusive locks.

Prev: [[16-concurrency-control-theory]]
Next: [[18-timestamp-ordering-concurrency-control]]
