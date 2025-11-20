---
title: beyond-physical-memory-policies
---
# Beyond Physical memory: Policies

Prev: [[31-beyond-physical-memory-mechanisms]]
Next: [[33-complete-virtual-memory-systems]]





When the OS is low on memory, it has to decide to evict certain pages.
There's lots of policies to do so.

## Cache Management

It's important to minimize the number of cache misses. This can be
measured by Average Memory Access Time or AMAT.

Let's say that accessing memory costs 100 ns, and disk is about 10 ms.
If we have a 90% hit rate, then AMAT becomes 1 ms. If we get to 100% hit
rate, it approaches 100 ns.

## The Optimal Replacement Policy

The Optimal replacement policy models the following idea -- the cache
should throw out the one required furthest from now.

Assume we can hold 3 pages, and we access the pages like so:

0,1,2,0,1,3,0,3,1,2,1

We first populate the cache by missing 3 times.

Then, we have 2 hits, a miss, where we evict 2, then three hits, a miss,
then a hit.

In this case, the optimal policy is 5 hits and 5 misses.

## A Simple policy: FIFO

A queue is pretty good, but fails to be optimal in this case -- there's
a hit rate of 36%. Simply holding onto the most recently used pages
doesn't work if your workflow doesn't align with that.

Belady's anomaly here found out that FIFO even performs worse when the
cache is increased for FIFO.
LRU Cache always performs better when its stack size increases, but
neither FIFO nor random do, oddly enough.

This is because the LRU cache has a stack property -- every time you
increase its size, it performs better than previously.

## Another Simple Policy: Random

Random picks a random page to replace. Sometimes it does well -- about
40% of the time it was optimal, but sometimes it had 2 hits or fewer.

## Using History: LRU

LRU uses two observations to get more optimal: it uses history to
replace the page that was used last. Similarly, LFU replaces the page
that was used least.

In this workload, LRU is optimal, since it follows cache locality
principles.

## Workload Examples

As long as we generate a workload without locality, all of the previous
algorithms perform about the same. But with locality, LRU performs the
best.

If we generate a workload where 20% of the pages get 80% of the reads
(80-20 workload) then LRU does by far the best.

With a looping workload (Linear sweep, where the items are accessed in a
loop), Random does by far the best, with close to a 100% hit rate.

## Implementing Historical algorithms

LRU comes with huge overhead -- the classical O(1) algorithm access
costs O(n) memory -- with 1 million pages, this would cost maybe 8MB or
so, which is pretty heavy compared to 0 (FIFO) or random (maybe 32 bits?)

Lets try an approximation.

## Approximating LRU

One way to approximate LRU is to use a use bit. With some hardware
support, we can imagine the pages of the system arrange in a circular
list. Then, a clock hand points to a particular page. When a replacement
must occur, the clock hand increments each array until it finds a 0 bit,
which it then tries to free. It then sets that bit to 0 and moves on.
This does pretty closely well to LRU, for little overhead (a bit
array)

## Considering Dirty Pages

If the page has been modified and is thus dirty, it must be written back
to disk to evict it, which is expensive. However, if the page has not
been modified (it is clean) it can be freed cheaply -- so sometimes the
OS might prefer to free clean pages.

## Other VM Policies

The OS might choose between on demand paging (bringing in a page on
demand) or prefetching (doing it ahead of time if there's a reasonable
chance of success). For example, if page P is accessed, it might
reasonable to assume that page P+1 will be accessed soon, and so it
should be added to the cache line.

## Thrashing

Thrashing occurs when the OS is oversubscribed (there's too much memory
usage for the OS). Some previous OSes would try to run a smaller number
of processes with the hope that would allow some processes to make
progress.

Linux runs an Out of memory killer, where the daemon kills processes
that use a lot of memory.

Prev: [[31-beyond-physical-memory-mechanisms]]
Next: [[33-complete-virtual-memory-systems]]
