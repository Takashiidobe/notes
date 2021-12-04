---
title: transactions
---

Prev: [partitioning](partitioning.md) Next:
[distributed-systems-trouble](distributed-systems-trouble.md)

# Transactions

Many things can go wrong while writing to a node. Transactions have been
the mechanism of choice for simplifying these issues. Conceptually, a
transaction is a set of reads and writes that are treated as one logical
unit. If anything fails, the whole transaction can be rolled back. If it
succeeds, it can be applied in one go.

## The Slippery Concept of a Transaction

Transactions are well supported in RDBMS, but less so in NoSQL
databases.

## The Meaning of ACID

ACID stands for Atomicity, Consistency, Isolation and Durability. There
is a lot of ambiguity, especially around isolation.

Some systems that offer weaker guarantees call themselves BASE, for
Basically Available, Soft state, Eventual Consistency.

### Atomicity

ACID atomicity means that if there is a fault during a write during a
transaction, and the transaction cannot be committed due to a fault,
then the transaction is aborted, and all writes are discarded.

This makes operations grouped in a transaction safe to retry, since we
know that all writes in the transaction have been thrown away.

### Consistency

ACID consistency means that certain statements about your data are true;
like foreign keys or other check constraints.

### Isolation

ACID isolation means that concurrently executing transactions are
isolated from each other. Each transaction can pretend that it is the
only transaction running on the entire database. This is also called
serializability.

### Durability

ACID durability means that successfully committed transactions will not
lose data. In a single node DB, that means writing to the WAL and disk,
but on a distributed database, that can mean committing a write to a
certain number of nodes.

## Single-Object and Multi-Object Operations

Transactions are used to logically group two operations that are
disjoint. Let's say that you have a table of emails, and are querying
it like this:

```sql
SELECT COUNT(*) FROM emails WHERE recipient_id = 2 AND unread_flag = true;
```

You decide to denormalize the table (storing the unread messages in
another field). Thus, when you write an email, you have to increment the
unread messages field, and if you read an unread email, you have to
decrement it.

Without atomicity, if an error occurs somewhere, the contents of the
mailbox and unread counter might become out of sync.

Unfortunately, many NoSQL databases don't have a way of grouping
operations together.

### Single-Object writes

Atomicity and Isolation apply for a single object being changed. Let's
say in the middle of a write, if the network connection goes out, it
would be confusing if a half-written write propagated to the database.

Thus, storage engines almost always try to provide atomicity and
isolation at the single object level.

Some NoSQL dbs provide atomic operations, such as increment and compare
and set, but these are different from transactions, which operate on
multiple objects.

### The need for multi-object transactions

Many distributed datastores abandoned multi-object transactions because
of their difficulty to implement across partitions, but there is nothing
that prevents them from being implemented.

Likewise, there are many cases when they are useful, like:

- Updating foreign key references.
- Updating neighbor nodes of a graph.
- Updating logically grouped fields of a document.
- Updating secondary indexes after a write.

### Handling errors and aborts

ACID guarantees allow us to retry transactions, but this isn't a
perfect error handling mechanism.

- If the transaction succeeded, but the network failed, retrying still
  causes two writes.
- If the error is due to overload, we risk overloading the server by
  retrying.
- If the error is due to a constraint violation, retrying is
  pointless.
- If the database write has side-effects (like writing an e-mail) it
  might send those even if the transaction is aborted.
- If the client process fails, data is lost.

## Weak Isolation Levels

Databases have tried to hide concurrency issues from application
developers, but Serializable isolation has a performance cost, so
databases tend to offer weaker guarantees.

### Read Committed

Read Committed is the most basical level of transaction isolation.

1.  When reading from the database, you will only see data that has been
    committed (no dirty reads).
2.  When writing to the database, you will only overwrite data that has
    been committed (no dirty writes).

#### No dirty reads

If another transaction can see uncommitted or unaborted data, that is a
dirty read. This prevents:

- Impartial updates.
- Reads seeing data that was later rolled back.

#### No dirty writes

What happens if a write overwrites an uncommitted value? That's a dirty
write.

This helps us avoid these situations:

- If Alice and Bob try to buy a car: Let's say Bob wins, because he
  wrote to the listings table first so he gets the certificate, but
  Alice is given the invoice, because she wrote to the invoices table
  first.

#### Implementing read committed

Read Committed is a popular isolation level, and default on most RDBMS.

This can be implemented by having all transactions take the lock on
single-object keys, and release them when the transaction aborts or
completes.

However, this is slow in practice, and slows read volume speed. Because
of this, this isn't used much.

Instead, MVCC is used, where for every object written in a transaction,
the database remembers the old value and the new value. Readers can read
the previous value while the transaction is ongoing, and read the new
value after the transaction has been committed.

### Snapshot Isolation and Repeatable Read

This doesn't prevent us from getting into concurrency bugs: Imagine a
person trying to transfer money from one account to another:

Assume Alice has two accounts with $500, and wants to transfer $100
from account 1 to account 2.

If Alice queries her first account before the transaction completed and
queries her second account after the transaction, it will look as though
$100 disappeared.

```sql
select balance
from accounts
where id = 1; -- returns 500

-- Transaction here, take $100 from account 2 and put into account 1.
Begin Transaction;
update accounts
set balance = balance + 100
where id = 1;

update accounts
set balance = balance - 100
where id = 2;
Commit;

select balance
from accounts
where id = 2; -- returns 400, as the transaction has finished.
```

This is called read skew (nonrepeatable read). If Alice looks at her
account 1 balance again after the transaction, it will return the proper
answer.

There are some cases where this is problematic:

1.  Backups: Backups require making a copy of the entire database, which
    can take hours. Read skew can result in some versions of the data
    containing an old version and others containing a new version, which
    can make inconsistencies like disappearing money become permanent.

2.  Integrity checks: Integrity checks will fail if they read some parts
    of the data in an old state and some parts of it in a new state.

Snapshot Isolation is the most common solution: Each transaction reads
from a consistent snapshot of the database, i.e. all committed reads at
that time.

### Implementing snapshot isolation

To implement snapshot isolation, we should implement a locking system
where readers never block writers, and writers never block readers.

To do this, the database keeps several different committed versions of
an object side by side, so readers can access previous versions. This is
called multi-version concurrency control (MVCC).

To do this, every transaction is written an only increasing transaction
id (txid). Each row has a created_by and a deleted_by field,

Prev: [partitioning](partitioning.md) Next:
[distributed-systems-trouble](distributed-systems-trouble.md)
