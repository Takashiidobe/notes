---
title: "Index Concurrency Control"
---

# Index Concurrency Control

Prev: [trees-indexes-ii](trees-indexes-ii.md)
Next: [sorting--aggregations](sorting--aggregations.md)

## Index Concurrency Control

A concurrency control protocol is the method that the DBMS uses to ensure "correct" results for concurrent operations on a shared object.

Two main forms:

**Logical Correctness**: Can I see the data that I am supposed to see?
**Physical Correctness**: Is the internal representation of the object sound?

## Locks vs. Latches

**Locks**:

- Protects the indexs logical contents from other transactions.
- Held for (mostly) the entire duration of the transaction.
- The DBMS needs to be able to rollback changes.

**Latches**:
- Protects the critical sections of the indexs internal data structure from other threads.
- Held for operation duration.
- The DBMS does not need to be able to rollback changes.
- Two Modes:
    - **READ**: Multiple threads are allowed to read the same item at the same time. A thread can acquire
    the read latch if another thread has it in read mode.
    - **WRITE**: Only one thread is allowed to access the item. A thread cannot acquire a write latch if another thread holds the latch in any mode

## Latch Implementations

The underlying primitive to implement a latch is an atomic compare-and-swap(CAS) instruction.

### Blocking OS Mutex

We can use the OS's built in mutex infrastructure as a latch. In linux, the futex system call is comprised of a spin latch in userspace, and an OS-level mutex in kernel land. If the thread can acquire the userspace latch, then it becomes set, blocking all other clients. Otherwise, it goes to the kernel to try and acquire a more expensive mutex. If the client fails to acquire that one, the OS deschedules the thread.

For a DBMS, it is generally a bad idea, due to management by the OS and large overhead.

### Test-and-Set Spin Latch (TAS)

Basically an atomic spinlock. If a client cannot acquire a lock, it spins in a while loop forever, trying to update it. This is very inefficient, and should be avoided unless there is very little contention.

### Reader-Writer Latches

A Reader-Writer Latch allows a latch to be held in read or write mode. It has two counters for the number of readers and the number of writers.

## Hash Table Latching

Since threads always move in the same direciton when moving from one slot to the next, and threads can only access one page/slot at a time, deadlocks are not possible, since two threads cannot compete for latches held by another thread.

Resizing a table requires taking a global latch, however.

To support latching in a dynamic hash table, there are two general modes:

- **Page Latches**: Each page has its own Reader-Writer latch that protects all of its contents. If there's a lot of write contention in a page, you'll need some finer grained concurrency control.
- **Slot Latches**: Each slot has its own latch. This increases parallelism, but increases the overhead of locking, since there are many more locks.

## B+ Tree Latching

For B+ Trees, you might have to manipulate the parent of the node you're currently on (for splits and merges), so you must take both latches and release the parent when you're sure its safe to do so. Thus, the steps to operate on a B+ Tree are:

1. Get latch for parent.
2. Get latch for child.
3. Release latch for parent if there are no splits/merges.

For searches, you can just do the following. For inserts/deletes, you have to latch the whole path, and only release latches if the current child is safe.

An improved (optimistic) protocol might involve assuming that an operation is safe, but if it turns out not to be, redoing the operation, but by grabbing latches the whole way down.

## Leaf Node Scans

Leaf Node scans are susceptible to deadlocks because they have to acquire locks in two different directions (left-to-right and right-to-left). Since index latches don't have deadlock detection or avoidance, only careful coding can help with this. One way is to use "no-wait" mode, which means that if a thread tries to acquire a latch on a leaf node, but the latch is unavailable, then it immediately aborts, releasing locks, and restarts its read.

Prev: [trees-indexes-ii](trees-indexes-ii.md)
Next: [sorting--aggregations](sorting--aggregations.md)
