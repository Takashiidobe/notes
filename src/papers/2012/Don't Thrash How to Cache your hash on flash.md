---
title: Don't Thrash How to Cache Your Hash on Flash
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Saturday, December 7th 2024, 8:44:48 pm
pdf_url: "[[Don't Thrash How to Cache Your Hash on Flash.pdf]]"
---

# Don't Thrash How to Cache Your Hash on Flash

Many large storage systems use an approximate-membership-query (AMQ) to
deal with the massive amounts of data that they process.

This paper describes the Cascade Filter, an AMQ data structure that
scales beyond main memory. Bloom filters work well in memory, but not on
disk. The Cascade Filter supports 500k insertions/deletions per second
and over 500 lookups per second on an SSD.

# Introduction

An AMQ data structure supports the following operations: Insert, lookup,
and optionally delete. 

For a key in the set, lookup always returns present.
For a key not in the set, lookup returns present sometimes (incorrectly)
and absent (mainly) with a probability of 1 - Error, where Error is
tunable (less error = more memory consumption).

Bloom Filters work well when they fit into main-memory. Bloom Filters
require about one byte per stored data item, and Counting Bloom Filters
(which support deletions) cost about 4 times more space.

When Bloom filters grow too big to fit into main memory, they become
extremely slow -- Instead of supporting 1M ops/second, they slow down to
a couple hundred operations per second. 

To improve insertion performance, it is possible to employ buffering
techniques to batch writes and insert maybe 100 writes as one I/O op.

The paper introduces the Cascade Filter, which performed 670k insertions
per second and 530 lookups per second on a dataset containing 8.5B
elements.

This is about 40x faster with buffering and 3,200 times faster for
writes, but lookup throughput is 3x slower, or about the cost of 6
random reads on flash.

Thrashing is the problem -- in memory, randomly setting bits like a
Bloom Filter would isn't that expensive but RAM access is fast -- but on
disk, random access is ~10x slower than sequential access. So we know
what to do -- set bits closer to each other. 

# Design and Implementation

The Cascade Filter is inspired by a Quotient Filter, which achieves fast
performance by merging and writing QFs in an I/O efficient manner.

The QF stores p-bit fingerprints of elements. This is a compact hash
table, using the fingerprint as the key. If there are two of the same
fingerprint, we have a soft collision to be resolved with linear
probing, which sorts items in the QF they're added to.

There are three additional bits in each slot: 

`is_occupied`
`is_continuation`
`is_shifted`

A Quotient Filter may store one filter in RAM, and two layers in flash:

| 0   | E   | G   | Q   | R   | T   | W   |     |     |     |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 1   | B   | I   | K   | N   | S   | U   |     |     |     |     |     |     |
| 2   | A   | C   | D   | F   | H   | J   | L   | M   | O   | P   | V   | X   |

This can then be merged in a few I/O operations: (The merge is fast
because all three lists are guaranteed to be sorted by linear probing,
so it requires O(n) time to merge.

| 0 |   |   |   |   |   |   |   |   |   |   |   |         |
|---|---|---|---|---|---|---|---|---|---|---|---|---------|
| 1 |   |   |   |   |   |   |   |   |   |   |   |         |
| 2 |   |   |   |   |   |   |   |   |   |   |   |         |
| 3 | A | B | C | D | E | F | G | H | I | J | K | L.. etc |

A false positive occurs when two elements map to the same fingerprint.

The space usage is roughly the same as a bloom filter (1.2x a BF).

As well, reads only require $O(log(n/M))$ block reads, and an insert only
requires O((log(n/M))/B) amortized block reads.

# Evaluation

The Cascade Filter trades a 3 fold slowdown in lookup throughput on
flash in exchange for a 40x speed in insertion throughput over a BF
optimized to use all of its buffer for queuing random writes. The
Cascade Filter is CPU bound, and not I/O bound.

# Future Work

Cascade Filters are guaranteed to have better performance in the future,
as I/O scales slower than CPU, so being CPU bound instead of I/O bound
improves the scaling of this AMQ.

Future work involves applications to maybe making a parallel
implementation, which could perform 50 million inserts per second with a
drive performing 400MB/s serial writes.
