# ARM vs Risc-V

ARM and RISC are both RISC architectures that have different
philosophies which affect their implementation.

ARM uses a load-store design, with 32-bit instructions, 31 general
purpose registers, and separate FP and Vector registers. ARM has
condition codes (NZCV flags) for arithmetic, with corresponding test
instructions. The Thumb instruction set supports 16-bit instructions.

RISC-V has similar 32-bit instructions, with 31 registers and 1 zero
register, and FP registers. There's a compressed extension that supports
16-bit instructions. There are no condition flags in RISC-V.

## ISA

ARM has fixed 32-bit instructions, but this can hurt code size. RISC-V
can mix 16-bit and 32-bit instructions, so binary sizes can become about
20% smaller for the same program.

ARM has many compound instructions, like multiply-add (MADD), as well as
load-pair (LDP) and store-pair (STP) which moves two registers/memory
slots at once. It also supports CBNZ/CBZ (branch if register is
nonzero/zero) and TBZ/TBNZ (test bit and branch) to reduce instruction
count. This can lower binary size, but modern processors can fuse
multiple instruction sequences internally, and execute them at the same
time, so the speed gains are up in the air.

For loads, ARM supports PC-relative addressing and registers offsets
with scaling in loads/stores (for array/struct field access). RISC-V has
loads/stores with a basic register + 12 bits for offset.

Also for ARM, condition codes allow for flags to be set for later
branches. This can be useful for overflow arithmetic, and acting upon
conditions, whereas RISC has no condition flags, so it has to explicitly
check for overflow or tests with registers.

Both ARM and RISC-V should have theoretically similar performance, but
current implementations are more performant on ARM.

For power efficiency, ARM and RISC-V both provide instructions for
entering low power states (WFI/WFE - wait for interrupt/event) and
RISC-V has WFI when in privileged mode. RISC-V has a very weak memory
model, which can let hardware be more efficient when handling memory.
