---
title: interlude-files-and-directories
---

# Interlude: Files and Directories

Prev:
[redundant-arrays-of-inexpensive-disks-raids](redundant-arrays-of-inexpensive-disks-raids.md)
Next:
[file-system-implementation](file-system-implementation.md)

## Files and Directories

Two key abstractions for virtualizing storage includes the file and the
directory. Each file has a low-level name, called an `inode number`.

Directories are an abstraction which contains a list of files and
folders.

The directory hierarchy starts at a root directory, and uses a separator
to name subsequent sub-directories until the desired file or directory
is named. There are absolute and relative pathnames.

Directories and files can have the same name as long as they are in
different locations. File names generally have two parts -- a name and a
file extension, to indicate the file type.

## Creating Files

To create a file, we use the `open` system call, and pass `O_CREAT` to
create a new file if it doesn't exist.

This code creates a file using the open system call.

```c
int fd = open("foo", O_CREAT|O_WRONLY|O_TRUNC,
S_IRUSR|S_IWUSR);
```

This can also be done with `creat`.

```c
int fd = creat("foo", S_IRUSR|S_IWUSR);
```

`open` returns a file descriptor -- an integer, private per process,
that acts as a handle to the file.

The OS would keep the number of open files in the `proc` struct on unix
systems.

## Reading and Writing Files

To read and write files, lets try to `cat` a file.

```c
> strace cat foo
open("foo", O_RDONLY|O_LARGEFILE) = 3
read(3, "hello\n", 4096) = 6
write(1, "hello\n", 6) = 6
hello
read(3, "", 4096) = 0
close(3) = 0
```

Going through the code, the call to open foo returns the int 3. This is
because each process has stdin (0), stdout (1), and stderr (2) as open
files. Thus, the first new file to be opened starts out at the integer
3.

Then, the program reads from file descriptor 3, the contents "hello\n"
which returns 6. (the size of the file). This is then written to stdout
(fd 1), which is shown. Then, the read stops as the call to read returns
0, indicating nothing was read. Finally, the file is closed.

## Reading And Writing, But Not Sequentially

To read randomly from a file, the system call `lseek` is used:

```c
off_t lseek(int fildes, off_t offset, int whence);
```

The first argument is the file descriptor to seek into:
The second argument is the offset, which puts the offset to a particular
location within the file.
The third argument determines how the seek is performed.

`SEEK_SET` means to offset to offset.
`SEEK_CUR` means the offset is set to its current location plus offset
bytes.
`SEEK_END` sets the offset to the size of the file plus offset bytes.

The OS thus caches an offset for each open file in the file system:

Examples might make this clearer:

The `read` system call reads the number of bytes requested in the file,
and increments the current offset by that amount, so the next `read`
goes to the right place.

| System Calls                 | Return Code | Current Offset |
|------------------------------|-------------|----------------|
| fd = open("file", O_RDONLY); | 3           | 0              |
| read(fd, buffer, 100);       | 100         | 100            |
| read(fd, buffer, 100);       | 100         | 200            |
| read(fd, buffer, 100);       | 100         | 300            |
| read(fd, buffer, 100);       | 0           | 300            |
| close(fd);                   | 0           | -              |

In another example, two file descriptors are allocated, each a different
entry in the open file table, which read the same file:

They both get an independent offset, so they read the same data.

| System Calls                  | Return Code | OFT[10] | OFT[11] |
|-------------------------------|-------------|---------|---------|
| fd1 = open("file", O_RDONLY); | 3           | 0       | -       |
| fd2 = open("file", O_RDONLY); | 4           | 0       | 0       |
| read(fd1, buffer1, 100);      | 100         | 100     | 0       |
| read(fd2, buffer2, 100);      | 100         | 100     | 100     |
| close(fd1);                   | 0           | -       | 100     |
| close(fd2);                   | 0           | -       | -       |

Another example involves using `lseek` to seek to a different location
in the file:

| System Calls                 | Return Code | Current Offset |
|------------------------------|-------------|----------------|
| fd = open("file", O_RDONLY); | 3           | 0              |
| lseek(fd, 200, SEEK_SET);    | 200         | 200            |
| read(fd, buffer, 50);        | 50          | 250            |
| close(fd);                   | 0           | -              |

## Shared File Table Entries: fork() and dup()

In the case of `fork()` and `dup()`, a parent has its own offset that is
shared with its child.

Imagine opening a file, setting its offset in the child, and then in the
parent:

```c
int main(int argc, char *argv[]) {
  int fd = open("file.txt", O_RDONLY);
  assert(fd >= 0);
  int rc = fork();
  if (rc == 0) {
    rc = lseek(fd, 10, SEEK_SET);
    printf("child: offset %d\n", rc);
  } else if (rc > 0) {
    (void) wait(NULL);
    printf("parent: offset %d\n",
    (int) lseek(fd, 0, SEEK_CUR));
  }
  return 0;
}
```

This returns:

```
prompt> ./fork-seek
child: offset 10
parent: offset 10
prompt>
```

The open file table keeps track of processes acting on an open file
table with a refcount field.

This can be used to create a shell:

```c
int main(int argc, char *argv[]) {
  int fd = open("README", O_RDONLY);
  assert(fd >= 0);
  int fd2 = dup(fd);
  // now fd and fd2 can be used interchangeably
  return 0;
}
```

## Writing Immediately with fsync()

The `write` system call buffers to the OS, which actually writes to the
file at some point in the future. For some applications this is
unacceptable, so the OS provides `fsync()`, which takes a file
descriptor, and returns after it has committed the write to disk.

```c
int fd = open("foo", O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR);
assert(fd > -1);
int rc = write(fd, buffer, size);
assert(rc == size);
rc = fsync(fd);
assert(rc == 0);
```

Also remember to `fsync` the directory the file is in as well.

## Renaming Files

To rename a file, `rename` is provided. `rename` is also atomic, so
it either succeeds or fails, with no in-between state.

```c
int fd = open("foo.txt.tmp", O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
write(fd, buffer, size); // write out new version of file
fsync(fd);
close(fd);
rename("foo.txt.tmp", "foo.txt");
```

This allows for atomic renaming of files.

## Getting Information About Files

To get information about files, `stat` is frequently used. On linux, the
struct might look like this:

```c
struct stat {
  dev_t st_dev; // ID of device containing file
  ino_t st_ino; // inode number
  mode_t st_mode; // protection
  nlink_t st_nlink; // number of hard links
  uid_t st_uid; // user ID of owner
  gid_t st_gid; // group ID of owner
  dev_t st_rdev; // device ID (if special file)
  off_t st_size; // total size, in bytes
  blksize_t st_blksize; // blocksize for filesystem I/O
  blkcnt_t st_blocks; // number of blocks allocated
  time_t st_atime; // time of last access
  time_t st_mtime; // time of last modification
  time_t st_ctime; // time of last status change
};
```

## Removing Files

To remove a file, `dtruss` or `strace` to find the system call:

```sh
prompt> strace rm foo
unlink("foo") = 0
```

## Making Directories

To make a directory, the `mkdir` system call is used. This creates an
empty directory with the given permissions:

```sh
prompt> strace mkdir foo
mkdir("foo", 0777) = 0
```

## Reading Directories

To read a directory, there are a set of different system calls:

`opendir` to open a dir, `readdir` to read a dir, and `closedir` to
close the directory.

```c
int main(int argc, char *argv[]) {
  DIR *dp = opendir(".");
  assert(dp != NULL);
  struct dirent *d;
  while ((d = readdir(dp)) != NULL) {
    printf("%lu %s\n", (unsigned long) d->d_ino, d->d_name);
  }
  closedir(dp);
  return 0;
}
```

The dirent struct looks like this:

```c
struct dirent {
  char d_name[256]; // filename
  ino_t d_ino; // inode number
  off_t d_off; // offset to the next dirent
  unsigned short d_reclen; // length of this record
  unsigned char d_type; // type of file
};
```

## Deleting Directories

To delete a directory, `rmdir()` is provided, but it comes with the
requirement that the directory is empty before it works.

## Hard Links

To create a file, we use the `link` system call, which takes two
arguments -- an old pathname and a new one, which links the two
together. `link` creates a pointer to the inode of the old file for the
new file.

When you `rm` a file, it decrements the reference count of the inode
that the file refers to. When `unlink` is called and the reference count
drops to 0, the inode is collected.

## Symbolic Links

Symbolic links allow you to create a `soft link`, which doesn't have the
restriction that it links two files together, which is done with `ln
-s`.

However, they also allow for dangling references:

```sh
prompt> echo hello > file
prompt> ln -s file file2
prompt> cat file2
hello
prompt> rm file
prompt> cat file2
cat: file2: No such file or directory
```

## Permission Bits and Access Control Lists

Unix permission bits are the first way to make access to files and
directories more granular.

```sh
prompt> ls -l foo.txt
-rw-r--r-- 1 remzi wheel 0 Aug 24 16:29 foo.txt
```

`-rw-r--r--` can be divided into three parts:

`rw-`(owner), `r--`(group), `r--` (anyone).

This file is readable and writable by the owner, readable by the group,
and readable by anyone.

The last bit, `x`, on files indicates if it is executable. However, for
directories, it indicates whether a user can cd and create files in the
directory.

## Making and Mounting A File System

To make a file system, `mkfs` and the `mount` system call are available.

This normally takes the file system type, and mount point, and creates a
new filesystem:

```sh
prompt> mount -t ext3 /dev/sda1 /home/users
```

Prev:
[redundant-arrays-of-inexpensive-disks-raids](redundant-arrays-of-inexpensive-disks-raids.md)
Next:
[file-system-implementation](file-system-implementation.md)
