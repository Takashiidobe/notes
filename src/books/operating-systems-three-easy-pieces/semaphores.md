---
title: semaphores
---

# Semaphores

Prev:
[condition-variables](condition-variables.md)
Next:
[common-concurrency-problems](common-concurrency-problems.md)

## Semaphores: A Definition

Semaphores are a generic synchronization primitive that can be used as
locks and condition variables.

POSIX has semaphores in the standard in `semaphore.h`.

```c
#include <semaphore.h>
sem_t s;
sem_init(&s, 0, 1);
```

Semaphores are initialized with `sem_init`, which takes a semaphore, an
enum which indicates if the semaphore is shared between threads in the
same process, and the count, which is `1`.

Wait and post are defined like so:

`sem_wait` decrements the value of the semaphore by one. If it is still
positive, it returns there. If not, it tells the calling thread to sleep.

`sem_post` increments the value of the semaphore by one. If one or more
thread is waiting, it wakes up one of them.

```c
int sem_wait(sem_t *s) {
  // decrement the value of semaphore s by one
  // wait if value of semaphore s is negative
}

int sem_post(sem_t *s) {
  // increment the value of semaphore s by one
  // if there are one or more threads waiting, wake one
}
```

## Binary Semaphores (Locks)

Semaphores set to a value of `1` are basically mutexes, but less
efficient (due to having to signal).

## Semaphores for Ordering

To emulate a condition variable, Semaphores can also be used, but with
their value set to `0`.

```c
sem_t s;

void *child(void *arg) {
  printf("child\n");
  sem_post(&s); // signal here: child is done
  return NULL;
}

int main(int argc, char *argv[]) {
  sem_init(&s, 0, 0);
  printf("parent: begin\n");
  pthread_t c;
  Pthread_create(&c, NULL, child, NULL);
  sem_wait(&s); // wait here for child
  printf("parent: end\n");
  return 0;
}
```

This means that the semaphore starts at 0, and then the parent does what
it needs to, decrements the semaphore, and is put to sleep. Then the
child will post, which wakes the parent.

## The Producer/Consumer (Bounded Buffer) Problem

This can be solved with a 2 semaphores and a mutex. The semaphores
signal for empty and full, and the mutex is used to guard the critical
section.

```c
void *producer(void *arg) {
  int i;
  for (i = 0; i < loops; i++) {
    sem_wait(&empty); // Line P1
    sem_wait(&mutex); // Line P1.5 (MUTEX HERE)
    put(i);           // Line P2
    sem_post(&mutex); // Line P2.5 (AND HERE)
    sem_post(&full);  // Line P3
  }
}

void *consumer(void *arg) {
  int i;
  for (i = 0; i < loops; i++) {
    sem_wait(&full);  // Line C1
    sem_wait(&mutex); // Line C1.5 (MUTEX HERE)
    int tmp = get();  // Line C2
    sem_post(&mutex); // Line C2.5 (AND HERE)
    sem_post(&empty); // Line C3
    printf("%d\n", tmp);
  }
}
```

## Reader-Writer Locks

A Common pattern that occurs is for locking on writers, but not on
readers, due to writers mutating data and readers not requiring a lock.

To do this, we use semaphores -- one that indicates if it is safe to
write, and another for the critical section.

```c
typedef struct _rwlock_t {
  sem_t lock;      // binary semaphore (basic lock)
  sem_t writelock; // allow ONE writer/MANY readers
  int readers;     // #readers in critical section
} rwlock_t;

void rwlock_init(rwlock_t *rw) {
  rw->readers = 0;
  sem_init(&rw->lock, 0, 1);
  sem_init(&rw->writelock, 0, 1);
}

void rwlock_acquire_readlock(rwlock_t *rw) {
  sem_wait(&rw->lock);
  rw->readers++;
  if (rw->readers == 1) // first reader gets writelock
    sem_wait(&rw->writelock);
  sem_post(&rw->lock);
}

void rwlock_release_readlock(rwlock_t *rw) {
  sem_wait(&rw->lock);
  rw->readers--;
  if (rw->readers == 0) // last reader lets it go
    sem_post(&rw->writelock);
  sem_post(&rw->lock);
}

void rwlock_acquire_writelock(rwlock_t *rw) { sem_wait(&rw->writelock); }

void rwlock_release_writelock(rwlock_t *rw) { sem_post(&rw->writelock); }
```

## The Dining Philosophers

The Dining philosophers problem has five philosophers at a table, who
need to grab two forks next to them to eat. They think, grab forks, eat,
then put their forks down. The challenge is to make sure that there is
no deadlock, no philosopher starves, and throughput is high.

A broken solution involves locking the forks, where each philosopher
grabs the fork to their left and then their right. If each philosopher
grabs the fork to their left, then tries to grab the fork to their
right, they enter deadlock, since no one can make progress.

Dijkstra's solution is fairly simple. Make one of the philosophers
right-handed -- they grab a different fork, so they break the cycle of
deadlock. Another way is cooperative -- a philosopher who grabbed a fork
may put it down. To ensure fairness, there might be an epoch counter and
the philosophers who put down the fork in one round might not in the
next round.

## Thread Throttling

Semaphores are also useful for throttling -- each thread that wants to
do computation calls the semaphore. This is good for rate limiting (no
more than X threads can be in the critical section at once).

## How to Implement Semaphores

Semaphores can be implemented using condition variables and locks:

```c
typedef struct __Zem_t {
  int value;
  pthread_cond_t cond;
  pthread_mutex_t lock;
} Zem_t;

// only one thread can call this
void Zem_init(Zem_t *s, int value) {
  s->value = value;
  Cond_init(&s->cond);
  Mutex_init(&s->lock);
}

void Zem_wait(Zem_t *s) {
  Mutex_lock(&s->lock);
  while (s->value <= 0)
    Cond_wait(&s->cond, &s->lock);
  s->value--;
  Mutex_unlock(&s->lock);
}

void Zem_post(Zem_t *s) {
  Mutex_lock(&s->lock);
  s->value++;
  Cond_signal(&s->cond);
  Mutex_unlock(&s->lock);
}
```

Prev:
[condition-variables](condition-variables.md)
Next:
[common-concurrency-problems](common-concurrency-problems.md)
