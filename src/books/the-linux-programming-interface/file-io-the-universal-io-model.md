---
title: file-io-the-universal-io-model
---

# File I/O: The Universal I/O Model

Prev: [system-programming-concepts](system-programming-concepts.md)
Next: [file-io-further-details](file-io-further-details.md)

## Overview

All system calls for performing I/O refer to open files using a file descriptor, a non-negative integer. File descriptors refer to all types of open files. All processes have its own file descriptors.

| File Descriptor | Purpose         | POSIX name    | stdio stream |
|-----------------|-----------------|---------------|--------------|
| 0               | standard input  | STDIN_FILENO  | stdin        |
| 1               | standard output | STDOUT_FILENO | stdout       |
| 2               | standard error  | STDERR_FILENO | stderr       |

Note that `stdin`, `stdout`, and `stderr` can be changed with `freopen`, so they only start out as `0`, `1`, `2`, and need not be those values.

The main system calls for dealing with files are:

- `open(pathname, flags, mode)`: open the file identified by pathname, setting `flags` to change the behavior of the file and `mode` to change permissions.
- `read(fd, buffer, count)`: read the file identified by `fd`, into the `buffer`, reading `count` bytes.
- `write(fd, buffer, count)`: writes up to `count` bytes from `buffer` to the open file referred to by `fd`.
- `close(fd)`: release the file descriptor `fd` back to the kernel.

## Universality of I/O

Unix has an idea of universality of I/O, so `open`, `read`, `write`, `close` can be used on all types of files, even terminals and devices. When access to specific features outside of the universal I/O model are required, the `ioctl` system call can be used.

## Opening a File: `open`

```c
#include <sys/stat.h>
#include <fcntl.h>
int open(const char *pathname, int flags, ... /* mode_t mode */); Returns file descriptor on success, or –1 on error
```

`open` is used to create a file at `pathname`. Some example access modes might look like:

| Access Mode | Description  |
|-------------|--------------|
| O_RDONLY    | Readonly     |
| O_WRONLY    | Writeonly    |
| O_RDWR      | Read + Write |

If open succeeds, it returns the lowest-numbered unused file descriptor for a process.

### The flags argument:

Some of the meanings of the flags argument:

| Flag                 | Purpose                                                          | SUS? |
|----------------------|------------------------------------------------------------------|------|
| O_RDONLY             | Open for reading only                                            | v3   |
| O_WRONLY             | Open for writing only                                            | v3   |
| O_RDWR               | Open for reading and writing                                     | v3   |
| O_CLOEXEC            | Set the close-on-exec flag (since Linux 2.6.23)                  | v4   |
| O_CREAT              | Create file if it doesn’t already exist                          | v3   |
| O_DIRECT             | File I/O bypasses buffer cache                                   |      |
| O_DIRECTORY          | Fail if pathname is not a directory                              | v4   |
| O_EXCL With O_CREAT: | create file exclusively                                          | v3   |
| O_LARGEFILE          | Used on 32-bit systems to open large files                       |      |
| O_NOATIME            | Don’t update file last access time on read() (since Linux 2.6.8) |      |
| O_NOCTTY             | Don’t let pathname become the controlling terminal               | v3   |
| O_NOFOLLOW           | Don’t dereference symbolic links                                 | v4   |
| O_TRUNC              | Truncate existing file to zero length                            | v3   |
| O_APPEND             | Writes are always appended to end of file                        | v3   |
| O_ASYNC              | Generate a signal when I/O is possible                           |      |
| O_DSYNC              | Provide synchronized I/O data integrity (since Linux 2.6.33)     | v3   |
| O_NONBLOCK           | Open in nonblocking mode                                         | v3   |
| O_SYNC               | Make file writes synchronous                                     | v3   |

### Errors from Open

- **EACCES** The file permissions don't allow the calling process to open the file in the mode specified by flags.
- **EISDIR** The specified file is a directory, and cannot be opened for writing.
- **EMFILE** The process resource limit on the number of file descriptors has been reached.
- **ENFILE** The system limit on the number of file descriptors has been reached.
- **ENOENT** The specified file doesn't exist, and `O_CREAT` wasn't specified, or one of the directories in pathname doesn't exist.
- **EROFS** The file is on a read-only file system, and the user wanted to write to it.
- **ETXTBSY** The specified file is an executable file that is executing. It is not possible to modify an executing file.

### The `creat` System Call

Before open had the `O_CREAT` flag, `creat` was used to open and create a new file.

```c
#include <fcntl.h>
int creat(const char *pathname, mode_t mode); // Returns file descriptor, or –1 on error
```

## Reading from a File: `read`

```c
#include <unistd.h>
ssize_t read(int fd, void *buffer, size_t count); // Returns number of bytes read, 0 on EOF, or –1 on error
```

`read` reads from `fd` the amount of bytes requested, and puts it into `buffer`. The `ssize_t` return value is the number of bytes read.

## Writing to a File: `write`

```c
#include <unistd.h>
ssize_t write(int fd, void *buffer, size_t count); // Returns number of bytes written, or –1 on error
```

A successful return from `write` does not mean the write was transferred to disk, due to the OS caching layer batching writes.

## Closing a File: `close`

```c
#include <unistd.h>
int close(int fd); // Returns 0 on success, or –1 on error
```

`close` is used to close file descriptors explicitly.

## Changing the File Offset: `lseek`

For each open file, the kernel records a file offset, which is the location in the file where the next `read` or `write` should commence.

The first byte is at offset 0.

This can be changed with `lseek`.

```c
#include <unistd.h>
off_t lseek(int fd, off_t offset, int whence); // Returns new file offset if successful, or –1 on error
```

The whence argument indicates the point from where offset should be interpreted:

- **SEEK_SET** the offset is from the beginning of the file.
- **SEEK_CUR** the offset is from the current file offset.
- **SEEK_END** the offset is set to the size of the file plus offset.

The return value of `lseek` is the new file offset.

### File holes

If a program seeks to the end of a file and writes to it, it actually writes bytes in the location. The gap between the old end of the file and the newly written content is called a file hole. These holes exist when reading, but don't take up any disk space.

## Operations Outside the Universal I/O Model: `ioctl`

`ioctl` is used for performing operations outside the Universal I/O model.

```c
#include <sys/ioctl.h>
int ioctl(int fd, int request, ... /* argp */); // Value returned on success depends on request, or –1 on error
```

Prev: [system-programming-concepts](system-programming-concepts.md)
Next: [file-io-further-details](file-io-further-details.md)
