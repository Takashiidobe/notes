---
title: "Logging Protocols + Schemes"
pdf: "[[20-logging-protocols-schemes.pdf]]"
---

# Logging Protocols + Schemes

Prev: [[19-multi-version-concurrency-control]]
Next: [[21-crash-recovery-algorithms]]

## Crash Recovery

Recovery algorithms ensure consistency, atomicity, and durability.

Every recovery algorithm has two parts:

1. Actions during normal transaction processing to ensure transaction aborts leave the DB in a consistent state.
2. Actions after a failure to recover the database to a consistent, atomic, durable state.

The two key primitives are `UNDO` and `REDO`.

- **UNDO**: Removing the effects of an aborted transaction.
- **REDO**: Reinstating a committed transaction for durability.

## Failure Classification

1. **Transaction Failures**
- **Logical Errors**: A transaction cannot complete due to an integrity/constrain violation.
- **Internal State Errors**: The DBMS terminates an active transaction due to an error condition.

2. **System Failures**:
- **Software Failure**: There is a problem with the DBMS implementation that causes the system to halt.
- **Hardware Failure**: The computer hosting the DBMS crashes. Assume that non-volatile storage is not corrupted by crash.

3. **Storage Media Failure**:
- **Non-Repairable Hardware Failure**: A disk failure destroys all or some parts of non-volatile storage. Destruction is detectable. The database must be restored from an archived version.

## Buffer Pool Management Policies

**Steal Policy**: Whether the DBMS allows an uncommitted transaction to overwrite the most recently committed value of an object on disk.
- **STEAL**: allowed
- **NO-STEAL**: not allowed
**Force Policy**: Whether the DBMS ensures that all updates made by a transaction are reflected on non-volatile storage before the transaction is allowed to commit.
- **FORCE**: enforced
- **NO-FORCE**: not enforced

Force makes it easier to recover but results in poorer runtime performance.

## Shadow Paging

The DBMS maintains two separate copies of the database (master, shadow). Updates are only made in the shadow copy. When a transaction commits, atomically switch the shadow to become the new master.

This is a `NO-STEAL` + `FORCE` system.

**Implementation**:

- Database pages are a tree, where the root is a single disk page.
- Two copies of the tree, the master and shadow.
    - Root points to master.
    - Updates are applied to the shadow.
- To install updates, overwrite the root so it points to the shadow. (Pointer swap). This is atomic on most architectures.
    - Before overwriting the root, none of the transaction updates are part of the database on disk.
    - After the swap, all the transactions are on disk.

**UNDO**: Remove the shadow pages. Leave the master and DB root pointer alone.
**REDO**: Not needed.

## Write-Ahead Logging

The DBMS records all changes made to the database in a log file on non-volatile storage before the change is made to disk. The log contains instructions required to undo and redo after a crash.

This is a `STEAL` + `NO-FORCE` system.

This has the fastest runtime performance, but recovery time is slower than shadow paging because it has to replay the log.

**Implementation**:
- All log records are written to non-volatile storage before the page is written to non-volatile storage.
- A transaction is not considered committed until all its log recordshave been written to disk.
- When the transaction starts, write a `BEGIN` record to the log.
- When it finishes, write a `COMMIT` to make sure all log records are flushed before it returns an acknowledgement to the application.
- Each log entry contains the following information:
    - Transaction ID
    - Object ID
    - Before Value (for UNDOing)
    - After Value (for REDOing)
- Log entries to disk after transaction commits. Group commits can be used to batch multiple log flushes together to amoritize overhead.

## Checkpoints

Write-Ahead Logging has a problem in that the log file grows infinitely. After a crash, the DBMS has to replay the entire log, which can take a long time if the log file is large. Thus, the DBMS can periodically make a checkpoint where it flushes all buffers out to disk.

**Blocking Checkpoint Implementation**:

- The DBMS stops accepting new transactions and waits for active transactions to complete.
- Flush all log records and dirty blocks to disk.
- Write a `CHECKPOINT` entry to the log and flush to stable storage.

## Logging Schemes

**Physical Logging**:
- Record the changes made to a specific location in the database

**Logical Logging**:
- Record the high level operations executed by transactions. Not necessarily restricted to a single page. Requires less data, but can be difficult to implement for non-deterministic queries. (RAND() will be tricky).

**Physiological Logging**:
- Hybrid approach where log records target a single page but don't specify the organization of the page.

Prev: [[19-multi-version-concurrency-control]]
Next: [[21-crash-recovery-algorithms]]
