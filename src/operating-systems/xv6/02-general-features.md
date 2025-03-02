---
title: Memory and Caching
date created: Sunday, March 2nd 2025, 9:07:43 am
date modified: Sunday, March 2nd 2025, 9:08:00 am
---
Some of the main features of xv6 are covered here:

# Memory and Caching

xv6 has 128MB of main memory, which is hardwired into the kernel with
a #derive. In real life systems, this is dynamic.
As well, the kernel has to use caching (L1, L2, L3 caches) to optimize
performance. xv6 does not.

# Device Support

- xv6 has UART (Universal Asynchronous Receiver-Transmitter) support for
  connecting to devices.
- xv6 only supports a single disk drive, which is emulated as a file on
  the host machine.
- Real world processors have interrupt controllers like PLIC
  (Platform-Level Interrupt Controllers) which manage interrupts and
  assigns them to the appropriate core, and CLIC (Core-Local Interrupt
  Controllers) which handle interrupts per core.

# Memory Allocation

- Physical Memory in xv6 is divided into 4KB pages. The kernel manages
  memory using a free list, a linked list of available pages.
- When memory is needed, the kernel allocates a page from the free list.
- When no longer needed, the page is returned to the front of the free
  list.

- There is a three-level page table to manage virtual memory.
- Kernel Page Table (Maps physical memory for all cores)
- per-process Page table (Maps virtual address space for each process)

Pages can be marked as:

- R (Readable)
- W (Writable)
- X (Executable)
- U (User-accessible)
- V (Valid)

Where user-mode processes can only access pages marked as U.

# Scheduling

xv6 has a simple round-robin scheduler.

1. Each process has a time slice of 1 million cycles
2. After the time slice expires, the process is returned to the ready
   queue.
3. The next process is selected for execution

All cores share a single ready queue, where each core scans through the
array linearly, searching for a runnable process.

# Booting

xv6 also simplifies the boot process:

The emulator loads the kernel directly into a fixed memory location.
And starts execution from there.

# Synchronization & Concurrency

xv6 has spinlocks where:

- 0 = free
- 1 = held

With two accompanying functions:

- `acquire()` wait in a loop until the lock is free, then lock.
- `release()` unlocks the acquired lock by setting variable to 0.

As well, there's `sleep()` and `wake_up()`

- `sleep()` puts a process in a blocked state
- `wake_up()` changes a sleeping process back to runnable for scheduling

There's also interrupt disabling. Each core can enable/disable
interrupts. However, this only works on the local core, so other cores
can still modify shared memory, so locking is necessary.

# System Limits

- The process table is an array.
- The maximum number of open files is predefined.
- Linear searches are used for killing processes.

# User Address Space

A program's virtual memory is laid out as so:

1. Code and Data section (loaded from the binary during execution)
2. Stack (Allocated one 4KB page). If the program exceeds this, it
   crashes.
3. Heap (Grows dynamically in page-sized increments)
4. Guard Page (prevents stack overflow by marking a page as
   inaccessible)
5. Trap/Trampoline pages (traps are per process, trampolines for all
   processes)
    - Trap frames store process state during exceptions
    - Trampoline for handling traps

Environment variables are not supported.

# Risc-V Memory Model

- Risc-v has a 39-bit virtual address space, and xv6 uses 38 bits,
  limiting the virtual address space to 256GB.
