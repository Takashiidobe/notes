---
title: "Trees Indexes I"
---

# Trees Indexes I

Prev: [hash-tables](hash-tables.md)
Next: [trees-indexes-ii](trees-indexes-ii.md)

## Indexes

A table index is a replica of a subset of a table's columns organized in a way that allows the DBMS to find tuples more quickly than performing a sequential scan.

If there's an index on a column, it's the DBMS' job to figure out the best indexes to use to execute queries.

## B+ Trees

A B+Tree is a self-balancing tree data structure that keeps data sorted, and allows for access operations in $O(\log({}n))$. It is optimized for disk based storage that read/write large blocks of data.

A B+ Tree is an $M$-way search tree with the following properties:

- Perfectly balanced (every leaf node is at the same depth)
- Every inner node other than the root is at least half full.
- Every inner node with $k$ keys has $k + 1$ non-null children.

Every node in a B+ Tree contains an array of key/value pairs:

- Arrays at every node are (almost) sorted by the keys.
- The value array for inner nodes will contain pointers to other nodes.
- Leaf node values can either contain:
    1. Record IDs: A pointer to the location of the tuple.
    2. Tuple Data: The actual contents of the tuples.

### Insertion

To Insert:

1. Find correct leaf $L$.
2. Add new entry into $L$ in sorted order:
    - If $L$ has enough space, finish.
    - Else, split $L$ into two nodes $L$ and $L2$. Redistributed entries evenly and copy the middle key and put in $L$.  Insert index entry point to $L2$ into parent of $L$.
3. To split an inner node, redistributed entries evenly, but push up the middle key.

### Deletion

1. Find correct leaf $L$.
2. Remove the entry:
    - If $L$ is still at least half full, finish.
    - Otherwise, redistribute, borrowing from sibling.
    - If that fails, merge $L$ and sibling.
3. If merge occurs, delete entry in parent pointing to $L$.

## B+ Tree Design Decisions

**Node Size**:
- The optimal size for a B+ Tree depends on the speed of the disk. The slower the disk, the larger the ideal node size.
- Workloads also affect the node size. Scan-heavy workloads like larger nodes, whereas single key lookups prefer smaller node sizes.

**Merge Threshold**:
- Delaying merging operations reduces the overhead of reorganization.
- For example, underflows might be ignored, and the tree can be rebuilt periodically to deal with this.

**Variable Length Keys**:
- Pointers can store keys as pointers to the tuples attribute (rarely used)
- Variable Length Nodes: The size of each node in the B+ Tree can vary, which complicates implementation.
- Key Map: Embed an array of pointers that map to the key+value list within the node.

**Non-Unique Indexes**:
- Duplicate Keys use the same leaf node layout, but store duplicate keys multiple times
- Value Lists store each key only once and maintain a linked list of unique values.

**Intra-Node Search**:
- Linear scanning: Scan key-value nodes from beginning to end. This doesn't require entries to be sorted, which is an advantage.
- Binary: $(\log{}n)$ to the size of the entry list, but requires presorting the key-value entries.
- Interpolation: Approximate the starting position of the search key based on the known low/high values in the node, and linear searching from there. This requires keeping statistics in the node.

## B+ Tree Optimizations

**Prefix Compression**:
- Sorted keys in the same leaf node are likely to have the same prefix.
- Extract that prefix and only store unique suffixes.

**Suffix Truncation**:
- The keys in the inner nodes are only used to direct traffic, so we can store just a prefix.

**Bulk Inserts**:
- The fastest way to build a B+ Tree from scratch is to first sort the keys and then build the index from the bottom up.
- This is faster, since there are no splits or merges.

Prev: [hash-tables](hash-tables.md)
Next: [trees-indexes-ii](trees-indexes-ii.md)
