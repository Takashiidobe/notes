---
title: interlude-thread-api
---

: Thread API"

# Interlude: Thread API

Prev:
[concurrency-an-introduction](concurrency-an-introduction.md)
Next: [locks](locks.md)

## Thread Creation

The thread creation API in POSIX is easy:

```c
#include <pthread.h>
int pthread_create(pthread_t *thread,
                   const pthread_attr_t *attr,
                   void *(*start_routine)(void *), void *arg);
                   Creates a new thread of execution.
```

There are four arguments:
1. a `thread`, a pointer to a `pthread_t` struct,
2. an `attr`, `const pthread_attr_t` struct, which specifies attributes
   to build the struct
3. a `void *` returning start routine that takes any argument
4. a `void *` argument, an argument to pass to the thread.

## Thread Completion

To wait for a thread to complete, you must call `pthread_join()`.

```c
int pthread_join(pthread_t, thread, void** value_ptr);
```

This returns 0 on success, or an error code.

For a full example of using a thread and joining it:

```c
typedef struct { int a; int b; } myarg_t;
typedef struct { int x; int y; } myret_t;

void *mythread(void *arg) {
  myret_t *rvals = Malloc(sizeof(myret_t));
  rvals->x = 1;
  rvals->y = 2;
  return (void *) rvals;
}

int main(int argc, char *argv[]) {
  pthread_t p;
  myret_t *rvals;
  myarg_t args = { 10, 20 };
  Pthread_create(&p, NULL, mythread, &args);
  Pthread_join(p, (void **) &rvals);
  printf("returned %d %d\n", rvals->x, rvals->y);
  free(rvals);
}
```

Make sure not to return a pointer to anything on the stack of the
thread:

```c
void *mythread(void *arg) {
  myarg_t *args = (myarg_t *) arg;
  printf("%d %d\n", args->a, args->b);
  myret_t oops; // ALLOCATED ON STACK: BAD!
  oops.x = 1;
  oops.y = 2;
  return (void *) &oops; // return freed memory
}
```

If you don't want to pass a single argument, you can pass one number as
an argument:

```c
void *mythread(void *arg) {
  long long int value = (long long int) arg;
  printf("%lld\n", value);
  return (void *) (value + 1);
}
int main(int argc, char *argv[]) {
  pthread_t p;
  long long int rvalue;
  Pthread_create(&p, NULL, mythread, (void *) 100);
  Pthread_join(p, (void **) &rvalue);
  printf("returned %lld\n", rvalue);
  return 0;
}
```

## Locks

Locks are created and locked and unlocked.

```c
int pthread_mutex_t lock;
int rc = pthread_mutex_init(&lock, NULL);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
```

To use a mutex, you'll want to guard the critical section:

```c
pthread_mutex_t lock;
int rc = pthread_mutex_init(&lock, NULL);
pthread_mutex_lock(&lock);
x = x + 1; // or whatever your critical section is
pthread_mutex_unlock(&lock);
```

There are two other interesting functions:

```c
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_timedlock(pthread_mutex_t *mutex,
struct timespec *abs_timeout);
```

The trylock returns a failure if the lock is already held;
the timedlock takes a timespec struct, and it returns a failure if it
can't get the lock in that time, otherwise it locks.

## Condition Variables

Condition variables are useful for signaling between threads without
busy-waiting:

The two main functions are:

```c
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
int pthread_cond_signal(pthread_cond_t *cond);
```

The first, puts the calling thread to sleep, and waits for another
thread to signal to it.

```c
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
Pthread_mutex_lock(&lock);
while (ready == 0)
Pthread_cond_wait(&cond, &lock);
Pthread_mutex_unlock(&lock);
```

The second function is used to signal to that thread.

```c
Pthread_mutex_lock(&lock);
ready = 1;
Pthread_cond_signal(&cond);
Pthread_mutex_unlock(&lock)
```

Prev:
[concurrency-an-introduction](concurrency-an-introduction.md)
Next: [locks](locks.md)
