# Kernel Startup and Timers

The focus is on `entry.S` and `start.c`, which transitions to supervisor
mode, has timer initialization, and handles timer interrupts in
`kernelvec.S`

## Kernel Startup Process

### entry.S

- `entry.S` is executed in machine mode, which is the highest privilege
level.
- It sets the stack pointer `sp` for each core.
- Each core gets its own 4KB stack.
- With `mhartid` to determine the core number of 0-7.
- jumps to `start()`

### start.c

- In machine mode, `start()` sets the `mstatus` register to supervisor
mode
- sets `mepc` to point to `main()`
- ensures `mret` will run `main()`
- disables paging by setting `satp = 0`
- Delegates exceptions and interrupts to supervisor mode.
- Enables interrupts from devices
- Configures memory protection
- initializes timer interrupts with `timerinit()`
- saves `mhartid` into `tp`
- executes `mret` to jump to main and get into supervisor mode

## Timer Initialization

`timerinit()` configures the core's timer with `mtimecmp` and schedules
the first timer interrupt 1 million cycles later.
- Uses `timer_scratch` to store `mtimecmp` and the timer interval.
- writes `timer_scratch` to `mscratch`
- sets `mtvec` to `timervec` to point the machine-mode trap handler to
  `timervec`
- enables machine-mode interrupts `mstatus` and `mie`

## Handling Timer Interrupts

After an interrupt happens:

- `timervec` executes, saving `a1`-`a3` into `timer_scratch`
- schedules the next timer interrupt at 1 million cycles in the future
- triggers a software interrupt to supervisor mode
- restores saved registers and executes `mret`

## Supervisor mode

After switching to supervisor mode, the kernel receives a software
interrupt, which it recognizes as a timer interrupt, and switches the
currently run process.

