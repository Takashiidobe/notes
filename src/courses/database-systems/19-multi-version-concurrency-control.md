---
title: "Multi-Version Concurrency Control"
pdf: "[[19-multi-version-concurrency-control.pdf]]"
---

# Multi-Version Concurrency Control

Prev: [[18-timestamp-ordering-concurrency-control]]
Next: [[20-logging-protocols-schemes]]

## Multi-Version Concurrency Control

MVCC is the most used concurrency protocol. Most RDBMS and NoSQL DBs support it.

The main idea: The DBMS maintains multiple **physical** versions of a single **logical** object in the database.

- When a transaction writes to an object, the DBMS creates a new version of that object.
- When a transaction reads an object, it reads the newest version that existed when the transaction started.

### Key Properties of MVCC

**Writes don't block readers. Readers don't block writers.**

Read-only transactions can read a consistent snapshot without acquiring locks. Timestamps are used to determine visibility.

Multi-versioned DBMS' can support time-travel queries that read the database at some point in time.

## Version Storage

The DBMS stores different physical versions of the logical object by using the tuple's pointer field to create a version chain for each logical tuple.

This allows the DBMS to query for the version of the tuple it needs at runtime. Indexes point to the head of the chain, and you can traverse it until you find the version that is visible to you.

### Implementations

1. **Append-Only Storage**: New versions are appended to the same table space. Can be done with;
    - **Oldest-To-Newest (O2N)**: Append new version to end of chain, lookups require entire chain traversal.
    - **Newest-To-Oldest (N2O)**: Head of chain is newest. lookups are quick, but indexes need to be updated on every insert.
2. **Time-Travel Storage**: Old versions are copied to a separate table space.
3. **Delta Storage**: The original values of the modified attributes are copied into a separate delta record space.

## Garbage Collection

The DBMS must have some way to reclaim memory.

1. **Tuple Level Garbage Collection**: Find old versions by examining tuples.
    - **Background Vacuuming**: Separate threads periodically scan the table and look for reclaimable versions. Works with any version storage scheme.
    - **Cooperating Cleaning**: Worker threads identify reclaimable versions as they traverse the version chain. Works with O2N.
2. **Transaction level**: Each transaction keeps track of its read/write set. When a transaction completes, the garbage collector can identify which tuples to relcaim.

## Index Management

All primary key indexes always point to the version chain head. Any updates to a pkey generally are treated as a DELETE then an INSERT. Thus, having incrementally inserting pkeys is much better.

Secondary indexes can be maintained by:

- **Logical Pointers** - Use a fixed identifier per tuple that does not change. Requires an indirection layer to map the logical id to the physical location of the tuple.
- **Physical Pointers** - Use the physical address to the version chain head.

Prev: [[18-timestamp-ordering-concurrency-control]]
Next: [[20-logging-protocols-schemes]]
