---
title: the-abstraction-the-process
---
# The Abstraction: The Process

Prev: [[03-a-dialogue-on-virtualization]]
Next: [[05-interlude-process-api]]





## The Process

The process is a running program. It has a bunch of instructions and
some memory, which is ready to spring into action. The OS takes this
process and executes it.

Also, a computer needs to run many processes at the same time (music,
web browser, a game, etc). It needs to virtualize the CPU by running one
process, then stopping it, and running another, and so forth. (This is
time-sharing).

Mechanisms are low level machinery to implement functionality for the
OS.

A context switch allows the Os the stop the running program and starting
running another one.

The high-level mechanism to run a program is a **policy**. A Policy is
an algorithm that makes decisions in the OS. A scheduling policy might
take some data to build a schedule of processes to run.

## The Abstraction: A Process

A process contains its machine state, what it can read/write, its
address space (where it can address into), as well as the program
counter (which is the instruction of the program currently being
executed, a stack pointer and associated frame pointer to manage the
stack).

## Process API

A process should be able to support fundamental operations:

1. Creation of processes
2. Destruction of processes
3. Waiting until the process finishes
4. Miscellaneous operations, like suspending and resuming
5. Status, like how long a process has run and its current state.

## Process Creation: A Little More Detail

To run a process, the OS must load its code and static data into memory,
in the address space of the process.

This can be done eagerly (all at once) or lazily (as needed). The
OS needs to allocate a stack, populated with argc and argv, as well as a
heap, which can be `malloc()`ed and `free()`d.

The OS may also set up I/O. Each process has three open file
descriptors, stdin, stdout, and stderr.

Then it runs main after all its setup has been done.

## Process States

A Process can be:

- Running
- Ready
- Blocked

A scheduler can move it from running to ready, and it can be blocked
while waiting for I/O, wherein it can be moved to done.

## Data Structures

A process list might keep a set of processes and relevant information
about it (here's what the xv6 operating system keeps for its processes).

```c
// the registers xv6 will save and restore
// to stop and subsequently restart a process
struct context {
  int eip;
  int esp;
  int ebx;
  int ecx;
  int edx;
  int esi;
  int edi;
  int ebp;
};
// the different states a process can be in
enum proc_state { UNUSED, EMBRYO, SLEEPING,
RUNNABLE, RUNNING, ZOMBIE };
// the information xv6 tracks about each process
// including its register context and state
struct proc {
  char *mem; // Start of process memory
  uint sz; // Size of process memory
  char *kstack; // Bottom of kernel stack
  // for this process
  enum proc_state state; // Process state
  int pid; // Process ID
  struct proc *parent; // Parent process
  void *chan; // If non-zero, sleeping on chan
  int killed; // If non-zero, have been killed
  struct file *ofile[NOFILE]; // Open files
  struct inode *cwd; // Current directory
  struct context context; // Switch here to run process
  struct trapframe *tf; // Trap frame for the
  // current interrupt
};
```

Prev: [[03-a-dialogue-on-virtualization]]
Next: [[05-interlude-process-api]]
