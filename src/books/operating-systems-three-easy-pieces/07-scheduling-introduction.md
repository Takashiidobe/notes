---
title: scheduling-introduction
---
# Scheduling: Introduction

Prev: [[06-mechanism-limited-direct-execution]]
Next: [[08-scheduling-the-multi-level-feedback-queue]]





This chapter is devoted to presenting a series of scheduling policies
for efficient execution of OS processes.

## Workload Assumptions

Before getting started, lets make 5 unrealistic assumptions to simplify
our workload:

1. Each job runs for the same amount of time
2. All jobs arrive at the same time.
3. Once started, each job runs to completion.
4. All jobs only use the CPU
5. The run-time of each job is known.

## Scheduling Metrics

We need metrics to compare different policies. Let's start with
**turnaround time**, which is defined as `T(turnaround) = T(completion) - T(arrival)`.

We want to optimize for **efficiency** (the CPU is idle as little as
possible) and **fairness** (each process gets equal time to make
progress).

## First In, First Out (FIFO)

Let's say 3 jobs (A, B, C) which each run for 10 seconds are processed
in that order. What is the average turnaround time?

`10 + 20 + 30 / 3 = 20`.

Let's relax the assumption that all jobs run for the same amount of
time:

Now lets say that A runs for 100 seconds, and B and C run for 10
seconds.

The average turnaround time becomes:

`100 + 110 + 120 / 3 = 110`.

This is called the **convoy effect**, because short jobs are blocked by
a long running job.

## Shortest Job First (SJF)

Think about what happens if we process (B, C) then (A).

The average turnaround time becomes:

`10 + 20 + 120 / 3 = 50`.

This is actually **optimal** for any workload. But we need to know how
long a job will run for, and they have to arrive at the same time, which
is unrealistic.

## Shortest Time-to-Completion First (STCF)

Now lets relax assumption 3. The OS can now preempt (stop) processes and
run another task. Assume we have (A, B, C) which run for (100, 10, 10)
seconds. If A arrives first, then B and C, as soon as B and C arrive,
the scheduler can run B and C and then finish with A.

This results in an optimal turnaround time:

`(120) + (20 - 10) + (30 - 10) / 3 = 50`.

## A New Metric: Response Time

If we only knew job lengths, and jobs only used the CPU, and our only
metric was turnaround time, STCF would be the best policy.

However, we run on computers that don't just run batch jobs. We want
jobs to respond to us quickly.

In that case, Shortest Job first is abysmal, since job C has to wait 20
seconds before it runs.

## Round Robin (RR)

To solve this problem, Round Robin scheduling is introduced, where a job
is run for a time slice, and then switches to the next job in the run
queue.

Assume that (A, B, C) each take 5 seconds, and arrive at the same time.

In SJF, the average response time is `0 + 5 + 10 / 3 = 5`, whereas in
round robin, with a time-slice of 1 second would be `0 + 1 + 2 / 3 = 1`.

Assuming that context switching has an overhead, we need to tune the
amount of time that each job runs before swapping, amortizing the cost
can reduce the time complexity.

In turnaround time, though, RR is the worst, since it finishes jobs at
(13, 14, 15) instead of (5, 10, 15) like SJF/STCF.

The fairest algorithm is now the least efficient in terms of turnaround
time.

## Incorporating I/O

With the requirement of no I/O being relaxed, we now have a choice.
Assume every I/O operation takes 10ms, and the CPU is blocked waiting
for I/O completion.

Imagine there are two kinds of jobs, A (which runs for 10ms, then issues
a 10ms blocking I/O request) and B, which just runs for 50ms.

In the case that you run A and then wait for the I/O request, it takes
20ms. But if you can overlap B while running A, then A realistically
only takes 10ms.

## No More Oracle

Lets remove the assumption that we can know _a priori_ the execution
time of any job. Now we have to exclude SJF and STCF, which only leaves
us with RR. What can we do?

Prev: [[06-mechanism-limited-direct-execution]]
Next: [[08-scheduling-the-multi-level-feedback-queue]]
