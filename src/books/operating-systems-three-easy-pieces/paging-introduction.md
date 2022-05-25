---
title: paging-introduction
---

# Paging: Introduction

Prev:
[free-space-management](free-space-management.md)
Next:
[paging-faster-translations-tlbs](paging-faster-translations-tlbs.md)

Segmentation involves chopping things up into variable-sized pieces, but
this leads to fragmentation.

Paging chops up memory into fixed-sized pieces. This combats
fragmentation, at the cost of using more memory. 

## A Simple Example and Overview

Imagine a simple 64 byte address space split into 16 byte pages.

{
  0: 0,
  1: 16,
  2: 32,
  3: 48,
}

This allows us to support a simple scheme for free-space management: if
the OS keeps a free list of all open pages, it can allocate 4 of the
first pages it finds.

The OS generally also keeps a per-process data structure known as a page
table, which stores address translations for each of the virtual pages
in the address space.

We can then translate the virtual address that the process has to a
physical address on memory by splitting memory into two pieces: the
virtual page number, and the offset within the page.

For our 64 byte example, we need 6 bits to indicate the location of
memory we want to index into:

The first two bits signal the page (0-3) to index into, and 4 bits are
sufficient for indexing into the byte (0-16).

Let's take an example in assembly:

```asm 
movl 21, %eax
```

21 is `010101`, which is `01` for the VPN and `0101` for the byte.
`01` is the first page, and `0101` is the 5th byte, so this refers to
the first page's 5th byte (byte 21). This can then be translated by the
OS to a physical page.

## Where Are Page Tables Stored?

Page tables can get extremely large -- assuming a 32-bit address space
with 4KB pages, this splits the address space into a 20-bit VPN and a
12-bit offset (4KB). 

Assuming that the OS needs to handle 4 bytes per page table entry, every
page table will be 4MB by default, and if there's 100 processes running,
the OS needs 400MB of memory for address translations.

It's even worse for a 64-bit, which would take gigabytes.

Instead, we store page tables in memory somewhere.

## What's Actually in the Page Table

Assuming a linear page table (an array), we need a valid bit to indicate
whether the particular translation is valid. If it is valid, it is
accessed, otherwise, a call to the OS is generated which may segfault
(if the memory is invalid according to the OS) or the OS will return the
page if it was swapped to disk.

We also have protection bits (2 bits) which indicate whether the page
can be read from, written to, or executed from.

A present bit indicates whether this page is in physical memory or on
disk (swapped).

A dirty bit is also common, indicating whether the bit has been modified
since it has been brought into memory. 

A reference bit can be used to track whether a page has been accessed,
and is useful in determining popular pages to either keep in memory or
swap to disk.

## Paging: Also Too Slow

With page tables in memory, we know that they're too large. But they can
also be too slow.

Take address 21, and translate the address into the correct physical
address (e.g. 117). 

Next, the system must find the page table for the currently running
process -- it indexes into the page-table base register and shifts into
it to find the physical address.

The hardware then picks out the VPN bits, then finds the correct virtual
address, and page, and then indexes into the page, and issues a read to
the OS to fetch the correct page. 

```c 
// Extract the VPN from the virtual address
VPN = (VirtualAddress & VPN_MASK) >> SHIFT

// Form the address of the page-table entry (PTE)
PTEAddr = PTBR + (VPN * sizeof(PTE))

// Fetch the PTE
PTE = AccessMemory(PTEAddr)

// Check if process can access the page
if (PTE.Valid == False)
  RaiseException(SEGMENTATION_FAULT)
else if (CanAccess(PTE.ProtectBits) == False)
  RaiseException(PROTECTION_FAULT)
else
  // Access is OK: form physical address and fetch it
  offset = VirtualAddress & OFFSET_MASK
  PhysAddr = (PTE.PFN << PFN_SHIFT) | offset
  Register = AccessMemory(PhysAddr)
```

This is a factor of two too slow, which isn't good enough for us.

Prev:
[free-space-management](free-space-management.md)
Next:
[paging-faster-translations-tlbs](paging-faster-translations-tlbs.md)
