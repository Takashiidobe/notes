# Scheduling in Linux

Linux by default uses a Completely Fair Scheduling (CFS) algorithm, which implements Weighted Fair Queueing (WFQ).

CFS starts by time-slicing the CPU among running threads. Each thread in the system gets to run at least once per timeslice (an epoch).

A thread accumulates vruntime (runtime / weight). When a thread's vruntime exceeds its assigned timeslice, it gets pre-empted.

This can be adjusted with `nice` or `renice`.

Threads are organized in a runqueue, implemented as an RB-Tree. When a CPU wants to pick a new thread, it picks the leftmost node in the RB-Tree, which contains the smallest vruntime.

With multi-cores, however, each core needs its own queue of tasks to run, but those tasks can become unbalanced, which lowers efficiency.

To mitigate this, CFS load-balances runqueues between cores to keep them roughly balanced. This is expensive and incurs cache locality penalities, so the load balancer tries its best to only move threads betweens cores that are physically close on the processor. If it can't find one close, then it'll widen its search until it can find a better core.

## Four Bugs

### Group Imbalance

The scheduler only used to look at average load of cores, which led relatively free cores to not steal work from overloaded cores. To fix this, the comparison worked off of minimum loads.

### Scheduling Group Construction

Scheduling groups could have nodes in multiple groups. If that was the case, then work could not be shared to the other group, because their average workload would look relatively similar to the scheduler.

### Overload-on-wakeup

When a thread goes to sleep on node X, and the thread that wakes it up later is running on that same node, it will try to use a core on that node, (to optimize cache locality). The scheduler was fixed to look at all idle cores, which worked better for workloads with lots of sleeping.

### Missing scheduling domains

There was another bug where if a core was disabled and then renabled, load balancing between the nodes never occurred, so that core would no longer be able to steal work. This led to a 138x speedup in one case.
