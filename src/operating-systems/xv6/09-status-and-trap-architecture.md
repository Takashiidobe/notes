# Status and Trap Architecture

Two kinds of Traps:

1. Exceptions
2. Interrupts

- System call (`ecall`)
- Program Error
    - Illegal Instruction, Alignment Error
- Device Interrupts
    - Happens in Supervisor or User mode

## Trap Handling

- `stvec` is a CSR that contains the address of handler code.
- `kernelvec` handles traps in supervisor mode
- `uservec` handles traps in user mode

## Supervisor Mode Trapping

- `sstatus` is the CSR that holds the status of interrupts in supervisor mode.
    - `sie` is a bit that holds whether or not interrupts are enabled/disabled.
    - `spie` is previous interrupts enabled.
    - `spp` is previous privilege level the interrupt happened in, with
      0 = User and 1 = Supervisor.

The kernel sets `sie` to prevent interrupts to the core.

When a trap occurs, if interrupts are disabled, the trap will wait until
later for processing. If interrupts are enabled, then the handler will
handle it right away.

The hardware then stores registers to use in the trap:

1. `pc` is saved in `sepc`.
2. `stvec` is saved in `pc`.
3. `scause` gets register info about the interrupt:
    - 1 = Timer interrupt
    - 8 = System call
    - 9 = External Device
    - anything else = program exception
4. `stval` stores other info about the fault
    - the address or instruction of the trap
    - a faulting memory address during page faults
    - if an illegal instruction, the failing instruction
5. `sstatus.SPP` is assigned the previous mode (0 = user, 1 = supervisor)
6. `sstatus.SPIE` is assigned `sstatus.SIE` (previous interrupts
   enabled)
7. `sstatus.SIE` is set to 0 to disable interrupts
8. `mode` is set to supervisor.

Then the trap executes, and returns to the handler. The handler then
restores context back to the running code.

Once the supervisor is done, it calls `sret` to do the following:

1. `sstatus.SIE` is assigned `sstatus.SPIE`
2. `mode` is assigned `sstatus.SPP`
3. `pc` is assigned `sepc`

To undo the storage done.

## Machine Mode Trapping

Similar to supervisor mode, except for `mpp`

- `mstatus` is the CSR that holds the status of interrupts in machine mode.
    - `mie` is a bit that holds whether or not interrupts are enabled/disabled.
    - `mpie` is previous interrupts enabled.
    - `mpp` is previous privilege level the interrupt happened in, with
      00 = User and 01 = Supervisor, and 11 = machine mode

The only interrupt is for the timer. Every other interrupt goes to
supervisor mode.

Interrupts are always enabled in machine mode

And on an timer interrupt:
- Force a software interrupt to supervisor mode
- re-enable interrupts
- returns to the interrupted code

`mtvec` contains the address of the handler

The hardware also stores registers from the interrupted code:

1. `pc` is saved in `mepc`.
2. `mtvec` is saved in `pc`.
3. `mcause` and `mtval` are ignored
4. `mstatus.SPP` is assigned the previous mode (00 = user, 01 = supervisor, 11 = machine)
5. `mstatus.SPIE` is assigned `mstatus.SIE` (previous interrupts
   enabled)
6. `sstatus.SIE` is set to 0 to disable interrupts
7. `mode` is set to machine.

The handler will then cause an interrupt at the supervisor level, and
then `mret` to restore registers

1. `mstatus.SIE` is assigned `mstatus.SPIE`
2. `mode` is assigned `mstatus.SPP`
3. `pc` is assigned `mepc`

## Status values

`seie` indicates whether device interrupts are on in supervisor mode
`stie` indicates whether time interrupts are on in supervisor mode
`ssie` indicates whether software interrupts are on in supervisor mode
`sip` indicates whether or not an interrupt is pending, 0 = no
interrupt.

## Hardware Delegation Registers

- `medeleg` is for delegating exceptions to supervisor mode
- `mideleg` is for delegating interrupts to supervisor mode.

### Medeleg

`medeleg` has a bunch of bytes:

- `STORE/AMO` page fault
- `Load` page fault
- `Instruction` page fault
- `ecall` m-mode
- `ecall` s-mode
- `ecall` u-mode
- `STORE/AMO` access fault
- `STORE/AMO` misaligned
- `Load` access fault
- `Load` misaligned
- `breakpoint`
- `illegal instruction`
- `Instr. access fault`
- `Inst. Misaligned`

`medeleg` is set with `csrw medeleg, $val`

### Mideleg

`mideleg` stores interrupt info:

- `Device interrupt` in m-mode
- `Device interrupt` in s-mode
- `Timer interrupt` in m-mode
- `Timer interrupt` in s-mode
- `Software interrupt` in m-mode
- `Software interrupt` in s-mode
