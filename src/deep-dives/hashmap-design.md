# Hashmap design

Hash tables are associative collections of Key -> Value. The approaches
to implement them fall into two buckets: Open Addressing, where items
are stored in a flat array, and Separate Chaining, where collisions are
stored in linked lists.

## Separate Chaining

Separate chaining stores collisions in linked lists. Each bucket stores
a pointer to the head of a linked list and traverses the linked list to
find an entry.

This has pros:

1. Load factor: if the Hashmap is overloaded, performance degrades
   linearly. As well, rebalancing isn't as necessary all the time like
   it is for open addressing, because performance degrades linearly
   for an open addressing scheme as load factor goes to 1, and stops
   working at a load factor of 1.
2. Stable references: items have stable references until they're
   removed. If the item itself is moved, its pointer can stay stable,
   which allows programs to have pointers to elements in a map.
3. Simple Deletion: open addressing requires complex deletion as well as
   supporting tombstones.

And cons:

1. Memory Overhead: each item needs to have space for a pointer,
   and allocation metadata, which a flat array would not have (just some
   metadata for the whole map, and no pointers per item).
2. Cache locality: linked lists are not contiguous in memory, and cannot
   be well predicted. In real life workloads, where pointers are not in
   L1, performance can suffer drastically.
3. Memory latency: a new node can require a heap allocation, which is
   slow.

## Open Addressing

Open addressing places all items in a singular array, and uses
tombstones to mark deletions.

Pros:

1. Cache-locality: all items are in the same array, so cache utilization
   is much better. Scanning through an array is much faster than chasing
   pointers.
2. Lower memory overhead: there is no allocation metadata, and
   tombstones can be as simple as a byte marker.
3. Speed: at lower load factors, open addressing is fast because there
   are very few collisions.

Cons:

1. Clustering and load: At higher loads, performance degrades linearly.
   Tables have to be rehashed at around 80% load, and stop working at
   100% load, whereas separately chained implementations can support
   100% load and still just have linear degradation.
2. Deletion: Tombstones are required to mark deletions, but they
   complicate implementation and require lookups to have branches to
   support deletions. Periodic rehashing is also required in case there
   are too many deletions, which can pause usage of the hashmap.
3. Iterator invalidation: if an item is rehashed or inserted, iterators
   can be invalidated, so there are no stable references.

## Modern Optimization Techniques

Newer hashmaps have SIMD acceleration for lookups. Take the SwissTable,
which has a metadata byte for each slot. This can be looked up in
vectorized order, and then checked to narrow down candidates for lookup.

They also group slots in chunks to align to cache lines as well.

## Concurrency

Neither hashmap supports concurrency out of the box, but a concurrent
map can support features from both types of maps. A common approach to
make a table concurrent is to divide the table into buckets, and have a
lock (either mutex or RwLock) on each bucket. In a separate chaining
map, this allows for good performance as long as keys are
well-distributed. As well, since deletion is a pointer deletion, which
is atomic and on most architectures, broadcast to all threads, even the
lists themselves can support finer grained locking.

Supporting concurrent operations on an open addressed map is harder. You
can split up tables into smaller tables, but if due to collisions, an
item needs to move to another table, the implementation wouldn't work.
This can be optimized using a metadata array, to narrow lookups on
concurrent sections.

Thus, separate chaining approaches are better for write-heavy hashmaps,
whereas open addressing schemes are better for read-heavy hashmaps.
