---
title: "The Unix Time-Sharing System"
---

# The Unix Time-Sharing System

This paper was written by Ritchie and Thompson, presented for the ACM,
detailing v3 unix.

The Unix Time-Sharing system is a general-purpose, multi-user,
interactive operating system for the DEC PDP-11.

The kicker? It runs on a PDP-11, costing as little as $40,000.

Major programs include: assembler, ed, a linker, debugger, a C compiler,
a Basic interpreter, a formatter, a Fortran compiler, a Snobol
interpreter, Top-down compiler compiler (TMG), a bottom-up
compiler-compiler (YACC), form letter generator, macro processor (M6)
and permuted index program.

## Hardware and Software Environment

The PDP-11 has a 16-bit word computer, with 144kb of core memory,
which Unix occupies 42kb, with device drivers, I/O buffers, and system
tables occupying another few 5kb.

The hard disk is a 1MB fixed-head disk, used for file system storage
and swapping, with four moving head 2.5MB removable disks, and a single
40MB disk pack.

## The File System

The most important job of Unix is to provide a file system. It provides:

1. Ordinary disk files
2. Directories
3. Special Files

### Ordinary Files

Ordinary files are just characters demarcated by the newline character.

### Directories

Directories introduce a structure on the file system as a whole. Each
user in the OS has a home directory of their own files, and they can
make subdirectories, which are all access controlled.

The system mains several directories for its own use, like system
administration.

Search starting with '/' starts at the root, while search without it
starts in the user's current directory.

A file may be linked to another location, where it is simply a pointer
to its location (this is a symlink).

### Special Files

Each I/O device supported by unix is associated with one file -- they
are read and written to like ordinary disk files, but requests to read
or write result in activation of the associated device.

For example, special devices reside in `/dev`. For example, punch paper
tape (the printer) would be at `/dev/ppt`. You could then write to it
"echo hi > /dev/ppt" and that would write the bytes corresponding to 'hi'
to that device.

This allows three advantages:

1. file and device I/O are as similar as possible.
2. a program can be passed a file or a device and handle it the same.
3. special files (devices) are subject to the same protection as files.

### Removable File Systems

Using the `mount` system call, a user can turn a leaf (a file) into a
subtree that uses that device as storage.

The user can then choose to `cd` into that subtree, and use it as
normal, except that the leaf file turns into the root directory of the
filesystem, and that it cannot reference files on other mounted
filesystems.

In the root directory of all file systems, '..' refers to the directory
itself, instead of its parent.

### Protection

Each user of the system is assigned a unique user identification number.
When a file is created, it is marked with that user id. Also, files are
given seven protection bits -- six of these specify read, write, and
execute permission for the owner for the file and other users.

There is a concept of a "super user" which isn't bound to the
permissions setup of the normal users.

### I/O Calls

I/O calls entail `open`, `create`, `write` to modify files, which are
represented by file handles. Files have
no limit on size nor any distinction on random or sequential I/O. The
file system also has no user-visible locks on the file system, due to
their overhead and the fact that users don't normally update other users
files.

The `read` system call returns the bytes transmitted, which returns 0
when it hits the end of file marker.

To do random access I/O, you can take a file handle, a pointer,
and the `seek` call to seek to a location in the file based on the
pointer, either positive or negative.

## Implementation of the File System

A directory entry only contains a name and a pointer to the file. The
pointer is an integer, called an `i-number`, short for `index number` of
the file. The i-node contains a description of the file as follows:

1. Its owner.
2. Its protection bits.
3. The physical disk or tape addresses for the file contents
4. Its size.
5. Time of last modification
6. The number of links to the file
7. A bit whether the file is a directory
8. A bit whether the file is a special file
9. A bit indicating whether the file is large or small.

Calls to open or create return a file pointer. When a file is created,
an i-node is allocated for it, and a directory entry is made, which
contains the name of the file and the i-node number. Making a link
involves creating a directory entry with the new name, copying the
i-number, and incrementing the link-count field of the i-node.

Removing a file involves decrementing the link-count of the i-node, and
erasing the directory entry. If the link-count drops to 0, it is freed.

The filesystem is divided into 512-bit blocks, which are logically
addressable.

### Efficiency of the File System

The filesystem is fairly efficient -- running an assembler program, the
time was 35.9 seconds, with 63.5% overhead from assembler execution,
16.5% system overhead, and 20% disk wait time.

## Processes and Images

Each process gets three logical segments: the text segment begins at
location 0 in the virtual address space. This is for putting
compile-time data. This is write-protected, and a single copy of it is
shared among all processes executing the same data.

The next 8kb are allocated for the stack.

The next segment is a non-shared, writable data segment, which can be
expanded with a system call (this is the heap).

### Processes

Processes are created with the `fork` system call. This splits the
process into two paths. Control returns from the fork to the parent,
while in the child, control is passed to the location label.

### Pipes

Processes may communicate through each other with the `pipe` system
call, which allows the output of one program to be send as input to
another process.

### Execution of Programs

the `execute` system call (execute(file, arg1, arg2,...argn)) can be
used to execute a file in the current process.

### Process Synchronization

Process synchronization is done with the `wait` system call. Wait
returns the processid of the terminated process. An error return is
generated if the calling process has no descendants.

### Termination

`exit` terminates a process, destroys its image, and closes its open
files.

## The Shell

### Standard I/O

The shell opens up two file descriptors, `0` for reading user input, and
`1`, for writing to. These two files can be read and written to by
programs in the shells lifecycle.

The shell can change the assignments of these file descriptors. For
example, `>` changes the file descriptor `1` to the file specified after
`>`. Likewise, `<` redirects input to a process from the file specified
after `<`. So `ed < script` means that `ed` will read from the text of
`script`.

### Filters

The `|` character is a filter, which is used to direct output from one
command to the input of another.

### Command Separators: Multitasking

Commands may be separated by semicolons. The `&` character returns the
process id to the shell, but executes the job in the background (is non-
blocking).

### The Implementation of the Shell

The shell mainly waits for a user to type a command.

When the new-line character ending the line is typed, the shell's read
call returns.

The shell analyzes the command line, putting the arguments in a form
appropriate for execute.

Then fork is called, which generates a child process. That child process
is given the appropriate arguments. The parent process then `waits` for
the child process to die. Then, it returns back to the user.

If the `&` character is provided, then it simply doesn't wait.

Since the child inherits from the parent process, this all works as
expected.

Finally, when an argument with `<` or `>` is given, it is only necessary
to close file `0` or `1`, and then open the output file. This is because
the file descriptor opened, by convention, is the lowest available
number.

Filters are straightforward extensions of standard I/O redirection with
pipes used, instead of files.

### Initialization

The shell itself is a child process of another process, called `init`.
`init` is used to set up devices with a process. Init then waits for
logins, where it reads a password file and then changes to the user's
home directory, and executes the shell, allowing the user to access
commands.

This then loops.

### Other Programs as Shell

The Unix System can also set up init to drop a specific user into a
different program than the shell, like `ed` for text editing. There are
also games like chess, blackjack, and 3D tic-tac-toe.

## Traps

The PDP-11 hardware detects a number of hardware faults, like reference
to nonexistent memory. Such faults cause the processor to trap to a
system routine. Normally, this results in the process being terminated
and the memory of the process written to a `core` file in the current
directory for debugging.

You can also use the quit signal to exit in the case that something goes
wrong.

## Perspective

The UNIX OS is successful because of its low hardware requirements, and
simple abstraction over devices as files. As well, since UNIX was dog
fooded, most of its design mistakes were fixed as soon as they appeared.

The shell, the file system, and access system have been extremely useful
for programmers to use.
