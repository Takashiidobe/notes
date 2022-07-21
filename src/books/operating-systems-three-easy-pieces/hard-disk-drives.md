---
title: hard-disk-drives
---

# Hard Disk Drives

Prev: [io-devices](io-devices.md) Next:
[redundant-arrays-of-inexpensive-disks-raids](redundant-arrays-of-inexpensive-disks-raids.md)

## The Interface

A disk can be viewed of as a set of 512-byte sectors.

Each read/write to a section is considered atomic -- if a large section
is written to, but there's a failure, it may only succeed partially.

## Basic Geometry

A simple disk might look like a platter, a circular hard surface where
data is stored by inducing magnetic changes to it.

The drive is coded with a thin magnetic layer which enables the drive to
persistently store bits even with the drive is off.

A spindle binds the platters together, which has a certain RPM
(rotations per minute).

Data is encoded in concentric circles of sectors, called a track.

## A Simple Disk Drive

A disk head, which reads and writes to and from the disk is attached to
the spindle.

### Single-track Latency: The Rotational Delay

Imagine a circle with the sectors numbering the disk like a clock
(0-11). Any write, at worst case, requires N/2 or rotational delay. If
we're on 0, the worst case read/write location would be at 6, or
vice-versa.

### Multiple Tracks: Seek Time

A real life hard disk would have multiple tracks, instead of just one.
The tracks would be layered on top of each other. When the arm has to
move from one track to the next, it does a `seek`, where it moves from
tracks. This can take a lot of time (0.5 to 2 ms), as the drive must find
the correct track to then rotate to.

### Some Other Details

Many drives use `track skew` to make sure that sequential reads can be
properly serviced when crossing track boundaries.

As well, some disks are `multi-zoned`, where zones are consecutive to
service faster reads and writes.

As well, disks have a cache, which take care of temporal and space
locality (if you read one sector, you'll probably read the adjacent
ones), so disks can populate cache with neighbors.

On writes, the drive can either populate the cache first, or the cache
afterwards. Writing to the cache first, then the disk makes writes look
faster, but can lead to problems (if the power goes out, an acknowledged
write can be lost).

## I/O Time: Doing The Math

Disk I/O can be calculated with the following:

I/O Time = Seek Time + Rotation Time + Transfer Time

The rate of I/O can be calculated by:

I/O Rate = Size / I/O Time

Let's do the math on two Hard Disk Drives from Seagate:

|              | Cheetah 15K.5 | Barracuda |
|--------------|---------------|-----------|
| Capacity     | 300 GB        | 1 TB      |
| RPM          | 15,000        | 7,200     |
| Average Seek | 4 ms          | 9 ms      |
| Max Transfer | 125 MB/s      | 105 MB/s  |
| Platters     | 4             | 4         |
| Cache        | 16 MB         | 16/32 MB  |
| Connects via | SCSI          | SATA      |

Assume that a 4KB read occurs at a random location on disk, for the
cheetah:

Seek Time = 4 ms, Rotation Time = 2 ms, Transfer Time = 30 microseconds

This is about 6 ms. A random I/O should thus take about 6 ms for the
Cheetah, and 13.2 ms for the Barracuda.

A sequential workload might look like this:

For a 100 MB transfer, with an 800 ms write speed, the throughput is
125 MB/s.

### Computing the "Average" Seek

The average seek is about 1/3 the seek distance.

## Disk Scheduling

Because I/O has a high cost, the OS will try to schedule it like
processes. But since it also knows the size of the I/O request, it can
try to greedily pick the shortest jobs for maximal efficiency.

### SSTF: Shortest Seek Time First

One early disk scheduling approach is Shortest Seek Time First, which
prioritizes writes to the same/nearest tracks. However, it has two
problems:

1. The OS doesn't understand tracks (it can use nearest-block-first,
   NBF).
2. Some requests may starve (if there are lots of requests to the same
   track, then further away tasks would not get scheduled.

### Elevator (SCAN or C-SCAN)

Another algorithm that avoids starvation is SCAN, which queues up I/O
requests, and then does a single pass across the disk (a sweep). It then
repeats.

One variant is C-SCAN, or Circular SCAN. The algorithm sweeps from outer-to-inner, and then restarts.

This is known as the `elevator` algorithm, as it goes from the bottom to
the top, then repeats.

### SPTF: Shortest Positioning Time First

Instead of SSTF, which assumes that seeking is slower than rotational
delay, we can do `SPTF`, which uses more detailed information to figure
out the distance of each rotation + seek, and maximizes the output of
I/O.

### Other Scheduling Issues

Some other scheduling issues involve when to merge I/O requests for
increased efficiency, like if there are these requests:

1. read block 33
2. read block 8
3. read block 34

The scheduler would be better served merging 1 and 3 to get this result:

1. read block 33, 34
2. read block 8

As well, there's an issue of `work-conserving` vs `anticipatory disk
scheduling`, where a disk might wait for newer I/O requests so as to get
more optimal requests to batch up.

Prev: [io-devices](io-devices.md)
Next:
[redundant-arrays-of-inexpensive-disks-raids](redundant-arrays-of-inexpensive-disks-raids.md)
