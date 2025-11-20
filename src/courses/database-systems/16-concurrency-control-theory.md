---
title: "Concurrency Control Theory"
pdf: "[[16-concurrency-control-theory.pdf]]"
---

# Concurrency Control Theory

Prev: [[15-query-planning-optimization-ii]]
Next: [[17-two-phase-locking-concurrency-control]]

## Transactions

Transactions allow for one or more operations to be grouped together.

Ex: Move $100 from Andy's bank account to his bookie's account

1. Check whether Andy has $100.
2. Deduct $100 from his account.
3. Add $100 to his bookie's account.

The scope of a transaction is inside the database.

We need a formal correctness criteria to determine whether an order of operations is valid.

## Definitions

A database is a set of named tuples (A, B, C, ..). A transaction is a sequence of read and write operations (R(A), W(B)).

The outcome of a transaction is either `COMMIT` or `ABORT`. Commits are saved, aborts are canceled.

Correctness Criteria: ACID
- Atomicity: All actions in the transaction happen, or none happen.
"All or Nothing"
- Consistency: If each transaction is consistent and the database is consistent at the beginning of the
transaction, then the database is guaranteed to be consistent when the transaction completes.
"It looks correct to me..."
- Isolation: The execution of one transaction is isolated from that of other transactions.
"As if alone"
- Durability: If a transaction commits, then its effects on the database persist.
"The transaction’s changes can survive failures..."

## ACID: Atomicity

The DBMS can guarantee atomicity of transactions in the following ways:

1. Shadow Paging

- Making copies of pages and transactions, and making changes to those copies. When the transaction commits, make the pages visible to others. This is kind of like RCU.

2. Logging

- DBMS logs all actions, so it can undo actions of aborted transactions.

## ACID: Consistency

The data in the database is correct, and the queries that the application asks about the data will return correct results.

Database Consistency:

- The database accurately represents the real world it is modeling.
- Transactions in the future see the effects of transactions committed in the past.

Transaction Consistency:

- If the database is consistent before the transaction starts, it will be consistent afterwards.

## ACID: Isolation

The DBMS provides the illusion that they are running alone in the system to transactions. They do not see the effects of concurrent transactions.

Concurrency Control Protocols:

A concurrency control protocol is how the DBMS decides the proper interleaving of operations from multiple transactions.

Two categories of concurrency control protocols:

1. Pessimistic: The DBMS assumes that transactions will conflict, so it avoids problems beforehand.
2. Optimistic: the DBMS assumes that conflicts between transactions are rare, so it chooses to deal with conflicts when they happen.

The order in which the DBMS executes operations is an execution schedule.

Serial Schedule: A schedule that does not interleave the actions of different transactions.
Equivalent Schedules: For any database state, the effect of executing the first schedule is identical to the effect of executing the second schedule.
Serializable Schedule: A schedule equivalent to some serial execution of the transactions.

If transactions are interleaved, it can create anomalies:

- Read-Write Conflicts (Unrepeatable reads): A transaction is not able to get the same value when reading the same object multiple times.
- Write-Read Conflicts (Dirty Reads): A transaction sees the write effects of a different transaction before it has been committed.
- Write-Write conflicts (Lost Updates): One transaction overwrites the uncommitted data of another concurrent transaction.

There are two types of serializability: Conflict and view. Conflict is more common.

Conflict Serializability

Schedules are equivalent to some serial schedule. If you can transform a schedule S into a serial schedule by swapping consecutive non-conflicting operations of different transactions.

A schedule S is conflict serializable if each transaction is a node, its transactions go in order, and its dependency graph is acyclic.

## ACID: Durability

All changes should be durable after a crash or restart. This should be done with either logging or shadow paging.

Prev: [[15-query-planning-optimization-ii]]
Next: [[17-two-phase-locking-concurrency-control]]
