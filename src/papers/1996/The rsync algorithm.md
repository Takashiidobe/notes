---
pdf_url: "[[The rsync algorithm.pdf]]"
title: The Rsync Algorithm
---

# The Rsync Algorithm

## Problem

The rsync algorithm is a general purpose algorithm to only send changes of files through the network.

- Assume two computers A and B are connected by a network.
- Assume the network is slow.
- Assume computer A has file F', and computer B has file F.
- F' is "similar" or has only been updated a little from F.

Instead of sending the entire file from A to B over the network (which would be prohibitively expensive) we want to find the changes (deltas) of files, send them from A to B, and have B reconstruct the new file using the previous file.

## The Algorithm

1. Computer A splits F' into non-overlapping fixed-sized blocks of size S bytes. The last block can be shorter than S bytes.
2. For each of these blocks, A calculates two checksums: a weak "32-bit" checksum, and a "strong" 128-bit MD4 checksum.
3. A sends all of these checksums to B.
4. B searches through F to find all blocks of S bytes that have the same weak and strong checksums as one of the blocks of F'.
5. A sends B a sequence of instructions for constructing a copy of F'.Each instruction is a reference to a block of F', or literal data.

## Rolling Checksum

The rolling checksum is a variant of Adler-32. Because it is a rolling checksum, it can be used to calculate successive values very quickly.

## Checksum Searching

The checksum searching algorithm is 3-leveled. The basic strategy computes the 32-bit rolling checksum for a block of length S in F'. The 32-bit checksums are hashed into a 16-bit hashtable, which points to the first match in the list, or a null pointer if there is no match.

At each offset, the 32-bit rolling checksum and its 16-bit hash are calculated. If there is no match, the second level check is invoked.

Next, the algorithm goes through the hashtable list in order to find a match. If it does not find a match, the third level check is invoked.

The third level check involves calculating the strong checksum for the offset, and comparing it with the strong checksum value in the current list entry. If they match, we have found a match, otherwise, there is some small chance they are different, but this is generally fine. This allows the algorithm to use the rolling characteristic of the checksum to quickly check of differences.

## Pipelining

It is easy to pipeline to this algorithm, as one process on each machine can deal with the checksum sending + receiving, while the other process can send and receive checksums. As well, this can be done on multiple files at once, so there is further opportunity for parallelism.