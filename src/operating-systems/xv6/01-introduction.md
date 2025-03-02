---
title: Intro
date created: Saturday, March 1st 2025, 8:40:53 pm
date modified: Sunday, March 2nd 2025, 8:40:56 am
---

# Intro

- xv6 is a small (~6000 loc) OS from MIT built as a teaching tool for OSes.
- there are two implementations, the risc-v one will be used, but there is an x86-64 one.
- QEMU is used for emulating the OS, since you probably don't want to run it on real hardware (a buggy OS could fry hardware)

## The Codebase

- ~6000 loc of C, 300 lines of assembly. 
- Processes run in their own virtual address spaces using page tables
- pipes are supported
- multitasking with time slicing

## System Calls

- only 21 implemented, compared to hundreds
- fork, wait, exit, pipe, open/close/read/write, kill, exec, link, unlink
- Used to implement userspace, like cat, echo, grep, kill, ln, ls, mkdir, rm, wc
## Limitations

- No user authentication
- No network support
- No virtual memory paging
- Only two device drivers
- limited userspace + system calls
