---
title: scheduling-proportional-share
---
# Scheduling: Proportional Share

Prev: [[08-scheduling-the-multi-level-feedback-queue]]
Next: [[10-multiprocessor-scheduling-advanced]]





This chapter describes a proportional share scheduler, which uses a
lottery to find the next process to run.

## Basic Concept: Tickets Represent Your Share

To pick the next process, assume there are 2 processes, A and B, where A
has 75 tickets and B has 25 tickets. 

The lottery takes up the total tickets (100) and generates a number from
0 to n - 1. The winner (0-74 for A, or 75-99 for B) gets to run for the
next time slice.

Random approaches are fast because they have little overhead, at the
cost of being non-deterministic (maybe process B gets really lucky and
wins the next four elections, starving out process A).

LRU caches, for example, have worse case runtimes that are worse than
random election -- if you have a cache smaller than the data being
cached, and you do a linear sweep, the LRU cache never does anything,
whereas a random algorithm may cache items.

## Ticket Mechanisms

Lottery scheduling with tickets allows us to manipulate tickets in
different and useful ways.

Ticket currency allows processes to issue their own currency which is
convertible to "global" tickets.

Ticket transfer, where a process can hand off its tickets to another
process is also useful, and ticket inflation, where a process can
increase or decrease its ticketed amount.

## Implementation

To implement lottery scheduling, we might imagine a linked list where
each job has its number of tickets. Then, after we generate a random
number, we traverse a linked list to find out which job to run.

This works, but can take a while to find the correct process.

## An example

We can measure the fairness of schedulers by using something called an
**unfairness metric**, which is the time the first job completes divide
by the time that the second job completes.

As noted, the longer the job length is, the more it trends towards
equality.

## How to Assign Tickets?

Unfortunately with this method, we can't figure out how to allocate
tickets to jobs. We could ask users, but we know from before that
doesn't end well.

## Why Not Deterministic?

There is a way of deterministically allocating a schedule, using stride
scheduling -- each job is given a stride, which is an inverse of the
amount of tickets it has.

For example, if A, B, C have 100, 50, 250 tickets, let's divide their
tickets by a large number (like 10000).

Every time we want to increment a number, we can increment a counter for
it (its pass value) to track its global process.

Then the scheduler picks the value with the lowest pass value so far.

This is completely deterministic, but has the pitfall of requiring
global state.

## The Linux Completely Fair Scheduler (CFS)

CFS uses an RB tree to balance processes, and uses an idea of virtual
runtime (vruntime) to pick a process. As each process runs, it
accumulates vruntime. The scheduler picks the process with the lowest
vruntime to run next.

CFS chooses how long a process should run through **sched_latency**,
which is normally 48 milliseconds. It then will allow each process to
run for a time slice being 48 ms / process_count.

If we had a lot of processes, that would lead to a lot of context
switching, so there's also **min_granularity**, normally set to 6ms to
make sure that a time slice never goes below that number.

As well, CFS allows for a `niceness` value, which allows a user to
increase or decrease the priority of a process.

### Using Red-Black Trees

Since RB Trees are balanced, CRUD operations on it are never more than
(log n) instead of O(n). 

### Dealing with I/O and Sleeping processes

If a process runs continuously vs going to sleep, CFS avoids starvation,
where jobs that sleep for a while will fall behind continuously running
processes.

Prev: [[08-scheduling-the-multi-level-feedback-queue]]
Next: [[10-multiprocessor-scheduling-advanced]]
