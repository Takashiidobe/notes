---
title: file-system-implementation
---
# File System Implementation

Prev: [[40-interlude-files-and-directories]]
Next: [[42-locality-and-the-fast-file-system]]





## The Way to Think

To think about file systems, think of:

1. Data structures of the file system
  - Should the file system use a simple structure like an array or a
      complicated one?
2. Access methods
  - How does this map onto system calls like `open()`, `read()`,
      `write()`?

## Overall Organization

We divide the disk into 4 KB blocks. Imagine there are 64 blocks (0 -
63):

0-7, 8-15, 16-23, 24-31, 32-39, 40-47, 48-55, 56-63

The first chunk of these blocks (0-7) is reserved for the system's use.

We'll use 5 blocks (3-7) to hold inodes, which comprise a file, the size
of the file, owner and access rights, access and modify times, and other
information.

We need a way to index into the data and the inodes, so one block is
used for a data bitmap, and another is used for an inode bitmap.

Finally, the first block is the superblock, which contains information
about the particular file system, like how many inodes and data blocks
are in the system, where the inode table begins, and where the data
begins, as well as a magic number to identify the file system type.

## File Organization: The Inode

The inode is short for index node, because these nodes were arranged in
an array, and indexed into when accessing a particular inode.

To read an inode (like number 32), the file system would calculate the
offset into the inode region (32 * sizeof(inode)), which is 8192, add it
to the start of the inode table (12KB), and then find out it was located
at the 20KB.

Then it would issue a read to a sector on disk that corresponds to it
(512KB blocks, so sector 40).

### The Multi-Level Index

In order to support bigger files, file system designers had to introduce
different structures within inodes. Instead of pointing to a block that
contains user data, it would point to a block of pointers to more data.
This would allow more storage at the cost of another indirection.

### Tip: Consider Extent-Based Approaches

Instead of using a bitmap, its also possible to lay out files by pointer
+ length. This allows files to be laid out flat on disk.

Prev: [[40-interlude-files-and-directories]]
Next: [[42-locality-and-the-fast-file-system]]
