# Design the interface for a Job Queue

We have a service that allows people to submit long running jobs to us,
and we process them.

We want to process these as fast as possible (obviously).

We allow our users to submit a job, and query for job status.

Jobs can be paused (at some penalty) and their progress can be saved
before swapping to another job.

How do we make an efficient and fair job queue?

## Questions

- What happens if some jobs take longer than others? (i.e. some are simple
  calculations, some are I/O bound).

- What happens if we want to prioritize certain tasks instead of others
  (they are more mission critical than others?)

- What happens if we don't know how long a job will take before
  accepting it?

- Can we add concurrency to good effect here? What are the pitfalls with
  concurrent jobs running?

## Solutions

- Lifo (Last in first out)
- Fifo (First in first out)
- Time-Based (prioritize shorter jobs first)
- Round Robin (Give each job a fixed slice of processor time in order)
- O(n) (Each task gets a fixed quantum. If it needs more time in the
  next round, it is granted more time).
- O(1) (use an array of active and expired tasks, where each task is
  given a fixed time quantum, and then preempted and moved to the
  expired array). Once all the tasks from the active array have
  exhausted their time, a switch takes place, which can be done in O(1)
  time.
- CFS (priority queue with RB-tree)
