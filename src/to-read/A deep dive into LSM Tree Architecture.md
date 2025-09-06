---
title: "A deep dive into LSM Tree Architecture"
source: "https://blog.canoozie.net/a-deep-dive-into-lsm-tree-architecture/"
author:
  - "[[Jeremy Tregunna]]"
published: 2025-05-09
created: 2025-07-20
description: "Database architecture might seem like an an arcane art, but at its core, it's about solving a fundamental challenge: how to retrieve and store data efficiently. While you've likely heard of relational databases using B-trees (like PostgreSQL or MySQL), there is another architectural approach that excels at write-heavy workloads... Log-Structured"
tags:
  - "clippings"
---
Database architecture might seem like an an arcane art, but at its core, it's about solving a fundamental challenge: **how to retrieve and store data efficiently**. While you've likely heard of relational databases using **B-trees** (like PostgreSQL or MySQL), there is another architectural approach that excels at write-heavy workloads... **Log-Structured Merge Trees**.

## B-Trees vs LSM trees

You've heard the expression *"Different tools for different jobs",* right? Well traditional B-tree based databases optimize for random reads, by maintaining a balanced tree structure.

When you insert or update data, the database needs to find the right place in the tree and modify it in-place. This works well for read-heavy workloads but can struggle with write-intensive applications.

You see, in write-heavy workloads, each write requires multiple random disk I/O operations, the tree needs constant re-balancing as it grows, and updates require both reading and writing to the same locations.

In contrast, LSM trees take a fundamentally different approach:

- All writes go first to an in-memory structure
- Data is periodically flushed to disk in immutable, sequential files
- Background processes merge these files to maintain read efficiency.

The difference is similar to taking notes during a meeting: **B-trees** are like meticulously organizing content in the perfect spot in your notebook as you go (slower to write, faster to find later); while LSM trees are like quickly jotting down information on new pages and organizing it later (faster to write, with some extra work to find things later).

### LSM tree design

I guess now is as good of a time as any to talk about [Kevo](https://github.com/KevoDB/kevo?ref=blog.canoozie.net), the database I've built based on an LSM tree design.

```
┌───────────────┐
                 │  Client API   │
                 └───────┬───────┘
                         │
                         ▼
┌────────────────────────┬─────────────────────┐
│                        │                     │
│           ┌────────────┴───────────┐         │
│           │         Engine         │         │
│           └────────────┬───────────┘         │
│                        │                     │
│                        │                     │
│     ┌─────────────────┬┴──────────────┐      │
│     │                 │               │      │
│     ▼                 ▼               ▼      │
│┌─────────┐    ┌──────────────┐   ┌──────────┐│
││MemTable │    │   Storage    │   │   WAL    ││
│└────┬────┘    │   Manager    │   └────┬─────┘│
│     │         └───────┬──────┘        │      │
│     │                 │               │      │
│     │                 ▼               │      │
│     │         ┌──────────────┐        │      │
│     │         │   SSTables   │        │      │
│     │         └──────┬───────┘        │      │
│     │                │                │      │
│     │                ▼                │      │
│     │         ┌──────────────┐        │      │
│     └────────►│  Compaction  │◄───────┘      │
│               └──────────────┘               │
└──────────────────────────────────────────────┘
```

The above diagram is how the LSM tree architecture is designed in Kevo. A client (for instance the [Python SDK](https://github.com/KevoDB/python-sdk?ref=blog.canoozie.net), calls into the engine to write some data, and it first ends up appendend to the **WAL** --more on this later. At the same time it's stored into the **MemTable**, and some time later, the MemTable(s) get flushed to **SSTables** which are sorted string tables.

An LSM tree can deliver exceptional write performance through several clever design choices:

- Writes are appended sequentially to memory and disk, avoiding expensive random I/O
- Multiple writes are grouped and processed together, amortizing the cost per operation
- Changes are first recorded sequentially in a log, allowing immediate acknowledgement to clients
- Data is sorted and organized during background processes, not during the critical path of the write operation

This architecture, allows databases like Kevo to handle thousands of writes per second with consistent performance, even on modest hardware.

### Read & Write Amplification

No database architecture is without its trade-offs, and Kevo is no exception.

Since data moves through multiple levels and may be rewritten several times during compaction, the actual amount of data written to disk can exceed the logical data size. Kevo tries to minimize this through some specific choices:

- Using tiered compaction strategies
- Implementing efficient compaction selection algorithms
- Batching writes together

When looking for a key, in an LSM tree architecture, you may require checking multiple locations (memory tables, and different disk levels). Kevo again makes some specific choices to minimize the impact of read amplification:

- Using [bloom filters](https://en.wikipedia.org/wiki/Bloom_filter?ref=blog.canoozie.net) to quickly determine if a key might be in a file
- Organizing files in levels with careful key range management
- Caching frequently accessed data

### From Log-structured file systems to modern databases

LSM tree architecture has evolved considerably since its introduction in the 1990s. Initially conceived for log-structured file systems, the concept was adapted for databases with [Google's BigTable paper](https://static.googleusercontent.com/media/research.google.com/en//archive/bigtable-osdi06.pdf?ref=blog.canoozie.net), which influenced many modern systems including [LevelDB](https://github.com/google/leveldb?ref=blog.canoozie.net), [RocksDB](https://rocksdb.org/?ref=blog.canoozie.net), [Cassandra](https://cassandra.apache.org/_/index.html?ref=blog.canoozie.net), and now [Kevo](https://github.com/KevoDB/kevo?ref=blog.canoozie.net).

Kevo builds on this heritage while focusing on simplicity, readability, and educational value--making the fundamental concepts more accessible than in some production systems where optimization complexity can obscure the core architectural principles.

## Key Components and how they interact

Kevo, like other LSM tree databases, consists of several interacting components that work together to provide efficient data storage and retrieval.

Let's explore each major component and how they fit into the bigger picture.

### MemTable: The fast lane

At the heart of Kevo's write performance is the MemTable--an in-memory, sorted data structure that is the first stop for all writes. Kevo uses [skip lists](https://en.wikipedia.org/wiki/Skip_list?ref=blog.canoozie.net) for its MemTable, providing efficient inserts, updates, lookups, and deletions with `O(log n)` time complexity.

Skip lists are attractive for a few reasons:

- Offers fast, ordered access with probabilistic balancing without the overhead of tree rotations or rebalancing
- Keys are always sorted in sorded order, enabling efficient range scans
- Can be immutable, allowing reads without locking

and one added benefit is that we can tune them by size, so if the active MemTable being written to gets too big, we can mark it immutable, allow the write to finish, but create a new mutable MemTable for the next write. Then we can flush immutable MemTables to disk once all in-process writes are done.

A **MemTablePool** manages all the mutable (1) and immutable (0-N) MemTables and their lifecycles. It ensures only one active MemTable can be in use at any given time, and holds a queue of immutable ones awaiting flushing to disk.

```
// Simplified pseudocode inspired by Kevo
type MemTablePool struct {
    activeMemTable *MemTable
    immutableMemTables []*MemTable
    mutex sync.Mutex
}

func (mp *MemTablePool) Put(key, value []byte) error {
    mp.mutex.Lock()
    if mp.activeMemTable.EstimatedSize() > mp.maxSize {
        // Promote current table to immutable
        mp.immutableMemTables = append(mp.immutableMemTables, mp.activeMemTable)
        // Start a new active table
        mp.activeMemTable = NewMemTable()
        // Notify background flusher
        mp.flushSignal <- struct{}{}
    }
    mp.mutex.Unlock()

    return mp.activeMemTable.Put(key, value)
}
```

This architecture ensures that data written to Kevo is immediately available from memory, even before it's flushed to persistent storage. That handoff between performance and durability leads us to the next stage in the system.

### SSTables: Persistent immutable storage

When a MemTable is full, and it's time to flush to disk, it's transformed into a Sorted String Table (SSTable)--an immutable file on disk that preserves the sorted nature of Kevo's MemTable. SSTables are the primary persistent storage mechanism in LSM tree databases.

In Kevo, they have a specific structure:

```
┌─────────────────────────────────────────┐
│ SSTable File                            │
│                                         │
│ ┌─────────────┐ ┌─────────┐ ┌─────────┐ │
│ │ Data Block 1│ │Block 2  │ │Block N  │ │
│ └─────────────┘ └─────────┘ └─────────┘ │
│ ┌─────────────────────────────────────┐ │
│ │ Index Block (maps keys to blocks)   │ │
│ └─────────────────────────────────────┘ │
│ ┌─────────────────────────────────────┐ │
│ │ Footer (metadata, bloom filter)     │ │
│ └─────────────────────────────────────┘ │
└─────────────────────────────────────────┘
```

Once an SSTable is written, it's never modified, only potentially deleted during compaction. Data is stored in fixed blocks (default 16KB) for efficient I/O. Kevo uses prefix compression to save space.

Prefix compression isn't very difficult to understand. Take for instance a format you use to save user metadata about your users in a key-value database like Kevo. You might choose a format like: `user:1` for your first user, `user:2` for your second, and so on. Instead of storing each key in full, Kevo stores: Full keys at restart points (every 16 keys by default); and for other keys, only:

- The length of the shared prefix (e.g., `5` for `"user:"`
- The length of the unique suffix (e.g., `1` for single digit numbers, etc.
- Only the unique part (`"1"`, `"2"`, etc.)

So `"user:1"`, `"user:2"`, `"user:3"` would store `"user:1"` then for `"user:2"` just store a reference to 5 shared bytes and the `"2"` character, saving significant space. This works because of the sorted nature of SSTables, sorting keys lexicographically.

Eventually they get organized into levels, thinking like branches of a tree that descend downwards (L0, L1, L2, etc.) each with different characteristics. Each SSTable will also house a bloom filter to make binary searching through a potentially large SSTable fast, to know if a key is likely in the table or not.

Since SSTables are immutable, this provides a number of benefits to a database like Kevo:

- Simple concurrency model (no locking needed for reads)
- Crash resilience (partial writes can't corrupt existing data)
- Efficient caching (data won't change unexpectedly)

### WAL: A safety net for durability

What happens if your database server crashes right after accepting a write operation but before it's safely persisted to an SSTable? That is where the [Write-Ahead Log](https://en.wikipedia.org/wiki/Write-ahead_logging?ref=blog.canoozie.net) (WAL) comes into play.

#### How the WAL works in Kevo

Kevo implements a robust WAL system that functions as a safety net for all database operations. Before any change reaches the MemTable, it gets recorded into the WAL like this:

```
┌─────────────────────────────────────────┐
│ Write-Ahead Log                         │
│                                         │
│ ┌──────────┐ ┌──────────┐ ┌──────────┐  │
│ │ Record 1 │ │ Record 2 │ │ Record N │  │
│ │ Checksum │ │ Checksum │ │ Checksum │  │
│ │ Type     │ │ Type     │ │ Type     │  │
│ │ Data     │ │ Data     │ │ Data     │  │
│ └──────────┘ └──────────┘ └──────────┘  │
└─────────────────────────────────────────┘
```

Each record in the WAL contains a precise structure:

- A CRC-32 checksum for data integrity verification
- A record type indicator (full record or fragment of a larger record)
- The operation data (key-value pairs, deletion markers, etc.)

#### Key Benefits of the WAL in Kevo

The WAL ensures that transactions are atomic--they either complete fully or not at all. If a server crashes mid-transaction, the WAL provides a complete record of what operations were in progress, allowing the database to either complete them or roll them back during recovery.

When Kevo restarts after a crash, it will automatically:

- Scan for all WAL files in chronological order
- Validate record integrity using checksums
- Reconstruct the exact state of the MemTable before the crash
- Resume normal operations with no data loss

The WAL takes advantage of a fundamental principal of disk I/O: Sequential writes are much faster than random writes. By appending all operations to the log sequentially, Kevo can achieve high throughput even when ensuring durability.

#### Configurable Sync Strategies

Kevo offers several configuration options to change durability guarantees throughout the WAL:

- **SyncImmediate** is the "safety first" option that forces an fsync after every write operation. Maximus Durabilis would be its name if it were Roman.
- **SyncBatch** is a more balanced approach that synchronizes after batches of operations. This significantly improves write throughput while still providing strong durability guarantees.
- **SyncNone** is the performance-oriented option that relies on OS caching. Fastest of the bunch, but provides fewer guarantees in the case of system failure.

You pick how much risk you are comfortable with.

#### A Real World Example

Consider you're building a user management system where the keys are structured as `"user:{id}"`. When creating a new user with ID 42:

1. The operation `PUT user:42 {"name":"Alice"}` first gets written to the WAL with a checksum
2. Only after the WAL confirms the write is safely persisted does the system update the MemTable
3. If a crash occurs before the MemTable is flushed to an SSTable, the WAL can restore the operation

This ensures that even if Kevo crashes between accepting the write and creating an SSTable, your user data remains safe and recoverable.

#### WAL Lifecycle

The WAL doesn't grow ad infinitum. The system has a set of sophisticated retention policies based on file count, age, or sequence numbers. As data gets safely persisted to SSTables, older WAL files become unnecessary, and are automatically cleaned up.

By balancing performance optimization with rock-solid durability guarantees, Kevo's WAL implementation provides the foundation for a reliable, high-performance database system that keeps your data safe against unexpected failures.

### Compaction happens in the background

An LSM tree based database, designed for write heavy workloads, requires good data organization eventually, to maintain read performance. Kevo's compaction system operates in the background to organize keys in the appropriate layers, in the appropriate order, so finding them remains quick.

Compaction matters because as your application writes data, Kevo stores it in SSTables that reflect the order in which data was written. Without organization, finding a specific key would eventually require checking dozens or hundreds of files--dramatically slowing down reads. This is where compaction steps in.

```
Before Compaction                  After Compaction
┌───────────────────────────┐      ┌───────────────────────────┐
│ Level 0                   │      │ Level 0                   │
│ [D, A]   [B, F]   [A, G]  │      │ [recent keys only]        │
└───────────────────────────┘      └───────────────────────────┘
             │                                │
             ▼                                ▼
┌───────────────────────────┐      ┌───────────────────────────┐
│ Level 1                   │      │ Level 1                   │
│ [A, B]   [C, D]           │      │ [A, B, C, D, F, G]        │
└───────────────────────────┘      └───────────────────────────┘
```

Kevo implements a tiered compaction strategy that organizes data into levels, each with specific properties:

- **Level 0** contains freshly written SSTables from MemTable flushes. Files here may have overlapping key ranges, meaning a key could exist in multiple files. This level prioritizes write speed over read efficiency.
- **Level 1 and higher** contains SSTables with non-overlapping key ranges, carefully organized for efficient searching. Each level can hold approximately 10x more data than the previous level, creating a pyramid structure that efficiently manages larger datasets.

#### Compaction Process

When compaction runs, Kevo will:

1. Identify files that need compaction, targeting areas with high overlap or excessive tombstones (deletion markers)
2. Combine the contents of multiple files, keeping only the most recent version of each key
3. Propagates tombstones down the levels or removes them when they're no longer needed
4. Ensures non-overlapping key ranges in higher levels for efficient binary search
5. Creates new optimized files and safely removes obsolete ones

By executing this process in the background, we get several critical benefits:

- Instead of checking dozens of files, Kevo can typically check just one file per level, reducing read amplification
- Compaction removes duplicate keys and eventually purges deleted data, optimizing space usage
- The leveled structure spreads write load, preventing bottlenecks and balancing write performance
- By preventing the build-up of small, fragmented files, it makes latency numbers more consistent and less spiky.

Kevo will automatically tune compaction based on the workload of your database, with intelligent algorithms that balance immediate performance needs against long-term storage efficiency. This self-tuning ability means you get excellent performance without constant manual intervention--letting you focus on building your application instead of maintaining your database.

## Closing

LSM tree architectures are neat, performant, and not really as common in the literature as some other types.

Next up, will dive into the specifics of Kevo's implementation of this architecture, but hope you enjoyed this warm-up.