---
title: "A Microarchitecture Case Study"
---

# A Microarchitecture Case Study

Prev: [microprocessors-platforms-and-systems](microprocessors-platforms-and-systems.md)
Next: [the-k6-3d-microarchitecture](the-k6-3d-microarchitecture.md)

The K6 microprocessor is an AMD chip that implements x86, and is a CISC
on RISC microprocessor.

The CISC is the x86 assembly, and the chip interprets those CISC
instructions as "RISC86" instructions internally.

It has a two-level dynamic branch predictor that can predict over 95% of
branches taken correctly.

It employs a 6-stage pipeline, which lets it run through multiple
instructions per cycle.

The RISC86 ops are divided into the following types, some which take one
or two cycles.

| Op Type                     | Mnemonic |
|-----------------------------|----------|
| Memory load                 | LdOps    |
| Memory Store                | StOps    |
| Integer                     | IntOps   |
| Floating Point              | FrOps    |
| Branch Condition Evaluation | BrOps    |
| Special operations          | SpecOps  |

x86 instructions are executed as these Risc86 ops.

Cache coherency is maintained through the MESI protocol.

Superscalar processors have a set of execution units that operate in
parallel:

1. Store Unit (SU)
2. Load Unit (LU)
3. Register Unit X (RUX)
4. Register Unit Y (RUY)
5. Floating Point Unit (FPU)
6. Branch Resolving Unit (BRU)

The decoders place four Ops in the scheduler's centralized buffer each
cycle. The scheduler then reads the ops, and then based on dependencies
and resource constraints,

Register renaming allows the hardware to achieve greater parallelism by
mapping the "high-level" CISC assembly into some RISC ops that do not
have data hazards.

For example, take something like this:

```asm
r1 = m[1024]     ;read the value in memory location 1024
r1 = r1 + 2      ;add two to the value
m[1032] = r1     ;save the result to location 1032
r1 = m[2048]     ;read value in 2048
r1 = r1 + 4      ;add 4
m[2056] = r1     ;save it to 2056
```

The first 3 lines are independent from the last 3 lines, but the
processor is blocked by a data transfer (`m[1032] = r1`), so it cannot
execute the two blocks out of order.

What the CPU can do is rewrite code like this:

```asm
r1 = m[1024]
r1 = r1 + 2
m[1032] = r1
r2 = m[2048]
r2 = r2 + 4
m[2056] = r2
```

Where it creates a new register, allowing for both blocks to be executed
in parallel. This works because there are far more physical registers on
a CPU than the high level assembly has (16 general purpose registers in
x86_64 vs. 192 on a Zen 3 computer, for example). Also, logical
registers are different from the physical registers on the chip.

With enough registers, we could hypothetically do SSA analysis on simple
code, but that's normally left to your compiler.

Some bits, called the predecode bits, provide a pointer to the first
bytes of the next instructions, to allow quick jumping between
instructions.

Some instructions that create a single micro-op are decoded by the short
decoder, and longer ones by the other decoders. The K6 only features two
decoders, whereas Intel P2s have three decoders.

Each op is executed in four as a FIFO queue.

A reorder buffer is a staging area where processors that support
speculative and out-of-order execution typically have operations which
have completed execution but have not been committed.

If a Branch conditional op is correctly predicted, its results are
committed. If it isn't then the ops that follow the branch are flushed
and the instructions corresponding to the other branch are rerun.

Prev: [microprocessors-platforms-and-systems](microprocessors-platforms-and-systems.md)
Next: [the-k6-3d-microarchitecture](the-k6-3d-microarchitecture.md)
