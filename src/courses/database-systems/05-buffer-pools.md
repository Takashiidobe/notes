---
title: "Buffer Pools"
pdf: "[[05-buffer-pools.pdf]]"
---

# Buffer Pools

Prev: [[04-database-storage-ii]]
Next: [[06-hash-tables]]

## Locks vs Latches

### Locks

- Protect the database's logical contents from other transactions.
- Held for the duration of the transaction.
- Need to be able to rollback changes.

### Latches

- Protects the critical section of the DBMS' internal data structures from other threads.
- Held for operation duration.
- No need to rollback

## Buffer Pool

The buffer pool is an in-memory cache of pages read from disk.

Each region of memory is organized as an array of fixed size pages, where each entry is called a **frame**. When a DBMS requests a page, a copy is placed in one of these frames.

The buffer pool maintains some metadata:

- **Page Table**: An in-memory hash table that keeps track of pages that are currently in memory. It maps page ids to frame locations in the buffer pool.
- **Dirty-flag**: When a page is modified, this flag is set. This tells the storage manager that this page must be written back to disk.
- **Pin Counter**: The number of threads currently accessing the page. If a page's count is greater than zero, then the storage manager cannot evict that page from memory.

Optimizations:

- **Multiple Buffer Pools**: The DBMS can have multiple buffer pools to reduce latch contention and locality.
- **Pre-Fetching**: The DBMS can optimize by prefetching pages based on the query plan.
- **Scan Sharing**: Query cursors can attach to other cursors and scan pages together.
- **Buffer Pool Bypass**: A scan might not store fetched pages in the buffer pool to avoid overhead.

Allocation Policies:

- **Global Policies**: How a DBMS makes decisions for all active transactions.
- **Local Policies**: Allocate frames to a specific transaction without considering the behavior of concurrent transactions.

## Replacement Policies

- A replacement policy is an algorithm that the DBMS implements to make a decision on which pages to evict from the buffer pool when it needs space.

**LRU**:
- LRU maintains a timestamp of when each page was last accessed.
- Evicts the page with the oldest timestamp.

**CLOCK**:
- Approximates LRU, with only one bit per timestamp.
- Each page has a reference bit, when a page is accessed, set to 1.

On eviction: go in a clockwise order, check if a page's bit is set to 1. If so, then set to 0, otherwise evict and save a cursor to the position.

### Alternatives

LRU and CLOCK are both susceptible to **sequential flooading**, where scanning disk with a query larger than the buffer pool makes the caches useless (only pure overhead).

Some better solutions include:

- LRU-K: Take into account history of the last K references.
- Priority hints: have a way to tell the buffer pool whether each page is important or not.

Prev: [[04-database-storage-ii]]
Next: [[06-hash-tables]]
