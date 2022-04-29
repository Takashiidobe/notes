---
title: mechanism-limited-direct-execution
---

# Mechanism: Limited Direct Execution

To virtualize the CPU, the CPU can time share for performance reasons.
We need to care about performance, where virtualization doesn't add
excessive overheard to the system.

Prev:
[interlude-process-api](interlude-process-api.md)
Next:
[scheduling-introduction](scheduling-introduction.md)

## Basic Technique: Limited Direct Execution

To run a process, lets think of direct execution:
Run a program directly on the CPU without limits

| OS                            | Program                  |
| ----------------------------- | ------------------------ |
| Create entry for process list |                          |
| Allocate memory for program   |                          |
| Load program with memory      |                          |
| Set up stack with argc/argv   |                          |
| Clear registers               |                          |
| Execute call main()           |                          |
|                               | Run main()               |
|                               | Execute return from main |
| Free memory of process        |                          |
| Remove from process list      |                          |

This makes sense, but the OS can't make sure the program doesn't reach
into other processes memory, nor can the OS stop it or re-run it.

## Problem 1: Restricted Operations

Direct execution is as fast as can be, but how does the CPU grant
requests for I/O to a disk, or other resources like more memory on the
heap?

One way would be to allow programs to do anything they wanted, but this
fails because any incorrect operations done by the user could corrupt a
disk or do worse things.

To aid in this, we introduce **user mode** where the user is limited to
only doing certain **safe** operations. User mode processes can
relinquish control to **kernel mode** operations by doing a system call,
which gives control to the kernel to more dangerous operations. System
calls need to **trap** into the kernel and then **return-from-trap**
back to the user-mode program.

The kernel can't trust user space applications, so it sets up a **trap
table** at boot time. The OS uses **trap handlers**, which setup code to
handle a trap instruction at a predetermined location on boot time to
handle system calls.

To specify a system call, a **system-call number** is assigned to each
system call, which is made so that user code cannot specify an exact
address to jump to, which protects the OS.

## Problem 2: Switching Between Processes

You might think that preempting a process is simple. Stop it, save its
state, and move to another process.

But if the OS isn't running on the CPU, and the process is, then the OS
is by definition dead -- it can't stop anything.

### A Cooperative Approach: Wait for System Calls

The first approach (on old Macs) is the **cooperative** approach - the
OS gives up the CPU to processes, which yield back to the OS after their
time is up, or they do some illegal (divide by zero).

Unfortunately, if processes end up in an infinite loop, the OS will
never get control again. Time to shut down the computer.

### A Non-Cooperative Approach: The OS Takes Control

Unfortunately, the cooperative approach has its pitfalls. Instead, we
can do a non-cooperative approach. A timer device is programmed to
interrupt the currently running process every X milliseconds.

When the interrupt handler fires, it returns control back to the OS.
At boottime, the OS sets up the trap table and interrupt handler, and
goes back to sleep, allowing a process to run. Then each process gets a
slice, the OS goes back on the CPU, and it can find a new process to
run.

### Saving and Restoring Context

Now that the OS has regained control, a **scheduler** has to make a
decision to continue running the current process or switch to another
one.

If the OS decides to switch processes, it does something called a
**context switch**, where the OS saves a few register values for the
currently-executing process, and setups up the stack for the next
process.

This can be done with the `swtch()` routine.

(swtch in xv6).

```c
# void swtch(struct context **old, struct context *new);
#
# Save current register context in old
# and then load register context from new.
.globl swtch
swtch:
# Save old registers
movl 4(%esp), %eax # put old ptr into eax
popl 0(%eax) # save the old IP
movl %esp, 4(%eax) # and stack
movl %ebx, 8(%eax) # and other registers
movl %ecx, 12(%eax)
movl %edx, 16(%eax)
movl %esi, 20(%eax)
movl %edi, 24(%eax)
movl %ebp, 28(%eax)

# Load new registers
movl 4(%esp), %eax # put new ptr into eax
movl 28(%eax), %ebp # restore other registers
movl 24(%eax), %edi
movl 20(%eax), %esi
movl 16(%eax), %edx
movl 12(%eax), %ecx
movl 8(%eax), %ebx
movl 4(%eax), %esp # stack is switched here
pushl 0(%eax) # return addr put in place
ret
```

## Worried About Concurrency?

What happens if two system calls fire at the same time? Or a timer
interrupt happens when an system call happens?

The OS might disable interrupts during interrupt processing so that case
might not happen, or lock data structures related to kernel processing.

Prev:
[interlude-process-api](interlude-process-api.md)
Next:
[scheduling-introduction](scheduling-introduction.md)
