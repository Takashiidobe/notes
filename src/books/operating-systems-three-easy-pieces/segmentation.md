---
title: segmentation
---

# Segmentation

Prev:
[mechanism-address-translation](mechanism-address-translation.md)
Next:
[free-space-management](free-space-management.md)

In this chapter, we explore the free space between the stack and the
heap which is wasteful for most processes. 

## Segmentation: Generalized Base/Bounds 

To solve this problem, segmentation was created, where the code, heap
and stack might be placed in different locations in memory.

Instead of putting them contiguously in memory, you can put a processes'
code, stack and heap anywhere in physical memory.

If you index out of bounds, you get a segmentation fault.

## Which Segment Are We Referring To?

Since we have three code segments to access into, we need to know if
we're indexing into the code, stack, or heap. 

To do so, we could take an explicit approach, where we set the first two
bits.

00 = code 
01 = stack 
11 = heap
10 = invalid

As shown, this wastes one state (there are 4 states but only 3
locations). To make only a one-bit signal, we could stick the code and
heap together.

As well, if we want to grow a segment, but we only have 16KB pointers,
we can't point to memory outside of the segment. Tough luck.

We can also use an implicit approach, where if the address was generated
from the program counter, we know it is a code instruction, if its based
off the stack, the stack, otherwise, look at the heap.

## What About the Stack

The stack grows backwards in our example. We also need to know what
direction the segments grow in (forwards or backwards) to index into it
properly.

## Support for Sharing 

As well, system designers realized they could make memory usage more
efficient by sharing code in memory. 

To do this, we need some protection bits from the hardware, where by
adding a few bits to each segment, we can find out whether or not we can
read, write, or execute to memory.

| Segment | Base | Size | Direction | Protection   |
|---------|------|------|-----------|--------------|
| Code    | 32k  | 2K   | 1         | Read-Execute |
| Heap    | 34k  | 3k   | 1         | Read-Write   |
| Stack   | 28k  | 2k   | 0         | Read-Write   |

In the code segment, since it is read-execute, if we try to write to it,
we'll get a segmentation fault.

Otherwise, we can read and write to and from the heap, so that's fine.

## Fine-grained vs. Coarse-grained Segmentation 

We're dividing memory into coarse-grained chunks, but earlier OSes, like
multics used fine-grained segmentation, with many segments, that the OS
could manage better. 

## OS Support 

Pieces of the address space are relocated into physical memory as the
system runs, and thus savings of physical memory is achieved during this
translation. 

When the process context switches, it needs to keep bounds of its
segment registers. 

When the process requests too much heap memory, malloc() and friends has
to move the heap segment, using the sbrk() or mmap() system call, where
the OS will update the segment size register to the bigger size and move
memory around.

This allows us to relax the constraint that all processes have the same
amount of memory, and the segments can be in different locations
altogether.

This does create external fragmentation, and requires compaction.

There are many ways to optimize free memory, like best-fit, worst-fit,
first-fit, and the buddy algorithm.

Prev:
[mechanism-address-translation](mechanism-address-translation.md)
Next:
[free-space-management](free-space-management.md)
