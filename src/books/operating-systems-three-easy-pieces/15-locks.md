---
title: locks
---
# Locks

Prev: [[14-interlude-thread-api]]
Next: [[16-lock-based-concurrent-data-structures]]





## Locks: The Basic Idea

Locks are meant to prevent multiple threads from updating the same
variable:

```c
lock_t mutex; // some globally-allocated lock ’mutex’
lock(&mutex);
balance = balance + 1;
unlock(&mutex);
```

## Pthread locks

The most common locks API is the POSIX threads library (Pthreads).

The previous example would look like this:

```c
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
Pthread_mutex_lock(&lock); // wrapper; exits on failure
balance = balance + 1;
Pthread_mutex_unlock(&lock);
```

## Building a Lock

To build a lock, we'll need some hardware support

## Evaluating Locks

Locks must provide the following:

1. Mutual Exclusion
2. Fairness (does no lock *starve*?)
3. Performance (it should not cost much)

## Controlling Interrupts

To provide mutual exclusion, the OS can't interrupt a thread while it is
in a critical section. One solution is to disable interrupts while
locking:

```c
void lock() { DisableInterrupts(); }

void unlock() { EnableInterrupts(); }
```

This doesn't work:

1. Is a privileged operation, which applications will abuse
2. If an application is coded improperly, the OS will starve
3. Misses interrupts if locking for too long
4. Slow performance

## A Failed Attempt: Just Using Loads/Stores

Another attempt would look like this:

```c
typedef struct __lock_t { int flag; } lock_t;

void init(lock_t *mutex) {
  // 0 -> lock is available, 1 -> held
  mutex->flag = 0;
}

void lock(lock_t *mutex) {
  while (mutex->flag == 1) // TEST the flag
    ; // spin-wait (do nothing)
  mutex->flag = 1; // now SET it!
}

void unlock(lock_t *mutex) {
  mutex->flag = 0;
}
```

This is neither efficient nor correct:

With this interleaving, two threads could enter the critical section:

| Thread 1                | Thread 2                |
|-------------------------|-------------------------|
| call lock()             |                         |
| while (flag == 1)       |                         |
| Interrupt: switch to T2 |                         |
|                         | call lock()             |
|                         | while (flag == 1)       |
|                         | flag = 1;               |
|                         | interrupt: switch to T1 |
| flag = 1;               |                         |

The correctness is because a while loop is a spin-lock, which is
inefficient (it waits forever on its slice, when it should be sleeping
and only wake when something changes).

## Building Working Spin Locks with Test-And-Set

The simplest hardware support to build locks uses `test-and-set` or
`atomic-exchange`:

```c
int TestAndSet(int *old_ptr, int new) {
  int old = *old_ptr; // fetch old value at old_ptr
  *old_ptr = new; // store ’new’ into old_ptr
  return old; // return the old value
}
```

As well, there's Dekker's and Peterson's algorithms to create a lock
without hardware support:

```c
int flag[2];
int turn;
void init() {
  // indicate you intend to hold the lock w/ ’flag’
  flag[0] = flag[1] = 0;
  // whose turn is it? (thread 0 or 1)
  turn = 0;
}
void lock() {
  // ’self’ is the thread ID of caller
  flag[self] = 1;
  // make it other thread’s turn
  turn = 1 - self;
  while ((flag[1-self] == 1) && (turn == 1 - self))
    ; // spin-wait while it’s not your turn
}
void unlock() {
  // simply undo your intent
  flag[self] = 0;
}
```

We can use Test-and-set for a simple spin lock:

```c
typedef struct __lock_t {
  int flag;
} lock_t;

void init(lock_t *lock) {
  // 0: lock is available, 1: lock is held
  lock->flag = 0;
}

void lock(lock_t *lock) {
  while (TestAndSet(&lock->flag, 1) == 1)
    ; // spin-wait (do nothing)
}

void unlock(lock_t *lock) {
  lock->flag = 0;
}
```

## Evaluating Spin Locks

To evaluate our lock, assess its correctness, fairness, and performance

1. correctness: provides mutual exclusion
2. fairness: spin locks are not fair and not starvation-free
3. performance: extremely inefficient

This approach isn't terrible for multi-processors, though.

## Compare-And-Swap

`compare-and-swap` or `compare-and-exchange` allows us to build a lock
too:

```c
void lock(lock_t *lock) {
  while (CompareAndSwap(&lock->flag, 0, 1) == 1)
    ; // spin
}
```

## Load-Linked and Store-Conditional

Some platforms provide a pair of instructions for synchronization,
instead of just one (like test-and-set or compare-and-swap).

Alpha, PowerPC, and ARM use LL and SC. A Load-linked instruction is like
a load instruction, but a Store-Conditional instruction only succeeds if
no store has taken place to the address in the LL.

This can create a lock like so:

```c
void lock(lock_t *lock) {
  while (LoadLinked(&lock->flag) || !StoreConditional(&lock->flag, 1))
    ; // spin
}
```

## Fetch-And-Add

The final hardware primitive is `fetch-and-add`, which atomically
increments a value, and returns its old value:

```c
int FetchAndAdd(int *ptr) {
  int old = *ptr;
  *ptr = old + 1;
  return old;
}
```

This allows us to build a ticket lock, which is a starvation-free lock.

## Too Much Spinning: What Now?

A ticket lock would look like this: the first thread gets its turn,
enters the critical section, then the next, and so forth. This is now
starvation-free, but still inefficient (it spin-waits too much).

```c
typedef struct __lock_t {
  int ticket;
  int turn;
} lock_t;

void lock_init(lock_t *lock) {
  lock->ticket = 0;
  lock->turn = 0;
}

void lock(lock_t *lock) {
  int myturn = FetchAndAdd(&lock->ticket);
  while (lock->turn != myturn)
    ; // spin
}

void unlock(lock_t *lock) {
  lock->turn = lock->turn + 1;
}
```

## A Simple Approach: Just Yield, Baby

We need OS support for another system call: yielding. This allows for a
cooperative approach: any thread that finds it is locked out will yield
to the OS, allowing other threads to make progress.

However there's no starvation-freedom, and still inefficiencies to prune.

```c
void init() {
  flag = 0;
}
void lock() {
  while (TestAndSet(&flag, 1) == 1)
    yield(); // give up the CPU
}
void unlock() {
 flag = 0;
}
```

## Using Queues: Sleeping Instead of Spinning

It's possible to avoid all the pitfalls previously by adding two system
calls: `park()`, which puts a calling thread to sleep, and
`unpark(threadID)`, which wakes the thread provided. This allows a lock
that puts a caller to sleep if it tries to acquire a held lock and wakes
when the lock is free.

```c
typedef struct __lock_t {
  int flag;
  int guard;
  queue_t *q;
} lock_t;

void lock_init(lock_t *m) {
  m->flag = 0;
  m->guard = 0;
  queue_init(m->q);
}

void lock(lock_t *m) {
  while (TestAndSet(&m->guard, 1) == 1)
    ; // acquire guard lock by spinning
  if (m->flag == 0) {
    m->flag = 1; // lock is acquired
    m->guard = 0;
  } else {
    queue_add(m->q, gettid());
    m->guard = 0;
    park();
  }
}

void unlock(lock_t *m) {
  while (TestAndSet(&m->guard, 1) == 1)
    ; // acquire guard lock by spinning
  if (queue_empty(m->q))
    m->flag = 0; // let go of lock; no one wants it
  else
    unpark(queue_remove(m->q)); // hold lock
  // (for next thread!)
  m->guard = 0;
}
```

## Different OS, Different Support

Linux provides `futex`, which is like `un/park`. `futex_wait(address,
expected)` puts the calling thread to sleep if the address == expected.
If not, it returns. `futex_wake(address)` wakes one thread that is
waiting on the queue.

## Two-Phase Locks

A Two-phase lock spins once, trying to acquire the lock. If it does not,
it enters a sleep, where it is woken up when the lock becomes free
later.

Prev: [[14-interlude-thread-api]]
Next: [[16-lock-based-concurrent-data-structures]]
