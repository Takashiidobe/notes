---
title: "Transaction Management"
---

# Transaction Management

Prev: [memory-management](memory-management.md)
Next: [record-management](record-management.md)

## Transactions

One of the major features relational databases support is transactions.

The transaction API in SimpleDB looks like the following:

```rust
struct Transaction {
    fm: FileMgr,
    lm: LogMgr,
    bm: BufferMgr,
}

trait Transactions {
    fn pin(&self, blk: BlockId);
    fn unpin(&self, blk: BlockId);
    fn get_int(&self, blk: BlockId, offset: i32) -> i32;
    fn get_str(&self, blk: BlockId, offset: i32) -> String;
    fn set_int(&self, blk: BlockId, offset: i32, val: i32, ok_to_log: bool);
    fn set_string(&self, blk: BlockId, offset: i32, val: String, ok_to_log: bool);
    fn available_buffs(&self) -> i32;
    fn size(&self, filename: String) -> i32;
    fn append(&self, filename: String) -> Block;
    fn block_size(&self) -> i32;
}
```

The Recovery Manager is the portion of the database engine that reads and processes the log.

## Recovery Management

To be able to roll back a transaction, the recovery manager has to log information about the transaction's activities.

There are four kinds of log records:

1. start
2. commit
3. rollback
4. update

Rollback allows a transaction to be undone.

The general algorithm looks like this:

1. Set the current record to be the most recent log record.
2. Do until the current record is the start record for T:
    a) If the current record is an update record for T then:
    Write the saved old value to the specified location.
    b) Move to the previous record in the log.
3. Append a rollback record to the log.

As well, the log is used for recovery. Any uncompleted transactions are rolled back, and all committed transactions have their modifications written to disk.

The undo stage might look like this:

1. For each log record (reading backwards from the end):
a) If the current record is a commit record then:
Add that transaction to the list of committed transactions.
b) If the current record is a rollback record then:
Add that transaction to the list of rolled-back transactions.
c) If the current record is an update record for a transaction not on the
committed or rollback list, then: Restore the old value at the specified location.

The redo stage might look like this:

2. For each log record (reading forwards from the beginning):
If the current record is an update record and that transaction is on the committed
list, then: Restore the new value at the specified location.

## The SimpleDB Recovery Manager

The Simpledb recovery manager looks like the following:

```rust
struct RecoveryMgr {
    tx: Transaction,
    txnum: i32,
    lm: LogMgr,
    bm: BufferMgr,
}

trait RecoveryManagement {
    fn commit(&mut self);
    fn rollback(&mut self);
    fn recover(&mut self);
    fn set_int(buff: Buffer, offset: i32, val: i32);
    fn set_string(buff: Buffer, offset: i32, val: String);
}
```

Each log record implements an undo method, its transaction number, a way to write itself to a log, and deserialize itself.

As well, there is a lock manager that is used to implement transactions.

Prev: [memory-management](memory-management.md)
Next: [record-management](record-management.md)
