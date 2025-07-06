---
title: Risc-V Architecture
date created: Tuesday, March 4th 2025, 8:10:00 pm
date modified: Sunday, July 6th 2025, 2:42:57 pm
---
# Risc-V Architecture

Risc-V64 has 32 Registers. There's also a 128 bit version with 64
registers, and a Risc-V32E (E for embedded) with 16 registers.

Some notes:

Each register can be referred to as x0-x31, or its `abi` name, which
corresponds more directly to what it does:

i.e. `zero` always returns zero.

In machine/supervisor mode, the registers x8-x12 have different meanings
to be used. As well, `mhartid` exists, which can be read using `csrr`.
You can place it into a variable, like `csrr a0, mhartid` to get the
core number of the current core, and place it in a0.


 | Register | ABI Name | Callee/Caller Saved | Notes                              | Machine Mode                              | Supervisor Mode                           |
 |----------|----------|---------------------|------------------------------------|-------------------------------------------|-------------------------------------------|
 | x0       | zero     | -                   | Constant 0                         | 0                                         | 0                                         |
 | x1       | ra       | Caller-saved        | Return address                     | Return address                            | Return address                            |
 | x2       | sp       | Callee-saved        | Stack pointer                      | Stack pointer                             | Stack pointer                             |
 | x3       | gp       | -                   | Global pointer                     | Global pointer                            | Global pointer                            |
 | x4       | tp       | -                   | Thread pointer                     | Thread pointer                            | Thread pointer                            |
 | x5       | t0       | Caller-saved        | Temporary                          | Scratch                                   | Scratch                                   |
 | x6       | t1       | Caller-saved        | Temporary                          | Scratch                                   | Scratch                                   |
 | x7       | t2       | Caller-saved        | Temporary                          | Scratch                                   | Scratch                                   |
 | x8       | s0/fp    | Callee-saved        | Saved register/Frame pointer       | Saved                                     | Saved                                     |
 | x9       | s1       | Callee-saved        | Saved register                     | Saved                                     | Saved                                     |
 | x10      | a0       | Caller-saved        | Function argument / return value   | Argument/return value                     | Argument/return value                     |
 | x11      | a1       | Caller-saved        | Function argument / return value   | Argument/return value                     | Argument/return value                     |
 | x12      | a2       | Caller-saved        | Function argument                  | Argument                                  | Argument                                  |
 | x13      | a3       | Caller-saved        | Function argument                  | Argument                                  | Argument                                  |
 | x14      | a4       | Caller-saved        | Function argument                  | Argument                                  | Argument                                  |
 | x15      | a5       | Caller-saved        | Function argument                  | Argument                                  | Argument                                  |
 | x16      | a6       | Caller-saved        | Function argument                  | Argument                                  | Argument                                  |
 | x17      | a7       | Caller-saved        | Function argument / system call ID | Argument                                  | Argument                                  |
 | x18      | s2       | Callee-saved        | Saved register                     | Saved                                     | Saved                                     |
 | x19      | s3       | Callee-saved        | Saved register                     | Saved                                     | Saved                                     |
 | x20      | s4       | Callee-saved        | Saved register                     | Saved                                     | Saved                                     |
 | x21      | s5       | Callee-saved        | Saved register                     | Saved                                     | Saved                                     |
 | x22      | s6       | Callee-saved        | Saved register                     | Saved                                     | Saved                                     |
 | x23      | s7       | Callee-saved        | Saved register                     | Saved                                     | Saved                                     |
 | x24      | s8       | Callee-saved        | Saved register                     | Saved                                     | Saved                                     |
 | x25      | s9       | Callee-saved        | Saved register                     | Saved                                     | Saved                                     |
 | x26      | s10      | Callee-saved        | Saved register                     | Saved                                     | Saved                                     |
 | x27      | s11      | Callee-saved        | Saved register                     | Saved                                     | Saved                                     |
 | x28      | t3       | Caller-saved        | Temporary                          | Scratch                                   | Scratch                                   |
 | x29      | t4       | Caller-saved        | Temporary                          | Scratch                                   | Scratch                                   |
 | x30      | t5       | Caller-saved        | Temporary                          | Scratch                                   | Scratch                                   |
 | x31      | t6       | Caller-saved        | Temporary                          | Scratch                                   | Scratch                                   |
 | -        | -        | -                   | **Program Counter**                | `pc` (Next instruction address)           | `pc` (Next instruction address)           |
 | -        | -        | -                   | **Hart ID**                        | `mhartid` (Hart ID)                       | -                                         |
 | x8       | s0/fp    | Callee-saved        | **Status Register**                | `mstatus`                                 | `sstatus`                                 |
 | x9       | s1       | Callee-saved        | **Exception Program Counter**      | `mepc`                                    | `sepc`                                    |
 | x10      | a0       | Caller-saved        | **Trap Vector**                    | `mtvec`                                   | `stvec`                                   |
 | x11      | a1       | Caller-saved        | **Trap Cause**                     | `mcause`                                  | `scause`                                  |
 | x12      | a2       | Caller-saved        | **Scratch Register**               | `mscratch`                                | `sscratch`                                |
 | -        | -        | -                   | **Trap Value**                     | `mtval` (Faulting address or instruction) | `stval` (Faulting address or instruction) |
 | -        | -        | -                   | **Cycle Counter**                  | `mcycle` (Counts CPU cycles)              | -                                         |
 | -        | -        | -                   | **Machine Timer**                  | `mtime` (Real-time clock ticks)           | -                                         |

## Registers

- `zero` always returns zero. This is useful when you might need to get
  a zero value for an operation. You can always use zero, e.g. for
  XORing, or copying, i.e. `add x5, x1, x0` copies `x1` to `x5`.
- `ra` is the return address `jal ra, func` would jump to `func` and
  store the return address in `ra`, so you can `ret` out of func and get
  back to `ra` without having to spill to the stack.
- `sp` is the stack pointer. You can use it to set up the stack `addi
  sp, sp, -16` (allocate two double words of stack space).
- `gp` is the global pointer. It points to static data, `la gp,
  _global`. It's used by the compiler to jump to data via offsets
  quickly.
- `tp` is the thread pointer. In xv6 it's used to hold the `mhartid`
  value, the core number for the thread.
- `pc` is the program counter. It holds the next instruction address.

### Function Args/Working Args

- `a0` and `a1` are for function args and return values.
- `a0` through `a7` are for function arguments in general.

### Temporary Registers

- `t0` through `t6` are temporary registers, and can be used inside a
  function or to do anything. They're all caller saved, so a function
  can do anything to them.

### Callee-Saved

- `s0` through `s11` are callee-saved registers, so if a function uses
  them, it must save them to the stack and restore them before
  returning.

## Context Switches

During a context switch, the kernel has to save all the user mode
registers, and then restore them when choosing another process to run.

This can be seen in `kernelvec.S`, which saves registers onto the stack,
calls `kerneltrap` to process the trap, and then restores all registers
except the `tp`.

```asm
.globl kerneltrap
.globl kernelvec
.align 4
kernelvec:
        # make room to save registers.
        addi sp, sp, -256

        # save caller-saved registers.
        sd ra, 0(sp)
        sd sp, 8(sp)
        sd gp, 16(sp)
        sd tp, 24(sp)
        sd t0, 32(sp)
        sd t1, 40(sp)
        sd t2, 48(sp)
        sd a0, 72(sp)
        sd a1, 80(sp)
        sd a2, 88(sp)
        sd a3, 96(sp)
        sd a4, 104(sp)
        sd a5, 112(sp)
        sd a6, 120(sp)
        sd a7, 128(sp)
        sd t3, 216(sp)
        sd t4, 224(sp)
        sd t5, 232(sp)
        sd t6, 240(sp)

        # call the C trap handler in trap.c
        call kerneltrap

        # restore registers.
        ld ra, 0(sp)
        ld sp, 8(sp)
        ld gp, 16(sp)
        # not tp (contains hartid), in case we moved CPUs
        ld t0, 32(sp)
        ld t1, 40(sp)
        ld t2, 48(sp)
        ld a0, 72(sp)
        ld a1, 80(sp)
        ld a2, 88(sp)
        ld a3, 96(sp)
        ld a4, 104(sp)
        ld a5, 112(sp)
        ld a6, 120(sp)
        ld a7, 128(sp)
        ld t3, 216(sp)
        ld t4, 224(sp)
        ld t5, 232(sp)
        ld t6, 240(sp)

        addi sp, sp, 256

        # return to whatever we were doing in the kernel.
        sret
```

## Risc-V Modes

There are three modes in Risc-V, machine, supervisor, and user.

### Machine Mode

- The highest, most powerful mode.
- This mode is entered after turning on the computer, and is used for
  startup of the kernel, but is quickly left to get into supervisor mode
  to run the kernel. `entry.S` is the only machine mode code that gets
  executed.
- Timer interrupts require using machine mode.

### Supervisor Mode

- Kernel code runs in supervisor mode.
- Some instructions are privileged, and can only be run in machine or
  supervisor mode.

### User Mode

- Userspace runs in this mode.
- Privileged instructions cause a trap + abort.

## Control and Status Registers (CSRs)

There are special instructions that start with `csr`, and can only be
accessed in a privileged mode.

- `csrr a0, sstatus` to read `sstatus` and `a0`
- `csrw sstatus, a0` to write `sstatus` to `a0`
- `csrrw a0, mscratch, a0` to swap atomically

| Machine Mode CSR | Supervisor Mode CSR | Purpose in xv6                                                              |
|------------------|---------------------|-----------------------------------------------------------------------------|
| `mstatus`        | `sstatus`           | Tracks CPU status, privilege mode, and interrupt enable bits.               |
| `mepc`           | `sepc`              | Stores the return address after an exception or system call.                |
| `mcause`         | `scause`            | Indicates the reason for a trap, exception, or interrupt.                   |
| `mtvec`          | `stvec`             | Holds the address of the trap handler function.                             |
| `mtval`          | `stval`             | Stores faulting instruction address or memory address in exceptions.        |
| `mscratch`       | `sscratch`          | Temporary storage for traps (e.g., saving registers).                       |
| `mideleg`        | `-`                 | Delegates interrupts from machine mode to supervisor mode.                  |
| `medeleg`        | `-`                 | Delegates exceptions from machine mode to supervisor mode.                  |
| `mhartid`        | `-`                 | Stores the hardware thread (hart) ID, used for multi-core processing.       |
| `mip`            | `sip`               | Pending interrupts (Supervisor Timer Interrupt - `STIP` is used in xv6).    |
| `mie`            | `sie`               | Enables interrupts (Supervisor Timer Interrupt - `STIE` is used in xv6).    |
| `satp`           | `satp`              | Holds the physical address of the page table root, used for virtual memory. |
| `pmpcfg0`        | `-`                 | PMP configuration register (used to control memory access rules).           |
| `pmpaddr0`       | `-`                 | First PMP address register (used to define memory access boundaries).       |

## Traps, Exceptions and Interrupts

In Risc-V, traps occur when user mode code loses control.

### Exceptions

Exceptions are synchronous and generally caused by user code. For
example, syscalls willingly give up control to the kernel, and program
errors in user code traps to the kernel, where it can handle those
faults.

Some program errors include:

- Illegal Instructions
- Alignment Error
- Memory Access/Page Fault

### Interrupts

Interrupts are generally asynchronous and come from outside user code.
They can come from:

- Timers
- Software Interrupts (caused by timer interrupts)
- Devices (UART)

## Special "Registers"

These aren't registers because you can't write to them, but you can read
them to a register:

### Mhartid

`mhartid` contains the core number, and is moved to `tp` during startup.
`cpuid()` returns the value of `tp`, and thus, `mhartid` in xv6.

In user mode, `tp` can be overwritten, but the kernel will restore `tp`
from the stack after a trap, so user mode code can happily write to
`tp`, and the kernel will always have the value of it in supervisor
mode.

### Pmpcfg0 and Pmpaddr0

`pmp` stands for `Physical Memory Protection` and limits access to
physical memory for code in S and M mode.

This is used for secure bootstrapping and VMs.
