---
title: Concurrent Tries with Efficient Nonblocking Snapshots
author:
  - "Aleksandar Prokopec"
  - "Martin Odersky"
  - "Nathan Grasso Bronson"
  - "Phil Bagwell"
doi: "10.1145/2370036.2145836"
url: "https://doi.org/10.1145/2370036.2145836"
pdf_url: "[[Concurrent tries with efficient non-blocking snapshots.pdf]]"
is_oa: true
date created: Saturday, July 19th 2025, 11:10:29 pm
date modified: Sunday, July 20th 2025, 10:37:29 am
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