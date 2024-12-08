---
title: Concurrent Tries with Efficient Nonblocking Snapshots
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Saturday, December 7th 2024, 8:44:36 pm
---

# Concurrent Tries with Efficient Nonblocking Snapshots

This paper introduces a non-blocking concurrent hash trie that has
efficient lock-free snapshot operations, consistent iterators, and
linearizable size retrieval. The only requirement is that this hash trie
requires a compare-and-swap instruction, (CAS) and is mainly blocked on
how fast that is done.

# Motivation

Most concurrent collections don't have linearizable snapshot -- this
requires grabbing a lock on the entire data-structure, traversing it,
and taking a snapshot of it. As well, the size() operation isn't
consistent, either requiring a lock for consistency (in exchange for
lower performance) or giving up accuracy (for more performance).

This requires a CAS instruction to create a GCAS procedure:
This takes 3 parameters, an I-node in, with two main nodes old and n.
Each I-node contains an immutable field for its generation, and allows
linearizability.

All operations have a worst-case complexity of O(log n), with snapshot
being an amortized O(1) complexity, linearizable lock-free size,
iterator, and clear operations.
