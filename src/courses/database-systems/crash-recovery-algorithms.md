---
title: "Crash Recovery Algorithms"
---

# Crash Recovery Algorithms

Prev: [logging-protocols--schemes](logging-protocols--schemes.md)
Next: [introduction-to-distributed-databases](introduction-to-distributed-databases.md)

## ARIES

Aries stands for Algorithms for Recovery and Isolation Exploiting Semantics. Developed by IBM in the 90s.

Main ideas:

- **Write Ahead Logging**: Any change is recorded in log ons table storage before the database change is written to disk (STEAL + NO-FORCE).
- **Repeating History During Redo**: On restart, retrace actions and restore database to exact state before crash.
- **Logging Changes During Undo**: Record undo actions to log to ensure action is not repeated in the even of repeated failures.

## WAL Records

To implement this, the DBMS's log record format needs additional information. Every log includes a globally unique *log sequence number* (LSN).
Components in the system keep track of **LSNs** that pertain to them:

- Each data page contains a *pageLSN*: The LSN of the most recent update to the page.
- System keeps track of *flushedLSN*: The max LSN flushed so far.
- Before page $i$ can be written to disk, log must be flushed to the point where $pageLSN_i \le flushedLSN$.

## Normal Execution

### Transaction Commit

When a transaction goes to commit, the DBMS writes `COMMIT` to the log. Then the DBMS flushes all records up to and including the transaction's `COMMIT` to disk.

Once the `COMMIT` record is safely stored on disk, the DBMS returns an acknowledgement to the application that the transaction has committed. At some other point, the DBMS will write a `TXN-END` record for internal bookkeeping. It does not need to be flushed immediately.

### Transaction Abort

Aborting a transaction requires log records to have a pointer to the previous LSN. This points to the previous LSN for the transaction. The DBMS makes a linked list of LSNs to make it easier to walk through the log to find its records.

As well, aborts require another record called the *compensation log record* (CLR). A CLR describes the actions taken to undo the actions of a previous update record.

To abort, the DBMS appends an `ABORT` record to the log buffer in-memory. It then undoes the transaction's updates in reverse order to remove their effects from the database. For each update, the DBMS creates CLR entries in the log and restores old values. Afterwards, the DBMS writes a `TXN-END` log record.

## Checkpointing

Prev: [logging-protocols--schemes](logging-protocols--schemes.md)
Next: [introduction-to-distributed-databases](introduction-to-distributed-databases.md)
