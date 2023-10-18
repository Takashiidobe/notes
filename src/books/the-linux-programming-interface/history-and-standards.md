---
title: history-and-standards
---

# The Linux Programming Interface

Prev: [preface](preface.md) Next: [fundamental-concepts](fundamental-concepts.md)

## A Brief History of Unix and C

Linux is a descendant of Unix, which was an operating system built at bell labs in 1969. The C programming language was written to write the Unix kernel, which was previously written in assembly. [^1]

[^1]: "The UNIX Time-Sharing System" by Ritchie and Thompson goes into more details about the history of Unix.

Between 1969 and 1979, there were many editions of classic Unix, called editions.

- First edition: Nov 1971. Unix was on the PDP-11 and had a Fortran compiler and many useful utilities.
- Second edition: Jun 1972. Unix was installed on 10 machines within AT&T.
- Third edition: Feb 1973. This edition had a C compiler and pipes.
- Fourth edition: Nov 1973. This was rewritten in C.
- Fifth edition: Jun 1974. Installed on more than 50 computers.
- Sixth edition: May 1975. The first edition to be used outside of AT&T.

Because AT&T had a monopoly on the US telephone system, it could not sell Unix, so it licensed it out to universities starting in 1974. By 1977, Unix was running in 500 sites in many countries.

### The birth of BSD and System V

In 1979, the seventh edition of Unix was released, which included `awk`, `make`, `sed`, `tar`, `bash`, and a Fortran 77 compiler. As well, Thompson went back to Berkeley to work on adding features to Unix with some graduate students[^2]. This added `csh`, `vi`, virtual memory and the Fast File System to Unix. This would be called `3BSD`, for Berkeley software distribution.

[^2]: Bill Joy, one of the founders of Sun Microsystems, was one of those graduate students.

In 1983, the Computer Systems Research Group at Berkeley released 4.2BSD, which had TCP/IP sockets, and various networking tools. This later formed the basis for SunOS (from 1983) and the later BSDs, like FreeBSD, NetBSD, OpenBSD and Darwin (MacOS X's kernel).

Finally, in 1983, after AT&T was broken up by the US government, AT&T released System V, which eventually included the BSD networking tools.

## A Brief History of Linux

In 1984, Stallman, a programmer at MIT set to work creating a "free" Unix implementation. He started the "GNU" project, which stands for GNU's not Unix, with the aim of building a kernel and associated software packages. GNU is famous for its userspace (most linux utils use GNU tools to this day), its compiler collection (gcc), the gnu libc implementation (glibc), and the GPL license, which requires that projects with the GPL license must be made available in source code form.

### The Linux Kernel

In 1991, Linus Torvalds, a student at the University of Helsinki, started writing a Unix like operating system for his Intel 386 PC. He was taught by Tanenbaum, a professor who wrote Minix, a mini Unix system. Eventually Linux garnered a lot of programmers and it released its 1.0 in 1996. The rest, is history.

### An aside: The BSDs

Bill and Lynne Jolitz developed a port of the BSD OS to x86-32, with all AT&T code rewritten in 1991. Eventually, however, progress stalled, and it was forked into two groups: NetBSD, which prioritizes portability, and FreeBSD, which emphasizes performance. OpenBSD showed up a bit later in 1996, with a focus on security. In 2003, a new BSD, DragonflyBSD also appeared.

### Linux distributions

Linux just refers to the kernel developed by the Linux project. The early distributions, like slackware and debian showed up in 1993. The distributions built the complete operating system, and make choices such as which file system or packages are installed on the distribution.

## Standardization

Due to the disparity in lineage between the Unixes, it was difficult to port code between them, since they all had different features. Thus, a standardization effort began to synchronize the unixes together.


### The C Programming Language

The C programming language was first standardized by ANSI in 1989, which is sometimes called ANSI C or C89. Some improvements were made in 1999, which is called C99. More improvements landed in 2011, 2017, and 2023, which are called C11, C17, and C23.

### The First POSIX Standards

The term POSIX (Portable Operating System Interface) is a standard for Unix like operating systems ratified by the IEEE. Posix.1 was ratified in 1988, and the latest standard, POSIX.1-2008 was ratified in 2008.

Prev: [preface](preface.md) Next: [fundamental-concepts](fundamental-concepts.md)
