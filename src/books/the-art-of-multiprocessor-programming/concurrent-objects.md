---
title: "Concurrent Objects"
---

# Concurrent Objects

Prev: [mutual-exclusion](mutual-exclusion.md)
Next: [foundations-of-shared-memory](foundations-of-shared-memory.md)

## Concurrency and correctness

To learn more about correctness, lets start off with a lock based queue
which acquires a lock:

```java
class LockBasedQueue<T> {
  int head, tail;
  T[] items;
  public LockBasedQueue(int capacity) {
    head = 0; tail = 0;
    items = (T[]) new Object[capacity];
  }

  public synchronized void enq(T x) throws FullException {
    if (tail - head == items.length) {
      throw new FullException();
    }
    items[tail % items.length] = x;
    tail++;
  }

  public synchronized T deq() throws EmptyException {
    if (tail == head) {
      throw new EmptyException();
    }
    T x = items[head % items.length];
    head++;
    return x;
  }
}
```

Since both `enq` and `deq` are synchronized, all calls to the queue must
operate sequentially, and is this correct.

However, since both `enq` and `deq` use the same lock, this is not that
performant. A better implementation would use fewer locks.

To do so, imagine a non-synchronized queue (Wait Free):

Since there is no need for the lock to coordinate access, this is still
*correct*, but only if there is one enqueuer or dequeuer.

```java
class LockBasedQueue<T> {
  int head, tail;
  T[] items;
  public LockBasedQueue(int capacity) {
    head = 0; tail = 0;
    items = (T[]) new Object[capacity];
  }

  public void enq(T x) throws FullException {
    if (tail - head == items.length) {
      throw new FullException();
    }
    items[tail % items.length] = x;
    tail++;
  }

  public T deq() throws EmptyException {
    if (tail == head) {
      throw new EmptyException();
    }
    T x = items[head % items.length];
    head++;
    return x;
  }
}
```

## Sequential objects

In an object used sequentially, it can be described with a
**precondition** and a **postcondition**, where the object that is in X
state is mutated to one in Y state after a certain method call.

In a multi-threaded world, however, there are no certain **pre** and
**post** conditions -- an object may always have an in-progress call.

## Sequential Consistency

We can try to look at concurrent objects the same way we look at
sequential objects. To do this, split up a concurrent call into two
parts, its **invocation** and its **response**. A method that has been
called on a concurrent object but has not returned is considered
**pending**.

To make concurrent objects easy to understand, method calls should be:

1. Appear to happen one-at-a-time in sequential order.
2. Executed in First-Come-First-Served order.
3. Method calls should appear to take effect in program order.

These constraints define **sequential consistency**, which is easier to
understand.

### Sequential consistency versus real-time order

Imagine the case where thread A enqueues X, later on thread B enqueues
y, and A dequeues y. This is inconsistent with the real-time order (X
should be dequeued), but it doesn't always occur.

### Sequential consistency is nonblocking

To be sequentially consistent, an object must immediately respond to an
invocation, otherwise it blocks other objects.

### Compositionality

Unfortunately, sequential consistency is not compositional. If you have
two concurrent queues, is the system (both queues) concurrent? No.

## Linearizability

Since sequential consistency is not compositional, we need a stronger
constraint:

- Each method call should appear to take effect instantaneously at some
  moment between its invocation and response.

This elevates sequential consistency to linearizability.

### Linearization points

If a method mutates state at one point, that is called its
**linearization point**.

### Linearizability versus sequential consistency

Linearizability is nonblocking, but compositional. It's thus better for
describing larger systems.

## Quiescent Consistency

To trade off consistency for performance, there's also quiescent
consistency. If an object has no pending method calls, it can be totally
ordered, otherwise, there is no guarantee that method calls take effect
in their real-time order.

## Memory consistency models

Code can be affected by the memory consistency models of the hardware
and language. Java and C++ have a memory order on architectures they run
on, which provide keywords to prohibit reordering of operations by
compilers and hardware.

## Progress conditions

### Wait-freedom

A method is **wait-free** if every call finishes its execution in a
finite number of steps. A lock based queue is not wait-free because
enqueueing or dequeuing could be infinitely blocked by the other
operation.

### Lock-freedom

A weaker progress condition is **lock-freedom**, where at least some
threads terminate in a finite number of steps.

### Obstruction-freedom

A method is obstruction free if no other thread obstructs it -- i.e. it
finishes in a bounded number of steps if no other threads block it.

### Blocking progress conditions

A method is **starvation-free** if it completes in a finite number of
steps provided that every thread with a pending method call keeps taking
steps.

### Characterizing progress conditions

|                  | Independent, Nonblocking | dependent, nonblocking | dependent, blocking |
|------------------|--------------------------|------------------------|---------------------|
| maximal progress | Wait-free                | Obstruction-free       | Starvation-free     |
| minimal progress | Lock-free                |                        | Deadlock-free       |

Prev: [mutual-exclusion](mutual-exclusion.md)
Next: [foundations-of-shared-memory](foundations-of-shared-memory.md)
