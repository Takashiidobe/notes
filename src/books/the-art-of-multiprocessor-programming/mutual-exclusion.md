---
title: "Mutual Exclusion"
---
# Mutual Exclusion

Prev: [introduction](books/the-art-of-multiprocessor-programming/introduction.md)
Next: [concurrent-objects](concurrent-objects.md)

## Time and events

Reasoning about concurrent computation is mostly reasoning about time.
Sometimes we want things to happen simultaneously, and sometimes at
different times.

Threads share a common time, and are state machines that transition
through events.

We say that if a precedes b, this is written as `a -> b`, and applies a
total order on events.

## Critical sections

Mutual exclusion is used to guard **critical sections**, a block of code
that can only be executed by one thread at a time.

```java
public class Counter {
  private long value;
  private Lock lock; // for the critical section

  public long getAndIncrement() {
    lock.lock();
    try {
      long temp = value;
      value = temp + 1;
      return temp;
    } finally {
      lock.unlock();
    }
  }
}
```

Every lock should satisfy mutual exclusion, deadlock freedom, and
freedom from starvation.

## Two-thread solutions

### The LockOne class

To solve the LockOne algorithm, a thread sets its flag to true and waits
until the other thread's flag is false. When that's done, it finally
returns.

```java
class LockOne implements Lock {
private boolean[] flag = new boolean[2];
  // thread-local index, 0 or 1
  public void lock() {
    int i = ThreadID.get();
    int j = 1 - i;
    flag[i] = true;
    while (flag[j]) {} // wait until flag[j] == false
  }
  public void unlock() {
    int i = ThreadID.get();
    flag[i] = false;
   }
 }
```

Unfortunately, this algorithm can deadlock if thread executions are
interleaved.

### The LockTwo class

This algorithm supports mutual exclusion, but it gets stuck unless the
threads run concurrently, the opposite of LockOne.

```java
class LockTwo implements Lock {
 private int victim;
 public void lock() {
  int i = ThreadID.get();
  victim = i; // let the other go first
  while (victim == i) {} // wait
 }
 public void unlock() {}
}
```

### The Peterson Lock

The Peterson Lock supports a starvation-free lock for two-thread mutual
exclusion.

```java
class Peterson implements Lock {
// thread-local index, 0 or 1
private boolean[] flag = new boolean[2];
private int victim;
  public void lock() {
    int i = ThreadID.get();
    int j = 1 - i;
    flag[i] = true; // I’m interested
    victim = i; // you go first
    while (flag[j] && victim == i) {} // wait
  }
  public void unlock() {
  int i = ThreadID.get();
  flag[i] = false; // I’m not interested
  }
}
```

## Notes on deadlock

Even though the Peterson Lock is deadlock-free, if multiple peterson
locks are used, livelock can ensue, in which two threads prevent each
other from making progress.

## The filter lock

The filter lock generalizes the Peterson lock to work for n > 2. It
creates n - 1 `waiting rooms`, called levels.

```java
class Filter implements Lock {
int[] level;
int[] victim;
  public Filter(int n) {
  level = new int[n];
  victim = new int[n]; // use 1..n-1
    for (int i = 0; i < n; i++) {
    level[i] = 0;
    }
  }
  public void lock() {
    int me = ThreadID.get();
    for (int i = 1; i < n; i++) { // attempt to enter level i
    level[me] = i;
    victim[i] = me;
    // spin while conflicts exist
    while ((∃k != me) (level[k] >= i && victim[i] == me)) {};
    }
  }
  public void unlock() {
    int me = ThreadID.get();
    level[me] = 0;
  }
}
```

## Fairness

Although the filter lock is starvation-free, a thread might be overtaken
arbitrarily many times by another thread, because accesses to the
critical section are not **first-come-first-served**.

To make this happen, we can split the `lock()` method into a doorway and
a waiting section, where the doorway completes in a bounded number of
steps, before entering the waiting area.

```java
class Bakery implements Lock {
  boolean[] flag;
  Label[] label;
  public Bakery (int n) {
    flag = new boolean[n];
    label = new Label[n];
    for (int i = 0; i < n; i++) {
      flag[i] = false; label[i] = 0;
    }
  }
  public void lock() {
    int i = ThreadID.get();
    flag[i] = true;
    label[i] = max(label[0], ...,label[n-1]) + 1;
    while ((∃k != i)(flag[k] && (label[k],k) << (label[i],i))) {};
  }
  public void unlock() {
    flag[ThreadID.get()] = false;
  }
}
```

## Lamport's Bakery algorithm

Lamport's bakery algorithm guarantees the `first-come-first-served`
property, while fulfilling mutual exclusion, being deadlock-free, and
starvation free.

```java
AtomicIntegerArray ticket = new AtomicIntegerArray(threads); // ticket for threads in line, n - number of threads
// Java initializes each element of 'ticket' to 0

AtomicIntegerArray entering = new AtomicIntegerArray(threads); // 1 when thread entering in line
// Java initializes each element of 'entering' to 0

public void lock(int pid) {
    // thread ID
    entering.set(pid, 1);
    int max = 0;
    for (int i = 0; i < threads; i++) {
        int current = ticket.get(i);
        if (current > max) {
            max = current;
        }
    }
    ticket.set(pid, 1 + max);
    entering.set(pid, 0);
    for (int i = 0; i < ticket.length(); ++i) {
        if (i != pid) {
            while (entering.get(i) == 1) { Thread.yield(); } // wait while other thread picks a ticket
            while (ticket.get(i) != 0 && ( ticket.get(i) < ticket.get(pid) ||
                    (ticket.get(i) == ticket.get(pid) && i < pid))) {
                      Thread.yield();
                    }
        }
    }
    // The critical section goes here...
}

public void unlock(int pid) {
  ticket.set(pid, 0);
}
```

## Bounded timestamps

Unfortunately, the bakery algorithm requires that timestamps never
overflow, and are totally ordered. Of course, that's not feasible, since
a counter might overflow a 64-bit int, for example.

Prev: [introduction](books/the-art-of-multiprocessor-programming/introduction.md)
Next: [concurrent-objects](concurrent-objects.md)
