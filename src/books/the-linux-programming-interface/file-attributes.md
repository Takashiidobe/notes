---
title: file-attributes
---

# File Attributes

Prev: [file-systems](file-systems.md) Next: [extended-attributes](extended-attributes.md)

## Retrieving File Information: `stat`

The `stat`, `lstat`, and `fstat` system calls retrieve information about a file.

```c
#include <sys/stat.h>
int stat(const char *pathname, struct stat *statbuf);
int lstat(const char *pathname, struct stat *statbuf);
int fstat(int fd, struct stat *statbuf); // All return 0 on success, or –1 on error
```

They differ in the way the file is specified:

- `stat` for information about a named file
- `lstat` for information about a link
- `fstat` for information about a file descriptor

- `stat` and `lstat` don't require permissions on the file itself, but they require search permissions on all parent directories.

All these system calls fill in a stat struct, which looks like this:

```c
struct stat {
    dev_t st_dev; /* IDs of device on which file resides */
    ino_t st_ino; /* I-node number of file */
    mode_t st_mode; /* File type and permissions */
    nlink_t st_nlink; /* Number of (hard) links to file */
    uid_t st_uid; /* User ID of file owner */
    gid_t st_gid; /* Group ID of file owner */
    dev_t st_rdev; /* IDs for device special files */
    off_t st_size; /* Total file size (bytes) */
    blksize_t st_blksize; /* Optimal block size for I/O (bytes) */
    blkcnt_t st_blocks; /* Number of (512B) blocks allocated */
    time_t st_atime; /* Time of last file access */
    time_t st_mtime; /* Time of last file modification */
    time_t st_ctime; /* Time of last status change */
};
```

- `st_dev` identifies the device on which the file resides.
- `st_ino` contains the inode number of the file.
- `st_uid` and `st_gid` respectively identify the user ID and group ID to which the file belongs.
- `st_nlink` is the number of hard links to the file.
- `st_mode` is a bitmask for identifying the file type and specifying file permissions.
- `st_size` is the total size of the file in bytes for a normal file, and for a link, the length of the pathname pointed to.
- `st_blocks` indicates the number of pointer blocks (512-bytes).
- `st_blksize` is the optimal block size for I/O in this file system. It's normally 4KB, 4096.
- `st_atime`, `st_mtime`, and `st_ctime` contain the last file access, last file modification, last status change.

Prev: [file-systems](file-systems.md) Next: [extended-attributes](extended-attributes.md)
