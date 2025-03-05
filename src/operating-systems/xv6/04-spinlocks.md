# Spinlocks

Spinlocks in xv6 have three fields:

```c
// Mutual exclusion lock.
struct spinlock {
  uint locked;       // Is the lock held? (0 = unlocked, 1 = locked)

  // For debugging:
  char *name;        // Name of lock.
  struct cpu *cpu;   // The cpu holding the lock.
};
```

The important functions are:

```c
void initlock(struct spinlock *lk, char *name);
// acquires a lock using atomic swap (AMOSWAP)
void acquire(struct spinlock *lk);
void release(struct spinlock *lk);
// checks whether cpu is holding lock. Must have interrupts off.
int holding(struct spinlock *lk);
// disable interrupts. These have a counter (noff) to count how many
// times interrupts have been disabled.
void push_off(void);
// enable interrupts. If noff is 0, then interrupts are enabled. If not,
// then it decrements noff and continues.
void pop_off(void);
```

Acquire does the following:

1. Disable interrupts
2. use atomic swap `amoswap` to wait to acquire the lock.
3. then it fences the lock to make sure that acquires happen after lock
   acquisition, and the compiler doesn't reorder code.
4. records which cpu got the lock in the code for debugging.

```c
  push_off(); // disable interrupts to avoid deadlock.
  if(holding(lk))
    panic("acquire");

  // On RISC-V, sync_lock_test_and_set turns into an atomic swap:
  //   a5 = 1
  //   s1 = &lk->locked
  //   amoswap.w.aq a5, a5, (s1)
  while(__sync_lock_test_and_set(&lk->locked, 1) != 0)
    ;

  // Tell the C compiler and the processor to not move loads or stores
  // past this point, to ensure that the critical section's memory
  // references happen strictly after the lock is acquired.
  // On RISC-V, this emits a fence instruction.
  __sync_synchronize();

  // Record info about lock acquisition for holding() and debugging.
  lk->cpu = mycpu();
```

Release does the following:

1. Makes sure the current cpu holds the lock.
2. sets the lock's cpu number to 0.
3. fences to make sure loads and stores are not reordered.
4. Then atomically sets `&lk->locked` to 0.

```c
  if(!holding(lk))
    panic("release");

  lk->cpu = 0;

  // Tell the C compiler and the CPU to not move loads or stores
  // past this point, to ensure that all the stores in the critical
  // section are visible to other CPUs before the lock is released,
  // and that loads in the critical section occur strictly before
  // the lock is released.
  // On RISC-V, this emits a fence instruction.
  __sync_synchronize();

  // Release the lock, equivalent to lk->locked = 0.
  // This code doesn't use a C assignment, since the C standard
  // implies that an assignment might be implemented with
  // multiple store instructions.
  // On RISC-V, sync_lock_release turns into an atomic swap:
  //   s1 = &lk->locked
  //   amoswap.w zero, zero, (s1)
  __sync_lock_release(&lk->locked);

  pop_off();
```

Holding makes sure we have the lock:
Interrupts must be off.

```c
  return lk->locked && lk->cpu == mycpu();
```

Spinlocks should not be held for long, since they make the CPU spin. Use
spin and wakeup instead, or use `wfi` (wait for input) to sleep as well.

## Interrupts

Interrupt handlers (like getting input from a keyboard) work like so:
They TRAP (disabling interrupts), do stuff, then SRET (to enable
interrupts)

This can deadlock unless interrupts are disabled. You could imagine a
case where an interrupt happens, and then after a lock is acquired,
another interrupt happens, stopping execution of the previous code,
while the current code is interrupted.

As well, if we had nested code that looks like:

```c
acquire()
    // do stuff
    acquire()
        // do stuff
    release()
release()
```

Release could prematurely enable interrupts, deadlocking the code again.
Thus, we have to make it so `acquire` and `release` go in stack order.
