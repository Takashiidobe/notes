---
title: condition-variables
---
# Condition Variables

Prev: [[16-lock-based-concurrent-data-structures]]
Next: [[18-semaphores]]





Condition variables are for cases where a thread needs to check that a
certain condition has been met before continuing.

Imagine a parent, which spawns a child thread. The parent needs to wait
for the child thread to finish, but obviously wouldn't want to
spin-lock.

The spin-lock version is inefficient:

```c
volatile int done = 0;

void *child(void *arg) {
  printf("child\n");
  done = 1;
  return NULL;
}

int main(int argc, char *argv[]) {
  printf("parent: begin\n");
  pthread_t c;
  Pthread_create(&c, NULL, child, NULL); // create child
  while (done == 0)
    ; // spin
  printf("parent: end\n");
  return 0;
}
```

We use condition variables, where a thread sleeps (uses no CPU) until
another thread signals the desired condition and wakes the thread (like
park/unpark and futex).

```c
int done = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

void thr_exit() {
  Pthread_mutex_lock(&m);
  done = 1;
  Pthread_cond_signal(&c);
  Pthread_mutex_unlock(&m);
}

void *child(void *arg) {
  printf("child\n");
  thr_exit();
  return NULL;
}

void thr_join() {
  Pthread_mutex_lock(&m);
  while (done == 0)
    Pthread_cond_wait(&c, &m);
  Pthread_mutex_unlock(&m);
}

int main(int argc, char *argv[]) {
  printf("parent: begin\n");
  pthread_t p;
  Pthread_create(&p, NULL, child, NULL);
  thr_join();
  printf("parent: end\n");
  return 0;
}
```

The POSIX calls look like so:

```c
pthread_cond_wait(pthread_cond_t *c, pthread_mutex_t *m);
pthread_cond_signal(pthread_cond_t *c);
```

CondVars require a mutex, condition var to signal, and a variable to
mutate.

## The Producer/Consumer (Bounded Buffer) Problem

The Producer Consumer problem arises when producers produce data into
some shared data structure and consumers read from it concurrently.

Take an example like so:

```c
int buffer;
int count = 0; // initially, empty

void put(int value) {
  assert(count == 0);
  count = 1;
  buffer = value;
}

int get() {
  assert(count == 1);
  count = 0;
  return buffer;
}
```

```c
void producer(void *arg) {
  int i;
  int loops = (int)arg;
  for (i = 0; i < loops; i++) {
    put(i);
  }
}

void consumer(void *arg) {
  while (1) {
    int tmp = get();
    printf("%d\n", tmp);
  }
}
```

One broken approach might look like this:

```c
int loops; // must initialize somewhere...
cond_t cond;
mutex_t mutex;

void *producer(void *arg) {
  int i;
  for (i = 0; i < loops; i++) {
    Pthread_mutex_lock(&mutex);         // p1
    if (count == 1)                     // p2
      Pthread_cond_wait(&cond, &mutex); // p3
    put(i);                             // p4
    Pthread_cond_signal(&cond);         // p5
    Pthread_mutex_unlock(&mutex);       // p6
  }
}

void *consumer(void *arg) {
  int i;
  for (i = 0; i < loops; i++) {
    Pthread_mutex_lock(&mutex);         // c1
    if (count == 0)                     // c2
      Pthread_cond_wait(&cond, &mutex); // c3
    int tmp = get();                    // c4
    Pthread_cond_signal(&cond);         // c5
    Pthread_mutex_unlock(&mutex);       // c6
    printf("%d\n", tmp);
  }
}
```

This unfortunately only works for a single consumer and producer. If a
consumer comes first, goes to sleep, then a producer puts data on the
buffer, and signals to the first thread, another thread could come in
its place and process the buffer.

This is because signals have `Mesa Semantics`, where a woken thread is
not guaranteed to be the next thread that runs.

`Hoare Semantics` would guarantee this, but these semantics are rare.

This can be fixed by using a `while` loop instead of an if conditional.

```c
int loops;
cond_t cond;
mutex_t mutex;

void producer(void *arg) {
  int i;
  for (i = 0; i < loops; i++) {
    Pthread_mutex_lock(&mutex);         // p1
    while (count == 1)                  // p2
      Pthread_cond_wait(&cond, &mutex); // p3
    put(i);                             // p4
    Pthread_cond_signal(&cond);         // p5
    Pthread_mutex_unlock(&mutex);       // p6
  }
}

void consumer(void *arg) {
  int i;
  for (i = 0; i < loops; i++) {
    Pthread_mutex_lock(&mutex);         // c1
    while (count == 0)                  // c2
      Pthread_cond_wait(&cond, &mutex); // c3
    int tmp = get();                    // c4
    Pthread_cond_signal(&cond);         // c5
    Pthread_mutex_unlock(&mutex);       // c6
    printf("%d\n", tmp);
  }
}
```

This, however, leads to deadlock, as none of the threads can make
progress.

To solve this problem, we use two condvars, one for producers and one
for consumers.

```c
int buffer[MAX];
int fill_ptr = 0;
int use_ptr = 0;
int count = 0;

void put(int value) {
  buffer[fill_ptr] = value;
  fill_ptr = (fill_ptr + 1) % MAX;
  count++;
}

int get() {
  int tmp = buffer[use_ptr];
  use_ptr = (use_ptr + 1) % MAX;
  count--;
  return tmp;
}
```

```c
cond_t empty, fill;
mutex_t mutex;

void *producer(void *arg) {
  int i;
  for (i = 0; i < loops; i++) {
    Pthread_mutex_lock(&mutex);          // p1
    while (count == MAX)                 // p2
      Pthread_cond_wait(&empty, &mutex); // p3
    put(i);                              // p4
    Pthread_cond_signal(&fill);          // p5
    Pthread_mutex_unlock(&mutex);        // p6
  }
}

void *consumer(void *arg) {
  int i;
  for (i = 0; i < loops; i++) {
    Pthread_mutex_lock(&mutex);         // c1
    while (count == 0)                  // c2
      Pthread_cond_wait(&fill, &mutex); // c3
    int tmp = get();                    // c4
    Pthread_cond_signal(&empty);        // c5
    Pthread_mutex_unlock(&mutex);       // c6
    printf("%d\n", tmp);
  }
}
```

## Covering Conditions

There is one more use for condvars, where a producer wants to broadcast
to all consumers.

Imagine a situation where one thread calls `malloc(100)` and another
thread calls `malloc(10)` and both go to sleep, because there is not
enough memory. Next, a call to `free(50)` comes back, but it doesn't
know which threads to wake up (if it wakes up the thread calling for
`malloc(100)`, it goes back to sleep).

To solve this problem, the code will instead call
`pthread_cond_broadcast()`, which wakes up all waiting threads. This
guarantees that the resource at hand (bytes from the allocator) is used
efficiently, even if waking up threads may be inefficient sometimes.

Prev: [[16-lock-based-concurrent-data-structures]]
Next: [[18-semaphores]]
