---
title: beyond-physical-memory-mechanisms
---

# Beyond Physical Memory: Mechanisms

Prev:
[paging-smaller-tables](paging-smaller-tables.md)
Next:
[beyond-physical-memory-policies](beyond-physical-memory-policies.md)

We previously assumed that address space fits in main memory. Now, lets
make it work on disk.

The addition of swap space allows the OS to support the illusion that
there's a large virtual memory for concurrently running processes.

## Swap space

We reserve some space on disk to store pages that hold processes. The OS
needs to remember the disk address of a given page.

## The Present Bit

Since we can have pages on disk as well as in memory, we'll also add
a bit to a page that states whether or not the page is present in memory
-- if not, the OS invokes a page-fault handler, which goes to the OS to
find the given page on swap space on disk.

## The Page Fault

Page-Fault handlers are normally run in software -- this is because
hardware doesn't necessarily know where in the Page table entry
to find the address, and I/O requests are slow anyway, so there's not
much performance loss -- as well, the OS is well equipped to handle
those requests and interleave them efficiently.

## What if Memory is Full?

If memory is full, we need to find a policy to kick a page out to main
memory -- but of course, that has a performance penalty -- if the wrong
page is sent to main memory, a program could run close to 100,000 times
slower. Therefore, its important to have a good policy, which is
discussed in the next chapter.

## Page Fault Control Flow

The control flow looks like this: If the page is present in valid, the
TLB can find the page, and retry the instruction.

If the page is not present in physical memory, then the OS goes to main
memory, after being notified by a page fault handler.

Otherwise, the OS waits for main memory to fetch the page and then gets
a TLB cache hit to service the request.

## When Replacements Really Occur

The OS does bookkeeping in the background -- it has two markers, a high
watermark and a low watermark -- the low watermark is when the OS
decides to free memory until it hits the high watermark. This is done by
the swap daemon or page daemon.

This allows for improved performance, since it allows for grouping of
work and batching during a better time for the hardware, and allows
software to act like its working faster.

Prev:
[paging-smaller-tables](paging-smaller-tables.md)
Next:
[beyond-physical-memory-policies](beyond-physical-memory-policies.md)
