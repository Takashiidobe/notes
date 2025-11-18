---
title: "Sorting + Aggregations"
---

# Sorting + Aggregations

Prev: [index-concurrency-control](index-concurrency-control.md)
Next: [joins-algorithms](joins-algorithms.md)

## Sorting

We need sorting because in the relational model, tuples have no specific ordering. Thus, `ORDER BY`, `GROUP BY`, `JOIN`, and `DISTINCT` operators can all sort.

Sorting can be accelerated using a clustered B+ Tree.

If the data fits in-memory, sorting can be done with a normal in-memory algorithm, but it might spill to disk, requiring an external sorting algorithm.

## External Merge Sort

External Merge sort splits the data set into separate runs and then sorts them individually.

1. Sorting: sort small chunks of data that fit in main memory, then write back to disk.
2. Merge: Combine sorted sub-files into a larger single file.

**Two-way Merge Sort**
1. Pass 0: Read every $B$ pages of the table into memory, sorts them, and writes them back to disk.
2. Pass 1..N: Recursively merges pairs of runs into runs twice as long.

Number of passes: $\log_{2}(N)$
Total I/O Cost: $2(N) * (passes)$

**General $K$-way Merge Sort**
1. Pass 0: Use $B$ buffer pages, produce $N/B$ sorted runs of size $B$.
2. Pass 1..N: Recursively merge $B - 1$ runs.

Number of passes: $\log{B-1}\frac{N}{B}$
Total I/O Cost: $2(N) * (passes)$

## Aggregations

An aggregation operator in a query plan collapses one or more tuples into a single scalar value.

**Sorting**: The DBMS sorts the tuples, either using an in-memory algorithm or external algorithm. The DBMS then sequentially scans the sorted data to compute the aggregation.

**Hashing**: Hashing can be cheaper than computing aggregations. The DBMS can populate an in-memory hash table as it scans the table, making the aggregation on the fly.

For data that is too large to fit in memory, the DBMS can create a hash table on disk:

1. Partition: use a hash function $h_1$ to split tuples into partitions on disk based on target hash key.
2. Rehash: For each partition on disk, read its pages into memory and build an in-memory hash table with a second hash function $h_2$ where $h_1 \neq h_2$. Then stitch together the aggregation.

Prev: [index-concurrency-control](index-concurrency-control.md)
Next: [joins-algorithms](joins-algorithms.md)
