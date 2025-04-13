# Intel vs AMD

Intel and AMD both use the x86-64 instruction set. However, they have
different philosophies for micro-ops, instruction fetch/decode, pipeline
depth, out of order execution, and register renaming.

## Historical Differences

Historically, Intel and AMD had different strategies -- Intel chose for
deep pipelines to enable high clock speeds. Netburst had 20+ pipeline
stages, which meant real world practice suffered in code (there's a
branch every 6 lines of code or so). AMD preferred smaller pipelines.
Intel eventually returned to shorter pipelines with the Pentium Pro, and
AMD's bulldozer which pursued throughput by sharing resources between
core pairs. AMD had a clustered multi-threading (CMT) design, where a
core would have two threads sharing a front-end in a module. Intel
preferred SMT (Simultaneous Multi-Threading) to use each core.

Intel later preferred large out of order window sizes for execution, at
the cost of power and complexity. However, AMD merged into Intel's
philosophy with Zen cores which supported wide decode pipelines, deep
speculation, SMT, and Out of Order Execution.

Intel has recently introduced Performance and Efficiency cores with
Alder Lake chips, to take on the mobile market. The Zen 4 and 5 also
took on the same design.

## Micro-ops and Instruction Decoding

Intel has historically had wider decoders, until the Zen times. Decoders
decoded 4 instructions per cycle, and each SMT thread had its own
decoder.

Both architectures support micro-op fusion, for say loads and stores.

Both architectures now support a micro-op cache, which stores micro-ops
for later execution, if fetching and decoding is faster.

## Pipeline Depth

AMD used to have far thinner pipelines (12 vs ~20) but now both have
converged to ~5GHz clock speeds, powerful branch predictors, and 19
stage pipelines.

Nowadays both companies also use ML branch predictors, keeping pipelines
full by reducing mispredicts.

The current AMD and Intel architectures have wide pipelines for
execution -- retiring 8-10 micro-ops per cycle.

## Out of Order Execution and Scheduling

To support Out of Order execution, many pieces of hardware need to work
together, including the Reorder Buffer (ROB), issue queues (schedulers),
register files, and load/store queues.

### Reorder Buffers

The reorder buffer (ROB) and in-flight window takes concurrently executed
instructions and enforces in-order retirement, to match the
architecture's memory ordering. Intel has pursued large ROBs, which take
up more silicon area and power. AMD has been more modest with 256 entry
ROBs, whereas Intels has been past 512 for a while now.

### Scheduling

Intel has unified scheduling, where the Reservation Station (RS) holds
micro-ops of all types waiting to be executed. In AMD's Zen, the
scheduler is split into an integer scheduler and an FP scheduler, which
can lower throughput if one side is not in use, at the cost of simpler
scheduling.

### Register Files and Renaming

Modern CPUs have hundreds of registers, currently around 300. This means
that the ISA registers are renamed to avoid false dependencies, at the
cost of a more complicated register file and register renaming logic.

This allows for optimizations like move elimination
(register-to-register moves simply update rename mappings).

### Memory Orderings

Both have the same load/store buffers for out of order memory access,
and support speculative memory disambiguation, where loads can bypass
stores if no conflict is detected. The load/store buffers allow for
multiple loads and stores per cycle, in Zen 3 2 loads + 2 stores are
possible in a cycle using two store-data paths. However, Intel's
implementation allowed a speculatively executed load to forward data to
dependent micro-ops before a permission check, leaving them vulnerable
to meltdown.

### Multithreading

Nowadays Intel and AMD both support Hyper-Threading (SMT) where two
hardware threads can share one physical core. Each cycle, the processor
can choose micro-ops from either thread to issue.

## Architectural Components

### Cache

Intel has generally used inclusive caches, whereas AMD supports
exclusive caches. Inclusive caches simplify snoop logic (if data is not
in L3, it's not in L2), since lower level caches include higher level
cache content by default. Exclusive caches have a more complicated cache
coherence protocol, but have more space as well.

### Memory Controllers

Both have similar memory-controllers on die for fast memory.

### Chip Design

Intel has favored monolithic dies, where all cores and cache are on one
silicon piece, whereas AMD has preferred chiplets, where smaller chips
communicate. This has a bit of increased latency but more scalability
and yield. Nowadays both favor the chiplet approach.

### Heterogeneous Cores

Intel supports Performance and Efficiency cores, whereas Zen is all
homogeneous. This allows for potential optimizations in the
mobile/laptop area.
