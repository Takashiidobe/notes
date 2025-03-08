# Trap Handling

This lecture goes over `proc.h` which focuses on process management in
and data structures to handle processes.

## Trap Handling

When a trap occurs, the CPU switches to kernel mode, disables
interrupts, saves user registers, and then processes the trap, before
restoring registers and returning control.

## Execution Flow from Trap to Sret

Trap Handling Begins:

- The hardware switches to supervisor mode.
- The CPU saves:
    - Program counter (PC) -> `sepc`
    - Trap cause -> `scause`
    - Jumps to uservec function (located in the trampoline page).

Saving User Context (uservec in trampoline page):

- Saves all user registers into the trap frame.
- Initializes the kernel stack pointer and core number (tp register).
- Switches to the kernel’s virtual address space (modifies satp).
- Jumps into the C function usertrap().

Processing the Trap (usertrap() in C)

- Updates stvec to point to the correct exception handler.
- Reads scause to determine the type of trap:
    - System Call -> Processes the syscall.
    - Hardware Interrupt -> Handles device or timer interrupts.
    - Program Error -> Terminates the process (exit()).
- If the time slice ends, the process is preempted and another process is scheduled.

Returning to User Mode (usertrapret() in C)

- Disables interrupts before returning.
- Resets `stvec` to point to `uservec` for future traps.
- Restores the user’s page table (modifies `satp`).
- Loads the user’s saved registers.
- Executes `sret`, restoring user mode execution.

## Key Data Structures

The `trapframe` struct stores the 31 GPRs from x1 to x31, saves the
program counter (`sepc`), stack pointer, `sp`, and `hartid` for the
running CPU.

### CPU struct

- There are 8 `cpu` structs, one for each core.

It outlines the pointer to the currently running process, the context
(where registers are saved), and the interrupt state.

```c
// Per-CPU state.
struct cpu {
  struct proc *proc;          // The process running on this cpu, or null.
  struct context context;     // swtch() here to enter scheduler().
  int noff;                   // Depth of push_off() nesting.
  int intena;                 // Were interrupts enabled before push_off()?
};

extern struct cpu cpus[NCPU];
```

### Process State

A process has a corresponding Proc structure:

- `pid` Process ID
- `state` Process state
- `parent` pointer to parent process

- `pagetable` pointer to the user page table
- `kstack` kernel stack pointer
- `trampframe` pointer to trap frame for user registers
- `context` CPU register save area

- `ofile` open files
- `cwd` current working directory
- `name` process name

And a corresponding proc state for each process.

```c
enum procstate { UNUSED, USED, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

// Per-process state
struct proc {
  struct spinlock lock;

  // p->lock must be held when using these:
  enum procstate state;        // Process state
  void *chan;                  // If non-zero, sleeping on chan
  int killed;                  // If non-zero, have been killed
  int xstate;                  // Exit status to be returned to parent's wait
  int pid;                     // Process ID

  // wait_lock must be held when using this:
  struct proc *parent;         // Parent process

  // these are private to the process, so p->lock need not be held.
  uint64 kstack;               // Virtual address of kernel stack
  uint64 sz;                   // Size of process memory (bytes)
  pagetable_t pagetable;       // User page table
  struct trapframe *trapframe; // data page for trampoline.S
  struct context context;      // swtch() here to run process
  struct file *ofile[NOFILE];  // Open files
  struct inode *cwd;           // Current directory
  char name[16];               // Process name (debugging)
};
```
