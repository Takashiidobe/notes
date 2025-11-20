---
title: common-concurrency-problems
---
# Common Concurrency Problems

Prev: [[18-semaphores]]
Next: [[20-event-based-concurrency-advanced]]





## What Types Of Bugs Exist?

There are lots of concurrency bugs. A study by Lu et. al (2008) analyzed
bugs in MySQL, Apache, Mozilla, and OpenOffice. Most bugs were deadlock,
and the remaining were deadlock bugs.

## Non-Deadlock Bugs

Non-Deadlock bugs can be characterized as Atomicity-Violation bugs, or
Order Violation bugs.

### Atomicity Bugs

Atomicity bugs look like this:

```c
Thread 1::
if (thd->proc_info) {
  fputs(thd->proc_info, ...);
}

Thread 2::
thd->proc_info = NULL;
```

First, thread 1 checks to see if `thd->proc_info` (a file to print to)
is not `NULL`. Then, it writes to it.

Thread 2 sets `thd->proc_info` to `NULL`.

If thread 1 is interrupted after the if conditional but before the
`fputs`, thread 2 will set it to `NULL` and then cause a crash.

This code assumes that the call to `thd->proc_info` and `fputs` are
atomic (in a transaction). To fix the code, we do exactly that:

```c
pthread_mutex_t proc_info_lock = PTHREAD_MUTEX_INITIALIZER;

Thread 1::
pthread_mutex_lock(&proc_info_lock);
  if (thd->proc_info) {
    fputs(thd->proc_info, ...);
  }
pthread_mutex_unlock(&proc_info_lock);

Thread 2::
pthread_mutex_lock(&proc_info_lock);
thd->proc_info = NULL;
pthread_mutex_unlock(&proc_info_lock)
```

### Order-Violation Bugs

Order Violation bugs occur if the code requires A to be before B, but
sometimes B can be run before A. In this case, `mMain` needs to be
initialized, but it is not always. This can be fixed with a condvar.

```c
Thread 1::
void init() {
  mThread = PR_CreateThread(mMain, ...);
}

Thread 2::
void mMain(...) {
  mState = mThread->State;
}
```

```c
pthread_mutex_t mtLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t mtCond = PTHREAD_COND_INITIALIZER;
int mtInit = 0;

Thread 1 ::void init() {
  ... mThread = PR_CreateThread(mMain, ...);

  // signal that the thread has been created...
  pthread_mutex_lock(&mtLock);
  mtInit = 1;
  pthread_cond_signal(&mtCond);
  pthread_mutex_unlock(&mtLock);
  ...
}

Thread 2 ::void mMain(...) {
  ...
      // wait for the thread to be initialized...
      pthread_mutex_lock(&mtLock);
  while (mtInit == 0)
    pthread_cond_wait(&mtCond, &mtLock);
  pthread_mutex_unlock(&mtLock);

  mState = mThread->State;
  ...
}
```

Most bugs were either atomicity or order violations (97%). Using
Mutexes, semaphores, and CondVars properly prevents most of these bugs
from happening.

## Deadlock Bugs

Deadlock occurs if there is a cycle in the calling graph which acquires
locks.

Four conditions are required for deadlock:

1. Mutual Exclusion: Threads require exclusive control
2. Hold-and-wait: Threads hold resources and wait for more resources
3. No preemption: Resources cannot be removed from threads holding them.
4. Circular wait: There exists a circular chain of threads such that
   each thread holds one or more resources in the chain.

### Prevention

#### Circular Wait

Breaking circular wait is the most common mitigation strategy -- if you
write your locks in a way that acquiring them is totally ordered, there
is no circular wait, and no deadlock.

In more complex systems, a partial ordering is good enough.

One simple way of doing this is to use the addresses of mutexes for
locking order.

```c
void do_work(mutex *m1, mutex *m2) {
  if (m1 > m2) {
    m1->lock();
    m2->lock();
  } else {
    m2->lock();
    m1->lock();
  }
}
```

#### Hold-and-wait

Hold and wait involves using a global lock that guards all of the other
locks:

```c
prevention->lock();
lock_1->lock();
lock_2->lock();
prevention->unlock();
```

This approach is fairly inefficient and breaks encapsulation, so it is
not as popular as applying an ordering to locks.

#### No Preemption

We could use preemption, where a thread tries to grab a lock if it can,
and otherwise tries again.

```c
top:
  pthread_mutex_lock(L1);
  if (pthread_mutex_trylock(L2) != 0) {
    pthread_mutex_unlock(L1);
    goto top;
  }
```

This leads however to `livelock`, where two threads could try to grab
both locks and keep failing, leading not to deadlock, but a state where
two threads cannot make progress. This is also inefficient and less
common.

#### Mutual Exclusion

Herlihy noted that one could design data structures without locks at
all, making `lock-free` and `wait-free` data structures.

All this requires is to have a Compare and Swap routine, which we can
use to make other routines, like increment.

List insertion would look like this, and be `lock-free`:

```c
void insert(int value) {
  node_t *n = malloc(sizeof(node_t));
  assert(n != NULL);
  n->value = value;
  do {
    n->next = head;
  } while (CompareAndSwap(&head, n->next, n) == 0);
}
```

#### Deadlock Avoidance via Scheduling

Assume that there are four threads grabbing two locks. T1 and T2 grab L1
and L2, and T3 only grabs L2.

|    | T1  | T2  | T3  | T4 |
|----|-----|-----|-----|----|
| L1 | yes | yes | no  | no |
| L2 | yes | yes | yes | no |

A scheduler might figure out that as long as T1 and T2 are not scheduled
on the same CPU, deadlock cannot occur, and thus would not schedule
those processes.

This requires static knowledge, which is useful in some systems but not
widely applicable.

#### Detect and Recover

Just Restart your computer when deadlock occurs.

Prev: [[18-semaphores]]
Next: [[20-event-based-concurrency-advanced]]
