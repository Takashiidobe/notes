---
title: "Hash Tables"
---

# Hash Tables

Prev: [buffer-pools](buffer-pools.md)
Next: [trees-indexes-i](trees-indexes-i.md)

## Data Structures

A DBMS uses various data structures for system internals:

- **Metadata**: for information about tables
- **Data storage**: for tuples
- **Temporary Data Structures**: Building data structures on the fly for joins
- **Table Indexes**: Auxiliary data structures to make it easier to find tuples.

There are some questions:

1. Organization: How do we organize memory and decide what to store in the data structure?
2. Concurrency: How do multiple threads access the data structure without causing problems?

## Hash Tables

A hash table allows for O(1) access and O(n) storage and maps keys to values.

There are two main considerations:

- **Hash Function**: How do we map a large key space into a smaller domain?
- **Hashing Scheme**: How to handle collisions

## Hash Functions

Hash functions take in any key as input, then it returns a deterministic representation of that key in some smaller $n$-bit space.

DBMS's should not use a cryptographic hash function, since they are slower. XXHash3 is the current state of the art.

## Static Hashing Schemes

A static hashing scheme is one where the size of the hash table is fixed. If the DBMS runs out of storage space in the hash table, it rebuilds the entire table from scratch with a larger table, like a vector.

It is important to avoid collisions, since that increases comparisons. A good load factor to rebalance at might be 70% or so.

### Linear Probe Hashing

- A single array is allocated.
- A value is hashed, and placed there. If there is a collision, you linearly search for the next free slot and use it.
- The scan stops if you find the desired key or you encounter an empty slot.
- If a key is deleted, it must leave behind a tombstone.

### Robin Hood Hashing

- Robin hood hashing is like linear probing, but each key also tracks how far away from their ideal position they are.
- On inserts, a key can take the slot of another key if it is further from its ideal key than another key. That other key is reinserted.

### Cuckoo Hashing

- Instead of maintaining one table, maintain multiple tables that use different hash functions.

- On insert, check every table, and pick one that has a free slot.
- If no tables have a free slot, evict an item from one of them, and rehash it to another location.
- If there's a cycle, rebuild all hash tables and double their size.

## Dynamic Hashing Schemes

Static Hashing schemes require the DBMS to know the number of elements it wants to store. Otherwise, a costly rebuild takes place.

Dynamic Hashing schemes are able to resize the hash table on demand without needing to rebuild the entire table.

### Chained Hashing

- Maintain a linked list of buckets for each slot in the hash table.
- If a bucket is full, add another bucket to that chain. The hash table can grow infinitely.

### Extendible Hashing

- Like chained hashing, but splits buckets instead of letting chains grow forever.
- The DBMS maintains a global and local depth bit count of the number of bits needed to find buckets in the slot array.
- When a bucket is full, the DBMS splits the bucket and reshuffles its elements. If the local depth is less than the global depth, then a new bucket is added. Otherwise, the DBMS doubles the size of the slot array to accomodate the new bucket, and increments the global depth counter.

### Linear Hashing

Instead of immediately splitting a bucket when it overflows, the scheme maintains a split pointer that keeps track of the next bucket to split. The DBMS always chooses to split this bucket, regardless of if it overflowed.

- When any bucket overflows, split the bucket chosen by adding a new slot entry, and use a new hash function.
- If the hash maps to the slot that was previously pointed to, apply the new hash function.
- When the pointer reaches the last slot, delete the original hash function and replace it with a new hash function.

Prev: [buffer-pools](buffer-pools.md)
Next: [trees-indexes-i](trees-indexes-i.md)
