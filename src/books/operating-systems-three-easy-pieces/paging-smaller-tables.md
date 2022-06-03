---
title: paging-smaller-tables
---

# Paging: Smaller Tables

Prev:
[paging-faster-translations-tlbs](paging-faster-translations-tlbs.md)
Next:
[beyond-physical-memory-mechanisms](beyond-physical-memory-mechanisms.md)

Remember that each page table is about 4 MB in size for a 32-bit
machine.

## Simple Solution: Bigger Pages

If pages become 4 MB, pages would have an 20-bit VPN and a 12-bit
offset.

Bigger pages also lead to more internal fragmentation.

## Hybrid Approach: Paging and Segments

Instead, combine paging and segments to come up with a hybrid strategy.
Instead of wasting all of the virtual address space, have pages map to
real pages on physical memory. This lowers the waste that comes with a
typical paging approach.

As well, think about having a single page table for the entire address
space of the process -- one for the code, stack, and heap.

As well, to have segmentation support faults, the hardware should
support three base/bounds pairs, for the code, stack, and heap.

This saves lots of space, and allows for segmentation.

## Multi-level Page Tables

Another way is to create a multi-level page table, which chops up the
linear page table into a tree like data structure. Each page that's
unused isn't allocated, and points to a null pointer.

There's another data structure that's used to keep track of pages, which
contains an entry, a valid bit, and a page frame number.

This tree like structure uses memory more efficiently, but adds a level
of indirection through the page directory, slowing down the whole
structure. As well, this adds complexity.

## Inverted Page Tables

To save more space, inverted page tables exist as well. Instead of
having many page tables, one per process, there is just one page table
that contains each page of the system, and the physical page it maps to.

## Swapping the Page Tables to Disk

Some systems support swapping page tables in kernel virtual memory,
allowing the system to swap these page tables to disk when memory
pressure gets a little tight.

Prev:
[paging-faster-translations-tlbs](paging-faster-translations-tlbs.md)
Next:
[beyond-physical-memory-mechanisms](beyond-physical-memory-mechanisms.md)
