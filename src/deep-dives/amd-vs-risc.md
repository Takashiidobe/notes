# AMD vs RISC-V

AMD64 is a CISC with variable length instructions, from 1 to 15 bytes,
and with support for multi-operation instructions. Thus, the decoder
must be complicated to figure out instruction boundaries and decode them
into internal operations. It also turns them

RISC-V is a RISC, where all instructions are 4 bytes, which allows for a
simple decoder pipeline. RISC-V uses a simple 5-stage pipeline for
simple chips: fetch, decode, execute, memory access, write-back. These
can be combined with deeper pipelines or superscalar dispatch.

## Pipeline Depth

Intel is known for its deep pipeline designs (30 stages in the Prescott
Pentiums) but it comes with a huge downside, which is a mispredict
flushes all branches. The AMD Athlon or K8 opted for shorter pipelines,
around 12-15 stages.

For RISC cores, with the out-of-order BOOMv3 cores, the pipeline is 10
stages. This lowers the mispredict penalty (about 12 cycles), which can
be painful for AMD64 designs.

## Out of Order Execution

x86 and RISC both have out of order support:

For x86, because instructions are broken into micro-ops, and executed
out of order, designs have to have mechanisms for high instruction-level
parallelism, by allowing independent micro-ops to execute as much in
parallel as much as possible. However this is complicated by the data
dependencies created, especially with flags and memory orderings.

RISC is much more friendly to out of order execution. There are no
flags, so there's no need to care for specific instructions having to go
in a strict order.

## Memory Ordering

x86 has a strong memory ordering model -- called Total Store Order. All
processors see memory operations in nearly consistent order. That means
that most memory loads and stores have to go in program order. The only
exception is stores can be done before loads as long as the store does
not affect a load that would come before it.

This allows for easier concurrent programming, at the cost of
performance in the hardware.

RISC-V has a weak memory model. The hardware is allowed to reorder
memory operations, so a store followed by a load can be seen out of
order unless fenced explicitly. This is similar to ARM or the DEC Alpha.
This weak memory model allows for more flexibility to reorder memory
accesses. RISC-V also has a Zsto extension to make it execute in TSO
mode like x86 if required.

## Concurrency Support

x86 supports a long list of atomics and locking instructions. In x86, a
load or store to a single location are atomic. The `LOCK` prefix can be
applied to memory instructions to make them atomic read-modify write
operations. There's also `XCHG` which is atomic and acts as a memory
barrier, `CMPXCHG` for compare and swap, and `XADD` which is fetch and
add. x86 also supports fence instructions, and there's also `PAUSE` to
deschedule the executing thread.

RISC-V supports LR/SC (Load-Reserved/Store-Conditional) instructions and
Atomic Memory Operations. ARM has LR/SC, where a load and store fail
only succeed if no other write interleaved between the two. There's also
fences, pause, and wfi, but these are more minimalist.

## Compiler Optimizations

x86 has 16 integer registers, whereas RISC has 31. x86, being a CISC,
can do a lot more work in one instruction, like `mov rax, [rbx + rcx *4
+ 8]` to load a value from an array in one instruction, where that would
  take a few instructions in RISC-V.

For instruction scheduling, compilers also have to keep in mind the
amount of micro-ops an instruction may cost. Thus, compilers tend to
favor simpler instructions, and avoid complex ones which could cause
pipeline stalls, so compilers might choose to XOR a register instead of
moving a constant into a register, since that could cause pipeline
stalls because of memory ordering requirements.

For RISC-V, this is less complex, there might be nops inserted or
instructions reordered, with the cost of making branch elimination
harder than say on x86.

As well, same as in ARM, because RISC-V supports lots of extensions,
compilers have to know which extensions are available. Most x86-64
instructions are more homogeneous, so the compiler has less choice to
make here.

## Branch Prediction Strategies

Branch prediction is more refined in x86 chips. AMD's Zen 2 introduced a
Tagged Geometric branch predictor, for high accuracy, and Intel has had
multi-level predictors. They also allow for fusing compare and branch
instructions to predict and execute.

For virtual functions, both can support indirect branch predictors, and
x86 supports heuristics for branch hints.
