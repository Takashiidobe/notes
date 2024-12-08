---
title: "RRB-Trees: Efficient Immutable Vectors"
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Saturday, December 7th 2024, 8:45:22 pm
---

# RRB-Trees: Efficient Immutable Vectors

RRB Trees stands for "Relaxed Radix Balanced Trees (RRB-Trees)". This
allows for immutable vector concatenation, insert-at and splits in O(log
N) time while maintaining an index, with update and iteration speeds of
O(1) time.

## Introduction

Cons is slow. Lists in Lisp are slow; as they must be immutable,
appending, updating, deleting take O(n) time, while prepending takes
O(1) time. As well, since the structure of a list isn't guaranteed in
stack memory, they take a long time to dereference properly.

Vectors are preferable to lists for this reason. As well, disjoint parts
of the vector can be worked on in parallel.

Clojure tries to solve this using "Ideal Hash Tries" (HAMTs), which are
used for hashmaps and 32-way branching trees. This allows for
single-element append in constant time, indexing in 1/5 log N time, and
updates in 32/5 log N time. As well, using 32-wide arrays as tree nodes
makes it cache friendly. An index update incurs 1/5 log N indirect
memory access, which is close to constant time.

Parallel processing requires concatenation, splitting, and insertion at a
given index. The RRB Tree has O(log N) concatenation and insertions.
This is useful for "filtering", where the size of the individual
partition results isn't known beforehand.

### Related Work

Previous immutable data structures that work on concatenation are ropes,
2-3 finger trees, and B-Trees. However they have limitations:

Ropes are for effective splitting and concatenation with strings. When a
string is concatenated, its size is added to the last node. Each node
contains its string length and the contents of the string. Splits can be
performed by creating a split node above the rope with the values of the
upper and lower split bounds. This degrades in performance over time, as
concatenation and splits occur. Balancing occurs periodically to
preserve performance, and prevent memory leaks.

2-3 finger trees have log N indexing, and update, with an amortized
constant time for adding items to the vector. Concatenation can be
accomplished in log N time as well. However, log N indexing is slower
than 1/5 log N time which the RRB tree has.

B-Trees have log N indexing, updating, but take O(n) to concatenate.

### Vectors

Using HAMTs like clojure, with a 32-way branching structure allows for
1/5 log N index performance.

### Concatenation

Concatenation of two vectors naively requires O(n) time, since it
requires copying all of the nodes from the right hand side to the left
hand side.

## RRB-Trees

In Vectors, the branch factor m is always 32, and the trees are
balanced. This allows radix search to find the child node during
indexing.

Radix Search is cache-aware, which means it can be three times faster
than a binary or linear search at the node.

## Conclusions

RRB-Trees provide a viable extension to 32-way HAMTs by having the
advantage of O (log N) concatenation and splits while maintaining the
same costs as the HAMT.
