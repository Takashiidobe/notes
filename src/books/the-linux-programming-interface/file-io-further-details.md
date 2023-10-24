---
title: file-io-further-details
---

# File I/O: Further Details

Prev: [file-io-the-universal-io-model](file-io-the-universal-io-model.md) Next: [processes](processes.md)

## Atomicity and Race Conditions

All system calls are executed atomically, so there are no conditions where a system call can interrupt another one.

### Creating a file exclusively

The `O_EXCL` flag passed to `open` can be used to guarantee exclusive creation of a file.

Without this flag it's not possible to guarantee exclusively opening a file, because it would take more than one syscall.

### Appending data to a file

Another use case (common in logging) is multiple processes appending data to the same file. Again, we require one syscall.

To do so, we can use `O_APPEND` to open the file exclusively in append mode.

## File Control Operations: `fcntl`

`fcntl` is used for control operations on an open file descriptor.

```c
#include <fcntl.h>
int fcntl(int fd, int cmd, ...); // Return on success depends on cmd, or -1 on error.
```

## Open File Status Flags

`fcntl` can be used to modify the access mode and open file status flags of a file.

To get them, pass `F_GETFL` to `fcntl`.

```c
int flags = fcntl(fd, F_GETFL);
```

And check the flags for synchronized writes:

```c
if (flags & O_SYNC)
```

Flags can be set using `F_SETFL`:

```c
int flags;
flags = fcntl(fd, F_GETFL);
flags |= O_APPEND; // add O_APPEND to the flags
fcntl(fd, F_SETFL, flags); // set the flags
```

## Relationship between File Descriptors and Open Files

Multiple file descriptors may refer to the same open file. They could be open in the same process or different processes.

## Duplicating File Descriptors

File descriptors can be duplicated using the `dup`, `dup2` system calls, which is what is done when piping at shell:

`$ ./myscript > results.log 2>&1`

`dup` looks like this: it returns a value that corresponds to the new file descriptor on success, which is the lowest unused file descriptor.

```c
#include <unistd.h>
int dup(int oldfd); // Returns (new) file descriptor on success, or –1 on error
```

But if you want to ensure the file descriptor has a specific number, use `dup2`:

```c
#include <unistd.h>
int dup2(int oldfd, int newfd); // Returns (new) file descriptor on success, or –1 on error
```

This closes the `newfd` if it exists, then returns the value again.

You can also use `fcntl`, which duplicates `oldfd`, and returning a value at least as large as `startfd`.

```c
int newfd = fcntl(oldfd, F_DUPED, startfd);
```

Another call, `dup3` also exists:

```c
#define _GNU_SOURCE
#include <unistd.h>
int dup3(int oldfd, int newfd, int flags); // Returns (new) file descriptor on success, or –1 on error
```

The supported flag is `O_CLOEXEC`, which allows the kernel to enable the close-on-exec flag for the new file descriptor.


## File I/O at a specified offset: `pread` and `pwrite`

`pread` and `pwrite` allow you to pass an offset, and a file, to read or write starting at an offset.

```c
#include <unistd.h>
ssize_t pread(int fd, void *buf, size_t count, off_t offset); // Returns number of bytes read, 0 on EOF, or –1 on error
ssize_t pwrite(int fd, const void *buf, size_t count, off_t offset); // Returns number of bytes written, or –1 on error
```

This is useful for multithreaded programs, because the file offset for each open file is global to all threads, so trying to use `lseek` on one thread would mess up the offset for other threads.

## Scatter-Gather I/O: `readv` and `writev`

```c
#include <sys/uio.h>
ssize_t readv(int fd, const struct iovec *iov, int iovcnt); // Returns number of bytes read, 0 on EOF, or –1 on error
ssize_t writev(int fd, const struct iovec *iov, int iovcnt); // Returns number of bytes written, or –1 on error
```

`readv` and `writev` allow for scatter-gather I/O, which transfer multiple buffers of data to and from files in a single system call.

Each element of `iov` is a struct:

```c
struct iovec {
    void *iov_base; /* Start address of buffer */
    size_t iov_len; /* Number of bytes to transfer to/from buffer */
};
```

### Scatter Input

`readv` reads a contiguous sequence of bytes from the file at `fd` and then scatters these bytes into the buffers at `iov`. It fills up each buffer in order, before proceeding to the next buffer.

`readv` completes atomically, which is an improvement over `read`. `readv` returns the number of bytes read or 0 if it encountered `EOF`.

### Gather Output

`writev` performs gather output, which concatenates data from all the buffers specified by `iov` and writes them as a sequence of contigious bytes to the file referred to by the file descriptor `fd`.

`writev` also completes atomically, and also can partially write, so checking its return value (same as `readv` is important.

### Performing scatter-gather I/O at a specified offset

Linux also allows for scatter-gather I/O at a specified offset with `preadv` and `pwritev`.

```c
#define _BSD_SOURCE
#include <sys/uio.h>
ssize_t preadv(int fd, const struct iovec *iov, int iovcnt, off_t offset); // Returns number of bytes read, 0 on EOF, or –1 on error
ssize_t pwritev(int fd, const struct iovec *iov, int iovcnt, off_t offset); // Returns number of bytes written, or –1 on error
```

This is useful for multithreaded applications that also want to use scatter-gather I/O.

## Truncating a file: `truncate` and `ftruncate`

`truncate` and `ftruncate` set the size of a file to the value specified by `length`.

```c
#include <unistd.h>
int truncate(const char *pathname, off_t length);
int ftruncate(int fd, off_t length); // Both return 0 on success, or –1 on error
```

If the file is longer than `length`, the excess data is lost. If the file is shorter than length, it is extended with null bytes or a hole.

`truncate` takes a pathname, and `ftruncate` takes a file descriptor.

## Nonblocking I/O

The `O_NONBLOCK` flag when opening a flag can be used for nonblocking I/O, which means:

- If the file can't be opened immediately, then `open` returns an error instead of blocking.
- After calling `open`, subsequent I/O operations are also non-blocking. If an I/O system call can't complete immediately, either partial data transfer is performed, or the system call fails with `EAGAIN` or `EWOULDBLOCK`.

## I/O on Large Files

Since `off_t` used to hold a file offset is a signed long, on 32-bit architectures, this would limit files to 2GB in size, which disks were much larger than. There was a large file summit (LFS) interface that allowed for the extension of SUSv2 to support larger files.

The lfs interface has the same name as normal functions but with `64` appended, like `open64`.

As well, lfs includes some other structs, like `stat64` and `off64_t`.

We can also just set the `_FILE_OFFSET_BITS` macro to 64, which converts all system calls into their LFS equivalents automatically.

## The `/dev/fd` directory

The virtual directory `/dev/fd` contains filenames `/dev/fd/n`, where `0..n` is a number corresponding to one of the open file descriptors for the process.

Opening one of the files in `/dev/fd` is the same as duplicating the file descriptor.


## Creating Temporary Files

Creating temporary files can be done with `mkstemp` or `tmpfile`, from glibc.

```c
#include <stdlib.h>
int mkstemp(char *template); // Returns file descriptor on success, or –1 on error
```

The template argument is a pathname in which the last 6 characters must be `XXXXXX`, which will be replaced to create a unique filename.

`mkstemp` creates the file with read and writer permissions for the file owner, no permissions for other users, and opens it with `O_EXCL`, so the caller has exclusive access to the file.

`tmpfile` creates a uniquely named temporary file that is opened for reading and writing. It is similarly opened with `O_EXCL`.

```c
#include <stdio.h>
FILE *tmpfile(void); // Returns file pointer on success, or NULL on error
```


Prev:
[file-io-the-universal-io-model](file-io-the-universal-io-model.md) Next: [processes](processes.md)
