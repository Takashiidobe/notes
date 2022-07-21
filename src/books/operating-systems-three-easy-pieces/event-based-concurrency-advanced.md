---
title: event-based-concurrency-advanced
---

# Event-based Concurrency (Advanced)

Prev:
[common-concurrency-problems](common-concurrency-problems.md)
Next:
[summary-dialogue-on-concurrency](summary-dialogue-on-concurrency.md)

Using threads for concurrency is difficult. Some other ways of having
concurrency are outlined below:

## The Basic Idea: An Event Loop

An event loop is pretty straightforward. It takes events from a queue,
and then processes them in a loop:

```c
while (1) {
  events = getEvents();
  for (e in events) { processEvent(e); }
}
```

This works well for a single-threaded environment, and greatly
simplifies programming (no more threads).

## An Important API: select() (or poll())

To build an event loop, `select()` or `poll()` can be used. Select looks
like this, where a set of file descriptors can be checked if they are
ready to read/write/error to in the future.

```c
int select(int nfds,
fd_set *restrict readfds,
fd_set *restrict writefds,
fd_set *restrict errorfds,
struct timeval *restrict timeout);
```

## Using select()

Some example code using select follows:

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
  // open and set up a bunch of sockets (not shown)
  // main loop
  while (1) {
    // initialize the fd_set to all zero
    fd_set readFDs;
    FD_ZERO(&readFDs);

    // now set the bits for the descriptors
    // this server is interested in
    // (for simplicity, all of them from min to max)
    int fd;
    for (fd = minFD; fd < maxFD; fd++)
      FD_SET(fd, &readFDs);

    // do the select
    int rc = select(maxFD + 1, &readFDs, NULL, NULL, NULL);

    // check which actually have data using FD_ISSET()
    int fd;
    for (fd = minFD; fd < maxFD; fd++)
      if (FD_ISSET(fd, &readFDs))
        processFD(fd);
  }
}
```

## A Problem: Blocking System Calls

Unfortunately, event based systems don't work well on systems with
synchronous I/O (all reads and writes would be blocking, which wouldn't
perform well).

## A Solution: Asynchronous I/O

For this, there's an Asynchronous I/O system call, like AIO.

The caller fills out the `aiocb` struct:

```c
struct aiocb {
  int aio_fildes; // File descriptor
  off_t aio_offset; // File offset
  volatile void *aio_buf; // Location of buffer
  size_t aio_nbytes; // Length of transfer
};
```

And calls `aio_read(struct aiocb *aiocbp);`

Which issues the I/O, which returns right away if successful and does
I/O in the background.

The system can then poll the struct with `int aio_error(const struct
aiocb *aiocbp)`.

Polling is difficult and ill performant, so some APIs use unix
signals to inform applications when asynchronous I/O completes.

## Another Problem: State Management

State management is also more difficult, since state needs to be
preserved (not on the stack) to handle the completed task.

This can be done with a continuation, where the state after the aio
request is issued is saved and read back from later on.

## What is Still Difficult With Events

An event-based approach doesn't solve all problems -- paging and
especially page-faulting still causes blocking, and it can be hard to
maintain an event-based system, since asynchronous and synchronous APIs
must be supported.

Prev:
[common-concurrency-problems](common-concurrency-problems.md)
Next:
[summary-dialogue-on-concurrency](summary-dialogue-on-concurrency.md)
