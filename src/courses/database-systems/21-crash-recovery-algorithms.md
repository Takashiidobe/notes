---
title: "Crash Recovery Algorithms"
pdf: "[[21-crash-recovery-algorithms.pdf]]"
---

# Crash Recovery Algorithms

Prev: [[20-logging-protocols-schemes]]
Next: [[22-introduction-to-distributed-databases]]

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

The DBMS makes checkpoints every once in a while, where it writes dirty pages in the buffer pool to disk. This keeps the size of the WAL bounded.

There are either **blocking** or **non-blocking** ways to take checkpoints.

### Blocking Checkpoints

The DBMS halts when it takes a checkpoint, to create a consistent snapshot. That is:

- Halt the start of any new transactions.
- Wait until all active transactions finish executing.
- Flush dirty pages to disk.

### Better Blocking Checkpoints

We can do better without stopping active transactions.

- Halt the start of any new transactions.
- Pause transactions while the DBMS takes the checkpoint.

We use some extra metadata to do this.

**Active Transaction Table (ATT)**: The ATT represents the state of transactions that are actively running in the DBMS. A transaction's entry is removed after the DBMS completes the commit/abort process for that transaction. For each transaction, the ATT contains:

- TXID
- status (the mode of the transaction, either Running, Committing, Undoing)
- lastLSN: The most recent LSN written by the transaction.

**Dirty Page Table (DPT)**: The DPT contains information about the pages in the buffer pool that were modified by uncommitted transactions. There is one entry per dirty page containing the recLSN (the LSN of log records that caused the page to be dirty)

### Fuzzy Checkpoints

A fuzzy checkpoint is where the DBMS allows other transactions to continue to run. ARIES does this. The DBMS uses additional log records to track checkpoint boundaries:

- <CHECKPOINT-BEGIN>: indicates the start of the checkpoint.
- <CHECKPOINT-END>: When the checkpoint has completed. Has the ATT and DPT.

## ARIES Recovery

The ARIES protocol is comprised of three phases. On startup or crash, the DBMS executes the following:

1. **Analysis**: Read the WAL to identify dirty pages in the buffer pool and active transactions at the time of the crash.
2. **Redo**: Repeat all actions starting from an appropriate point in the log.
3. **Undo**: Reverse the actions fo transactions that did not commit before the crash.

### Analysis Phase

- Start from the last checkpoint found in the database's LSN.
- Scan log forwards from checkpoint
- If the DBMS finds a `TXN-END`, remove it from the ATT.
- All other records add transaction to ATT with status **UNDO** and on commit, change transaction status to **COMMIT**
- For `UPDATE` records, if `P` is not in the DPT, add it. Then, set `P`'s recLSN to the log record's LSN.

### Redo Phase

This phase is to reconstruct state at the moment of the crash. Reapplies all updates, and redoes `CLRs`.
The DBMS scans forward from the log record containing the smallest recLSN in the DPT. For each update log, the DBMS reapplies the update unless:

- Affected page is not in the DPT
- Affected page is in DPT but that record's LSN is greater than the smallest recLSN
- Affected pageLSN(on disk) is greater than or equal to the LSN.

To redo an action, the DBMS reapplies the change in the log record and sets the affected page's pageLSN to that log record's LSN.

At the end of this phase, write `TXN-END` with status COMMIT and removes them from the ATT.

### Undo Phase

Finally, the DBMS has to reverse all transactions that were active at the time of the crash. These are transactions with `UNDO` status in the ATT after the Analysis phase.

The DBMS processes transactions in reverse LSN order, and as it reverses the updates of a transaction, the DBMS writes a CLR entry to the log for each modification.

Once the last transaction has been aborted, the DBMS flushes out the log and is ready to start processing new transactions.

Prev: [[20-logging-protocols-schemes]]
Next: [[22-introduction-to-distributed-databases]]
