---
title: "Measuring Memory"
---

# Measuring Memory

Prev: [measuring-cpus](measuring-cpus.md)
Next: [cpu-and-memory-interaction](cpu-and-memory-interaction.md)

Today's chips have lots of cache, 3 levels (L1I, L1D, L2, L3), and DRAM
that is connected to the chip.

L3 is generally shared between all cores of a chip, and L1 and L2 are
per core.

Accessing something in L1 cache may take around a cycle, or 0.3 nsec.

Accessing main memory can be 50-100 cycles, which is must slower.

Prev: [measuring-cpus](measuring-cpus.md)
Next: [cpu-and-memory-interaction](cpu-and-memory-interaction.md)
