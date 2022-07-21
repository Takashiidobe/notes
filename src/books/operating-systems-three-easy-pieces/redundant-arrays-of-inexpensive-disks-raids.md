---
title: redundant-arrays-of-inexpensive-disks-raids
---

# Redundant Arrays of Inexpensive Disks (RAIDs)

Prev: [hard-disk-drives](hard-disk-drives.md)
Next:
[interlude-files-and-directories](interlude-files-and-directories.md)

RAID stands for Redundant Arrays of Inexpensive Disks. RAID allows a
group of disks to act as one disk, with the benefit that using multiple
disks in parallel improves its performance, and increases its redundancy
RAID can tolerate the loss of a disk and operate as if nothing were
wrong.

RAID also provides this advantage transparently to systems that use
them. It looks just like a normal hard disk.

## Interface and RAID Internals

To a file system, RAID just looks like a big, reliable disk.

However, RAID is normally a separate hardware box with a standard
connection (SCSI, SATA) to a host. Internally, they have firmware that
synchronizes the disks and has DRAM for block buffering, as well as
parity calculations for block writes.

## Fault Model

One model to evaluate RAID is `fail-stop`, which means that a disk is
either working or failed. There are other failures like disk corruption.

## How to Evaluate a RAID

Three axes of evaluation:

1. Capacity - How much of the total capacity is available to clients?
2. Reliability - How many disk faults can the design tolerate?
3. Performance - How fast are reads and writes?

## RAID Level 0: Striping

The first approach isn't redundant, so it's not technically RAID. It
involves `striping`, or putting blocks in a round robin fashion across
the disks. Thus, reads and writes can progress in parallel, and the
capacity used is 100% of all blocks.

This might look like:

| Disk 0 | Disk 1 | Disk 2 | Disk 3 |
|--------|--------|--------|--------|
| 0      | 1      | 2      | 3      |
| 4      | 5      | 6      | 7      |
| 8      | 9      | 10     | 11     |
| 12     | 13     | 14     | 15

### Aside: The RAID Mapping Problem

RAID blocks can be mapped like so:

```
Disk = A % number_of_disks
Offset = A / number_of_disks
```

### Chunk Sizes

Chunk size (the size of blocks before moving onto the next disk) affects
performance. A small chunk size implies that files might get striped
across many disks, which increases parallelism at the cost of
positioning time.

### Evaluating RAID Performance

To evaluate performance, there are two factors to care for:

1. Latency
2. Steady-state throughput

As well as two broad workload types:

1. Sequential
2. Random

To calculate sequential and random disk performance, we could do the
following tests on this disk:

Average seek time: 7 ms
Average rotational delay: 3 ms
Transfer rate of disk: 50 MB/s

To compute the sequential transfer rate, imagine transferring a 10 MB
block:

The seek + rotational delay is the delay before the transfer starts (10
ms), and it takes 200 ms to transfer 10 MB at 50 MB/s. Thus, the whole
transfer takes 210 ms, and the throughput is 47.62 MB/s.

For a random workload of 10 KB/s, the transfer takes 10 ms to rotate and
seek, and takes 0.195 ms to transfer 10 KB at 50 MB/s. It thus takes
10.195 ms to transfer 10 KB, with a throughput of 0.981 MB/s.

## RAID Level 1: Mirroring

RAID 1 involves mirroring each block to one other disk. This would look
like:

| Disk 0 | Disk 1 | Disk 2 | Disk 3 |
|--------|--------|--------|--------|
| 0      | 0      | 1      | 1      |
| 2      | 2      | 3      | 3      |
| 4      | 4      | 5      | 5      |
| 6      | 6      | 7      | 7      |

When reading a block from a mirrored array, it can read from either
copy. When writing, however, it must update both copies of the data. At
least they can occur in parallel -- a system that supports parallel
writes would suffer less in performance.

## RAID-1 Analysis

From a capacity standpoint, RAID-1 is expensive. With mirroring for two
copies, we can only use half our capacity. From a reliability
perspective, RAID can handle anywhere from 1 failure to N/2 failures.
Performance wise, reads are as fast as always, and writes either take
about twice as long (with no parallelism) or about the same time (just a
little worse, because of tail latencies).

Compared to RAID-0, sequential reads are the same performance, writes
are half as fast, but random reads are just as fast as RAID-0, and
random writes are half as fast.

### Aside: The RAID Consistent Update Problem

With mirroring, writes issued to two different disks could enter a state
where one fails and one succeeds. However, RAID wants a system that can
write to disks atomically. The general way to solve this is to use a
write-ahead log in non-volatile RAM. This way, consistent updating is
provided without the high cost of logging to disk.

## RAID-4: Saving Space with Parity

RAID-4 uses `parity` to add redundancy to a disk array. They use less
capacity than `mirroring`, at the cost of performance. A Parity disk
might look like this:

| Disk 0 | Disk 1 | Disk 2 | Disk 3 | Disk 4 |
|--------|--------|--------|--------|--------|
| 0      | 1      | 2      | 3      | P0     |
| 4      | 5      | 6      | 7      | P1     |
| 8      | 9      | 10     | 11     | P2     |
| 12     | 13     | 14     | 15     | P3     |

Doing parity like this enables the loss of any single disk without
data loss. This is done by XORing each bit that the parity disk holds.
To recover, the parity bit and remaining disks are XOR'ed, which allows
for reconstructing data on one disk.

### RAID-4 Analysis

RAID-4 is capacity efficient -- it allows N - 1 disks to be used.
For a sequential read, (N - 1) * S MB/s.
For a sequential write, (N - 1) * S MB/s.
Random reads are also (N - 1) * R MB/s.
Random writes, however, are R/2 MB/s. This is due to having to update
the parity value, so you must read at least the parity value and the
previous value, and write the new parity value and the new value, so
all writes cost 2 reads and 2 writes per block.

## RAID Level 5: Rotating Parity

As above, RAID-4 has the problem of requiring updates to a parity value,
which means that writes cannot succeed in parallel when updating parity
corresponding to the same block. To fix this, RAID-5 has the parity
strewn across the disks:

| Disk 0 | Disk 1 | Disk 2 | Disk 3 | Disk 4 |
|--------|--------|--------|--------|--------|
| 0      | 1      | 2      | 3      | P0     |
| 4      | 5      | 6      | P1     | 7      |
| 8      | 9      | P2     | 10     | 11     |
| 12     | P3     | 13     | 14     | 15     |
| P4     | 16     | 17     | 18     | 19     |

This improves random read performance, and write performance,
effectively making random writes progress in parallel, with a throughput
of N / 4 R.

Prev: [hard-disk-drives](hard-disk-drives.md)
Next:
[interlude-files-and-directories](interlude-files-and-directories.md)
