# Faster Write Indexes

B-Trees are slow at index creation under InnoDB. Inserts also are fairly slow with B-Trees, sometimes 1x - 100x slower than they can be. For example, building an index on a large enough table under MySQL might take 3-4 minutes. With TokuDB it can take .5 seconds.

B-Trees slow in performance as they grow in size, since they have to store data at their leaves in sorted order. This means that random writes suffer a huge penalty, but sorted writes are generally easily insertable.

There are a few ways to make this faster: Log Structured Merge Trees (LSMs) or Fractal Trees (FTs).

## LSM Trees

LSM Trees combine a few optimizations into one.

First, they sort and hold their data in memory, in a data structure called a MemTable. Any write to this data structure is ordered, and saved in memory. Any reads that reference recently written data are then as fast as possible, since they read from this memtable.

All writes are saved sorted in a doubly linked list, so reads only have to traverse until they find the key, in which case the value is returned. Deletes create a tombstone to mark that the key no longer exists.

After a while, a MemTable is saved on disk as a Sorted String Table (SSTable), which is an immutable Key-Value mapping.

These SSTables are sorted in disk hierarchically, with older entries sifting down to the bottom. Periodically, a process does compaction, which takes a lot of I/O but removes redundancy (e.g. any writes to an item followed by a delete can be removed).

Reads, however, can be slow -- imagine reading for a key that doesn't exist in the LSM Tree. We would check the MemTable, then check every level of the tree through disk, which means reading every single block of the entire table (for a table that could be of modest size, like 64GB, this would take about 16 seconds for one query at 4 GB/s read on a top of the line SSD + computer).

To combat this, LSM trees use bloom filters in memory for each level, which can be held in memory and allow for faster read queries, because the query only needs to check sequentially by level if the membership query returns true.

## Fractal Trees

Fractal trees are implemented as B-epsilon trees, to support more write output. Each time a write comes in to a specific level, it is written to a buffer in the node. When the buffer is full, all contents are sorted and then pushed down the next level (so random writes are batched into one I/O).

## Math

16GB/s writes = 8B people on earth, so everyone gets to write 2 bytes.

4GB/s write = 4 machines * 3 = 12 machines to support everybody on earth writing 2 bytes a second.

Every day each person gets 200KB of data. 4KB means everybody on earth gets to write 50 pages per day on this setup.

If instead we have 100M customers daily, we have 80x that, so each customer would get about 16MB of writes a day, or 4000 pages.
