---
title: "Isolation"
---

# Isolation

Prev: [introduction](introduction.md)
Next: [pages-and-tuples](pages-and-tuples.md)

Invariants in the database can be enforced using constraints, but the
whole system might have stronger consistency requirements.

Thus, databases must provide transactions, where many commands are
grouped together.

ANSI SQL provides information of four isolation levels and some
anomalies that may or may not occur for concurrent transactions using
those isolation levels.

## Anomalies

### Lost Update

Lost update occurs when two transactions read the same row, and try to
do an update without taking into account the other change.

Imagine a row represents an account balance, $1000, and T1 and T2
concurrently want to increase it by $100.

Under this anomaly, both T1 and T2 change the balance to $1100, and then
commit their change, losing $100 in the process.

This is forbidden by the standard for all levels.

### Dirty Reads

Let's say a transaction, T1 transfers $100 to an empty account, but does
not commit this change. Another transaction, T2 reads the account state
and withdraws $100 from the account to make a payment to another
account. In the meanwhile, T1's transaction is aborted, and rolled back.

Thus, T2 reads uncommitted data and violates the invariant.

The standard allows dirty reads for Read Uncommitted.

### Non-Repeatable Reads

Let's say a constraint prevents negative balances for bank accounts. Say
T1 wants to withdraw $100 from an account. It can, as it checks the
balance is $1000. T2 withdraws all the money from the account and
commits, making the balance negative.

The standard allows non-repeatable reads for Read Committed and all
levels below.

### Phantom Reads

Phantom reads occur when one transaction executes two identical queries
returning a set of rows that meet a condition, while another transaction
adds rows matching this condition and commits, thus the first
transaction gets two different sets of rows.

For an example, imagine a user can only have one account tied to an
email. Two transactions try to open up an account at the same time. The
first transaction first checks the account count, and sees that it is 0.
The second transaction does the same and then commits its new account.
The first transaction then also creates an account, mistakenly believing
there is only one account.

The standard allows phantom reads at Repeatable read isolation levels
and below.

### No anomalies

There is a level, serializable, that does not allow for any anomalies.

## Isolation Levels in Postgres

The ANSI SQL standard assumes that transactions use locks, which
Postgres does not. Postgres uses Multiversion concurrency control, or
MVCC.

Thus, postgres does not support read uncommitted.
Read uncommitted might have lost updates, non-repeatable reads, and
phantom reads,
But repeatable read has none of the SQL anomalies.
Serializable remains the same.

Prev: [introduction](introduction.md)
Next: [pages-and-tuples](pages-and-tuples.md)
