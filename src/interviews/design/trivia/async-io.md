# Async I/O in Linux

## Synchronous I/O

`write()`, `read()`, and the like are synchronous. You issue a write or read, the process stops, context switches to the kernel, the kernel fulfills the request, and the action is done. This is slow because other actions could occur during the I/O, but don't. We need async.

## Select

Select is a unix supported way to deliver descriptors to the kernel. You provide a list of file descriptors you care about, and then pass a bitset of read/write/exceptions, where you want events about that type on the fd to propagate back to you.

## Epoll

Epoll is linux's way to check if file descriptors have seen an interesting event.

You can `epoll_create` to tell the kernel to epoll.
Then, `epoll_ctl` with a list of file descriptors to tell the kernel what you care about
And `epoll_wait` for updates about the list of files.

## AIO

Linux I/O is supported in 2.6, but only works for O_DIRECT files, and it is troublesome to use.

(O_DIRECT means to pass the kernel's cache). This is useful for databases, because they maintain their own caches, but useless for everyone else, and it is frequently blocking.

## Io_uring

Io_uring consists of two queues - a submission queue and a completion queue.

The user submits requests to the head of the submission queue, and the kernel starts processing requests from the tail of the submission queue, doing the action, and then placing the result on the completion queue at the tail, which the user can read from the head of the completion queue.

This allows for batched I/O, and the kernel to run batched requests, which can lead to performance gains (2x faster than the usual sync calls, and 4x faster than thread pools), a bit faster than AIO, but less clunky, and supporting lots of system calls.

## Flaws

Epoll, Select, and AIO all have flaws that make them hard to use.

Select, poll, and epoll require iterating over all the passed file descriptors, state, and register callbacks, which is slow. At 100 or so fds, this is a huge bottleneck and starts to degrade performance. This can cause polynomial degradation of performance for the calls, so use io_uring or some other thing by that point.
