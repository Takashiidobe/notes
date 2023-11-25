---
title: "Memory Management"
---

# Memory Management

Prev: [disk-and-file-management](disk-and-file-management.md)
Next: [transaction-management](transaction-management.md)

## Two Principles of Database Memory Management

The two principles of database memory management:

Minimize disk accesses:

RAM access is fast, and disk access (on flash) is 1000x slower. A database engine uses memory pages to cache disk blocks. It can read from these to avoid using the OS' page manager, and flush dirty pages to disk as appropriate.

Don't rely on virtual memory:

Some problems with relying on the OS' virtual memory: it impairs the database engine's ability to recover after a system crash. For example, a log record must be written to disk before a page. If they are both not written, then recovery would be corrupted.

As well, the OS doesn't have as much knowledge of the database as the database does -- if it swaps the incorrect page, it causes 2 disk accesses which can slow down the database. The database has a buffer manager to manage pages for the database.

## Logs

Whenever a user changes the database, the database engine must keep track of that change in case it needs to be undone. The Log manager handles those changes.

The algorithm to write a log looks like this:

1. Permanently allocate one memory page to hold the contents of the last block of the log file.
    Call this page P.
2. When a new log record is submitted:
    a) If there is no room in P, then:
        Write P to disk and clear its contents.
    b) Append the new log record to P.
3. When the database system requests that a particular log record be written to disk:
    a) Determine if that log record is in P.
    b) If so, then write P to disk.

## The SimpleDB Log Manager

The simpledb Log Manager implements the following methods:

```rust
struct LogManager {
    fm: FileManager,
    logfile: String,
}

pub trait LogManagement {
    fn append(&mut self, rec: &[u8]) -> i32;
    fn flush(&mut self, lsn: i32);
}

impl Iterator for LogManager {};
```

## The Buffer Manager

The Buffer Manager is responsible for the pages that hold data. A page is pinned if a client is pinning it, otherwise, it is unpinned. The Buffer manager must keep a page available to its clients as long as it is pinned. Any unpinned page is allowed to be assigned to another block.

Replacement of pages might follow FIFO, LRU, or other algorithms.

## The SimpleDB Buffer Manager

The Buffer Manager looks like the following:

```rust
trait BufferManagement {
    fn pin(&self, blk: BlockId) -> Buffer;
    fn unpin(&self, buff: Buffer);
    fn available(&self) -> i32;
    fn flush_all(&mut self, txnum: i32);
}

trait BufferTrait {
    fn contents(&self) -> Page;
    fn block(&self) -> BlockId;
    fn is_pinned(&self) -> bool;
}

struct BufferMgr {
    bufferpool: Vec<u8>,
    available: i32,
    max_time: i32,
}

struct Buffer {
    fm: FileMgr,
    lm: LogMgr,
    contents: Page,
    blk: Option<BlockId>,
    pins: i32,
    txnum: Option<i32>,
    lsn: Option<i32>,
}
```

Prev: [disk-and-file-management](disk-and-file-management.md)
Next: [transaction-management](transaction-management.md)
