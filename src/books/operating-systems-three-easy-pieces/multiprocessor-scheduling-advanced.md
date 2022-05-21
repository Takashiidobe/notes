---
title: multiprocessor-scheduling-advanced
---

# Multiprocessor Scheduling (Advanced)

Prev:
[scheduling-proportional-share](scheduling-proportional-share.md)
Next:
[summary-dialogue-on-cpu-virtualization](summary-dialogue-on-cpu-virtualization.md)

Multiprocessor scheduling is motivated with computers now having
multiple cores which can run tasks with a synchronization penalty.

## Background: Multiprocessor Architecture

Cores each have their own hardware caches in a hierarchy that help
programs run faster. Caches are based on locality:

1. Temporal locality (if a piece of data is accessed, it will most
   likely be soon).
2. Spatial locality (if a piece of data is accessed, items around it
   will most likely be accessed).

One problem with caching is cache coherence -- if you write to main
memory, you have to either invalidate the cached data or write through
the cache as well to keep it up to date.

## Don't Forget synchronization

When programs access shared data, they still have to synchronize their
accesses. This is mainly done by locking or atomics (lock-free)
structures.

## One Final Issue: Cache Affinity

There's an issue called **cache affinity**, whereby a process that runs
on a particular CPU will run faster on that CPU if run again (because it
builds state on that CPU). Cache affinity affects performance, so it
matters when building a scheduler.

## Single-Queue Scheduling

To make a basic multiprocessor scheduler, you could create a
multithreaded queue with locks -- called single-queue multiprocessor
scheduling. 

Locking cuts down performance a lot, however, and reduces scalability.

Imagine four CPUs with five jobs:

A -> B -> C -> D -> E 

CPU 1: A E D C B 
CPU 2: B A E D C 
CPU 3: C B A E D 
CPU 4: D C B A E 

This is bad for cache affinity, so we can try to put them on the same
CPU:

CPU 1: A E A A A 
CPU 2: B B E B B 
CPU 3: C C C E C 
CPU 4: D D D D E

Which improves its performance

## Multi-Queue Scheduling

We can improve scaling by having multiple queues, like one per CPU.

If we have two jobs and two CPUs: 

Q1: A -> C 
Q2: B -> D

CPU1: A A C C A A C C 
CPU2: B B D D B B D D

We get an even distribution.

If there's load imbalance however, 

Q1: A
Q2: B -> D

CPU1: A A A A A A A A 
CPU2: B B D D B B D D

This fails to work as desired.

However, we can make this work by migrating jobs between the processors,
where if we see that CPU1 only has one job, we can migrate another job
to it, to share load.

To deal with this, a **work stealing** approach could work. A source
queue that is low on work would look at a target queue and try to steal
work from it if it has more work.

## Linux Multiprocessor Schedulers

The O(1) scheduler, CFS, and BFS are some example Linux Multiprocessor
schedulers. The O(1) scheduler uses priority, CFS uses a deterministic
proportional share approach, and BFS has a proportional share approach.

Prev:
[scheduling-proportional-share](scheduling-proportional-share.md)
Next:
[summary-dialogue-on-cpu-virtualization](summary-dialogue-on-cpu-virtualization.md)
