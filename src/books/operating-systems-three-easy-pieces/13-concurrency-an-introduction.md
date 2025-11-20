---
title: concurrency-an-introduction
---
# Concurrency: An Introduction

Prev: [[12-a-dialogue-on-concurrency]]
Next: [[14-interlude-thread-api]]





Here we introduce threads, which are like processes, but with shared
memory -- therefore they need coordination.

The state of a thread is like a process -- if one thread has to be
context switched, its state is saved to a thread control block.

As well, each process now could have multiple stacks (a thread might
take 2KB or so), which could increase fragmentation.

## Why Use Threads?

Parallelism -- if the work a program does can be chopped into smaller
pieces that can make progress independently, a program would run faster
with threads.

As well, threading removes most of the penalty of slow operations --
while one thread is blocked on an I/O request, another thread can make
progress.

## An Example: Thread Creation:

```c
#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include "common.h"
#include "common_threads.h"

void *mythread(void *arg) {
  printf("%s\n", (char *) arg);
  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t p1, p2;
  int rc;
  printf("main: begin\n");
  Pthread_create(&p1, NULL, mythread, "A");
  Pthread_create(&p2, NULL, mythread, "B");
  // join waits for the threads to finish
  Pthread_join(p1, NULL);
  Pthread_join(p2, NULL);
  printf("main: end\n");
  return 0;
}
```

Take this example, creating two threads that print the name of the
thread, and then joining them. A or B could print in any order, because
either A or B prints first. This is all left to the scheduler's whims.

## Why It Gets Worse: Shared Data

```c
#include <stdio.h>
#include <pthread.h>
#include "common.h"
#include "common_threads.h"

static volatile int counter = 0;

// mythread()
//
// Simply adds 1 to counter repeatedly, in a loop
// No, this is not how you would add 10,000,000 to
// a counter, but it shows the problem nicely.
//
void *mythread(void *arg) {
  printf("%s: begin\n", (char *) arg);
  int i;
  for (i = 0; i < 1e7; i++) {
  counter = counter + 1;
  }
  printf("%s: done\n", (char *) arg);
  return NULL;
}

// main()
//
// Just launches two threads (pthread_create)
// and then waits for them (pthread_join)
//
int main(int argc, char *argv[]) {
  pthread_t p1, p2;
  printf("main: begin (counter = %d)\n", counter);
  Pthread_create(&p1, NULL, mythread, "A");
  Pthread_create(&p2, NULL, mythread, "B");

  // join waits for the threads to finish
  Pthread_join(p1, NULL);
  Pthread_join(p2, NULL);
  printf("main: done with both (counter = %d)\n",
  counter);
  return 0;
}
```

This code should count to 2 million, but if ran, it might not get there:

```c
prompt> ./main
main: begin (counter = 0)
A: begin
B: begin
A: done
B: done
main: done with both (counter = 19345221)
```

Luckily, C11 now supports atomic registers -- by declaring a type as
atomic, it will work properly.

```c
static atomic int c = 0;
```

## The Heart Of the Problem: Uncontrolled Scheduling

When we're incrementing the counter, something like this assembly is
emitted:

```asm
mov 0x8049a1c, %eax
add $0x1, %eax
mov %eax, 0x8049a1c
```

This takes three instructions, instead of the one we'd like, so threads
can be interrupted in the process of reading the register and adding,
causing data races.

We want mutual exclusion, where only one thread can read and increment
the value.

## The Wish For Atomicity

We really want the ability to execute those instructions at once. Some
instructions like compare and swap are provided by the hardware and
allow for this.

## One More Problem: Waiting For Another

What happens if a thread is put to sleep as its I/O request succeeds? It
needs to wake -- something we'll cover in another chapter on Condition
Variables.

Prev: [[12-a-dialogue-on-concurrency]]
Next: [[14-interlude-thread-api]]
