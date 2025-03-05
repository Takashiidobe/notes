---
title: 03-startup-and-organization
date created: Tuesday, March 4th 2025, 3:50:56 pm
date modified: Tuesday, March 4th 2025, 3:52:18 pm
---

# Startup and Organization

Some critical files include:

## Kernel

`entry.S` which sets up the stack for C code to run
    - There's a line, `csrr a1, mhartid`, which reads the hardware
      thread (hart) into a1. This is because there are multiple threads
      and they all need to have different stacks.
`start.c`which starts the computer in machine mode
`main.c` which starts the OS in supervisor mode, sets up and runs the
kernel. There's different code that runs based on if the current core is
the first core (`cpuid() == 0`), because the first core has to set up
the kernel, whereas all the rest wait and then get scheduled afterwards.

## User

`initcode.S` which contains code that execs `/init`, and sets up `argc`
and `argv` for a user process.
