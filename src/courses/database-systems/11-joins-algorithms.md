---
title: "Joins Algorithms"
pdf: "[[11-joins-algorithms.pdf]]"
---

# Joins Algorithms

Prev: [[10-sorting-aggregations]]
Next: [[12-query-execution-i]]

## Joins

For a tuple $r \in R$, and a tuple $s \in S$ that match on join attributes, the join operator concatenates $r$ and $s$ together into a new output tuple.

This can be done a few ways:

1. Copy all the data: This copies all the data from all matching tuples in $R$ and $S$ into an intermediate result table. This has the advantage that the query never needs to go back to either table, but it also potentially wastes a lot of memory.
2. Record Ids: Only copy the ids of matching tuples, and fetch their data later. This is called **late materialization**.

**Cost Analysis**

The cost analysis metric will be the number of disk I/Os used to compute the join.

Set $M$ as the pages in $R$, and $N$ as the pages in $S$.

## Nested Loop Join

This algorithm involves using two for loops, with the smaller table on the outer loop, and the larger table in the inner loop.

**Simple Nested Loop Join**
The regular $O(n^2)$ algorithm.
Cost: $M + (m * N)$

**Block Nested Loop Join**
For each block in the outer table, fetch each block from the inner table, and work on each pair of blocks. This is no faster in terms of comparisons, but less costly in terms of I/O.
Cost: $M + (M * N)$.

**Index Nested Loop Join**
If the inner table has an index, we can use that. Assume that each index lookup costs a constant, $C$.
Cost: $M + (m * C)$.

## Sort-Merge Join

First sort the tuples on the join key, and then merge them where they match.

Sort Cost for $R$: $2M * 1 + \log{B-1}(\frac{M}{B})$
Sort Cost for $S$: $2N * 1 + \log{B-1}(\frac{N}{B})$
Merge Cost: $(M + N)$
Cost: Sort + Merge $\approx O(M + N \log{}(M + N))$

## Hash Join

**Basic Hash Join**
Hash each item in $R$ and $S$ on the join key. Then, for each bucket of a hash function that matches, check the members of each hash bucket in $R$ and $S$.

This has a variable cost, depending on the amount of collisions, but is $\approx O(\max{R}{S})$.

**Grace Hash Join**
When hash tables do not fit in memory, swapping to disk would be expensive. Thus, this algorithm hashes the inner table into partitions that are written out to disk as well.

1. Build: Scan both the outer and inner tables and populate a hash table using the hash function $h_1$ on the join attributes. These are written out to disk as needed. If a bucket doesn't fit in memory, recurisvely partition it with a second hash function $h_2$ to further divide the bucket.
2. Probe: For each bucket, retrieve the pages in the outer and inner tables. Then perform a nested loop join on all tuples.

Partition Cost: $2 * (M + N)$
Probe Cost: $(M + N)$
Total Cost: $3 * (M + N)$

Prev: [[10-sorting-aggregations]]
Next: [[12-query-execution-i]]
