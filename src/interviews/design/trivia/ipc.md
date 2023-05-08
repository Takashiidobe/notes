# What are some common ways to do IPC?

## Signals

You can send signals to processes. Generally parents send signals to their children.

## Pipes

Pipes are used to redirect input and output from the shell to each other. This is done by creating two file data structures at the same VFS inode that point to a physical page in memory. One file can write, and the other can read.

The OS handles synchronization, by making sure that when a write is processed, the read also gets consumed from the file.

On writes, the process acquires the lock and gets to write to the page in memory. On reads, the process consumes bytes until it finishes, in which case it is put to sleep until signaled that there is more data (normally after the writer finishes writing).

## Sockets

Sockets allow for IPC as well. `socketpair` can be passed `AF_UNIX` for IPC or `AF_INET` for Internet protocol sockets, and then either `SOCK_STREAM` or `SOCK_DGRAM` for TCP or UDP style communication, and an array of ints to hold the socket fds.

## System V Mechanisms

### Message Queues

Message queues allow one or more processes to write messages, which will be read by one or more reading processes.

### Semaphores

Semaphores allow processes to signal between processes to operate on shared memory (like a file).

### Shared Memory

Processes can use shared memory and then read/write to those areas.
