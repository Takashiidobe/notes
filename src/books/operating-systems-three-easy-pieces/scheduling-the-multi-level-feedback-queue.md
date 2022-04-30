---
title: scheduling-the-multi-level-feedback-queue
---

# Scheduling: The Multi-Level Feedback Queue

Prev:
[scheduling-introduction](scheduling-introduction.md)
Next:
[scheduling-proportional-share](scheduling-proportional-share.md)

Since we no longer know how long jobs will last, let's optimize for
turnaround time and response time (efficiency and fairness).

## MLFQ: Basic Rules

MLFQ has a number of distinct queues, which are assigned a different
priority level.

There are two basic rules:

1. If Priority(A) > Priority(B) A runs (B doesn't)
2. If Priority(A) = Priority(B) A & B run in RR.

They key to MLFQ is how it sets priority. If a job relinquishes the CPU
while waiting for input from the keyboard, MLFQ keeps its priority high.
However, if a job uses CPU intensively for long periods of time, MLFQ
will reduce its priority. Thus, it uses history to predict future
behavior.

## Attempt 1: How to Change Priority

3. When a job enters the system, it is placed at the highest priority
   (the topmost queue).
4. If a job uses up an entire time slice while running, its priority is
   reduced. (goes down one queue)
5. If a job gives up the CPU before the time slice is up, it stays at
   the same priority level.

### Example 2: Along Came a Short Job

Imagine if there's a long running job A, where B, a short running job
comes in.
Well, as soon as B comes in, it will run on the next time slice, and
then A would run. This is good for turnaround time and response time.

The key here is that MLFQ guesses that jobs are short running, and
penalizes it the longer it runs (treats it more like a batch job).

### What about I/O?

If a job runs I/O before its time slice is up, it relinquishes control
to the CPU and gets to stay at the same level.

### Problems with our Current MLFQ

1. There's a problem with starvation -- if there are too many short jobs
   in the system, then long running jobs in the system will never make
   any progress.
2. It's possible to game the scheduler -- if you know how long each time
   slice is, you could devise a process which runs for just about that
   amount of time, and then issue an I/O request to stay at the same
   priority level (the top).
3. Finally, some jobs might be short running and then longer running or
   vice-versa. In that case, MLFQ will penalize or benefit it too much.

## Attempt 2: The Priority Boost

To avoid starvation, we can periodically boost the priority of all the
jobs in the system, by making a new rule.

6. After some time period S, move all the jobs in the system to the
   topmost queue.

This fixes the starvation problem, at the cost of requiring a voodoo
constant. What should we set S to? It could be configurable.

## Attempt 3: Better Accounting

To stop gaming of the system, we can keep track of how much CPU time
each process has used. Rewriting rule 4:

4. Once a job uses up its time allotment at a given level (regardless of
   how many times it has given up the CPU), its priority is reduced.

## Tuning MLFQ And Other Issues

A few other issues arise with MLFQ. How many queues should there be? How
long should the time slice be? How long should the priority bump be?

Maybe we can use some sort of a decay to penalize certain actions.

Prev:
[scheduling-introduction](scheduling-introduction.md)
Next:
[scheduling-proportional-share](scheduling-proportional-share.md)
