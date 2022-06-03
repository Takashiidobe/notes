---
title: complete-virtual-memory-systems
---

# Complete Virtual Memory Systems

Prev:
[beyond-physical-memory-policies](beyond-physical-memory-policies.md)
Next:
[summary-dialogue-on-memory-virtualization](summary-dialogue-on-memory-virtualization.md)

This chapter covers the VAX/VMS operating system, as well as Linux.

## VAX/VMS Virtual Memory

The VAX-11 minicomputer was introduced in the 1970s by DEC.

### Memory Management Hardware

The VAX-11 provided a 32-bit virtual address space per process, divided
into 512-byte pages. It used a 23-bit VPN with a 9-bit offset, with two
upper bits used to differentiate the segment the page was in, mixing in
paging and segmentation.

In the first half of process space, the code and heap grow downward,
whereas the stack grows upwards.

The OS designers lowered memory usage by segmenting the user space in
two, with no page-table space needed for the unused portion of the
address, and by placing user page tables in virtual memory, allowing the
OS to swap it to disk if needed, at the cost of complicated virtual
addressing.

### A Real Address Space

The VAX/VMS copied kernel code into user space, which made it easier
for the OS to handle writes to certain pointers from user space.

### Page Replacement

The VAX had no reference bit, so there was no way to figure out which
pages were active. They were also concerned about certain programs
hogging all the memory, which LRU doesn't consider.

They used segmented FIFO, which involved having three FIFO queues -- one
for pages, one for clean pages, and one for dirty pages. If a page was
to be flushed to disk, it would either be put at the end of the clean
pages or dirty pages. If the OS needs a clean page, it would look at the
clean pages. This also allowed the OS to batch together writes to disk
on the global dirty list.

### Other Neat Tricks

The VMS also supported demand zeroing of pages. If a page was requested
by the OS, it would fetch a clean page from its free-list quickly (that
wasn't zeroed out). When the process wants to read or write to it, that
page is zeroed out (for security reasons -- it would be bad to read
another processes' memory).

As well, Copy-On-Write was popularized by the VAX OS. Let's say you want
to copy a page from one address to another -- instead of copying the
page, you can map the page (point a reference to it). If a process wants
to write to it, the mapped page is copied, but this makes reads
responsive and uses less memory as well. This optimization makes fork
and exec work properly, because without copy on write semantics, exec
would be extremely wasteful.

## The Linux Virtual Memory Systems

The Linux Address space has a divider at about 3/4 the way down, where
the kernel stores logical memory, as well as virtual memory. Fetching
logical memory is governed by the system call `kmalloc`, and the virtual
address allocation is governed by a different call, `vmalloc`.

### Page Table Structure

In x86, page table structures have 16-bits unused, with the bottom 12
bits used directly, and the middle 36 bits to take part in the
translation.

### Large Page Support

x86 supports 4 KB pages, even 2 MB and 1 GB pages. This made TLB
translations much more performant (up to 10% in some programs) and
lowered cache saturation in the TLB in some cases.

Linux introduced huge pages incrementally -- where mmap() or shmget()
were allowed to pass in new flags to ask for these huge pages.
Eventually transparent huge page support was added, where the OS had
logic added to it to sometimes allocate huge pages if needed.

### The Page Cache

The Linux page cache is unified, keeping pages from three sources:

1. memory-mapped files
2. file data and metadata from devices
3. anonymous memory.

These are kept in a page cache hash table, allowing for quick lookups of
data.

The page cache tracks clean and dirty pages, where dirty pages are
written to backing store, and clean pages are reallocated.

Linux uses a 2Q replacement policy to determine which pages to kick out.

This is done by splitting the list into two, and having an inactive list
and an active list -- new pages are added to the inactive list, and then
if accessed again, added to the active list. Periodically, linux sweeps
out the inactive list, and demotes active pages to inactive, and uses
clock replacement to emulate LRU. This algorithm has the advantage that
it doesn't fall prey to LRU's worst case performance during a linear
sweep.

### Security and Buffer Overflows

In the era of networked computers, protecting against buffer overflows
are extremely important -- they can lead to privilege escalation.

AMD introduced an NX bit (no-execute) that prevents execution from any
page which has this bit set. Unfortunately, that's not enough -- there's
a form called `return-oriented programming`, where malicious code can
overwrite the stack such that a return address points to a desired
malicious instruction and return instruction, to execute arbitrary code.

Address space layout randomization (ASLR) was also crafted, to make the
OS put the code, stack, and heap in random locations.

```c
./a.out
code location: 0x1012faee0
stack location: 0x7ffeee90855c
heap location: 0x7ff0e7c05aa0
./a.out
code location: 0x10758dee0
stack location: 0x7ffee867555c
heap location: 0x7ff77d405aa0
./a.out
code location: 0x106dedee0
stack location: 0x7ffee8e1555c
heap location: 0x7fe602405aa0
```

Even the kernel uses ASLR, -- its called KASLR (kernel ASLR).

### Other Security Problems: Meltdown And Spectre

Meltdown and spectre used branch prediction in processors to read memory
from other processes, since speculative execution leaves traces of
memory usage after use. One fix was Kernel Page Table Isolation, which
requires switching to the kernel to read kernel data, which costs
performance in exchange for security.

Prev:
[beyond-physical-memory-policies](beyond-physical-memory-policies.md)
Next:
[summary-dialogue-on-memory-virtualization](summary-dialogue-on-memory-virtualization.md)
