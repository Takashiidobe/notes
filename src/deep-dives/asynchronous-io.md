# Asynchronous I/O

Linux supports synchronous and asynchronous I/O, with both
readiness-based (select/poll, epoll) and completion based io_uring.

The usual unix calls (read, write) are synchronous, and block the
current thread until completion.

Asynchronous I/O allows for work to continue while I/O is occurring.

The first asynchronous strategy, with readiness was select/poll. They
both allow submission of a list of file descriptors, and when one is
ready, the kernel returns, where you must scan the list of file
descriptors for work to do.

epoll does this in O(1), where the kernel keeps track of which fds are
ready, and notifies the user.

io_uring supports a completion based model for all I/O. There are a pair
of ring buffers (submission + completion). An application can queue
operations by filling out submission entries and then read completions
from the completion ring. These queues are memory-mapped into the
application's memory.

As well, readiness based completion models are generally combined with
synchronous system calls, like read/write. In io_uring, the kernel does
the operation asynchronously as well, which means there's no blocking
for the application thread.

Operations that are supported by the io_uring subsystem are provided as
opcodes to the submission queue, and checked for completion in the
completion queue.

This would look like this (taken from tokio.rs/io_uring's readme)

```rust
let mut ring = IoUring::new(8)?;

let fd = fs::File::open("README.md")?;
let mut buf = vec![0; 1024];

let read_e = opcode::Read::new(types::Fd(fd.as_raw_fd()), buf.as_mut_ptr(), buf.len() as _)
    .build()
    .user_data(0x42);

// Note that the developer needs to ensure
// that the entry pushed into submission queue is valid (e.g. fd, buffer).
unsafe {
    ring.submission()
        .push(&read_e)
        .expect("submission queue is full");
}

ring.submit_and_wait(1)?;

let cqe = ring.completion().next().expect("completion queue is empty");

assert_eq!(cqe.user_data(), 0x42);
assert!(cqe.result() >= 0, "read error: {}", cqe.result());
```
