---
title: paging-faster-translations-tlbs
---

: Faster Translations (TLBs)"

# Paging: Faster Translations (TLBs)

Prev:
[paging-introduction](paging-introduction.md)
Next:
[paging-smaller-tables](paging-smaller-tables.md)

We found out in previous chapters that Paging is too slow and memory
intensive. In this chapter, we'll tackle improving the speed of paging. 

To do so, we'll use a translation-lookaside buffer (TLB), which is a
part of the chip's memory-management unit (MMU), a cache of popular
virtual-to-physical address translations. When checking a memory
reference, the hardware checks the TLB, then goes to the slower page
table.

```c 
VPN = (VirtualAddress & VPN_MASK) >> SHIFT
(Success, TlbEntry) = TLB_Lookup(VPN)
if (Success == True) // TLB Hit
  if (CanAccess(TlbEntry.ProtectBits) == True)
    Offset = VirtualAddress & OFFSET_MASK
    PhysAddr = (TlbEntry.PFN << SHIFT) | Offset
    Register = AccessMemory(PhysAddr)
  else
    RaiseException(PROTECTION_FAULT)
else // TLB Miss
  PTEAddr = PTBR + (VPN * sizeof(PTE))
  PTE = AccessMemory(PTEAddr)
  if (PTE.Valid == False)
    RaiseException(SEGMENTATION_FAULT)
  else if (CanAccess(PTE.ProtectBits) == False)
    RaiseException(PROTECTION_FAULT)
  else
    TLB_Insert(VPN, PTE.PFN, PTE.ProtectBits)
    RetryInstruction()
```

## TLB Basic Algorithm

The basic algorithm is outlined above: the OS checks if the VPN is in
the TLB, and if so, accesses memory. If not, it goes to slower memory.
This allows for faster paging.

## Example: Accessing An Array

Imagine a simple TLB with a 16-byte cache, and looping over integers
(4-bytes) as a page access:

```c 
int sum = 0;
for (i = 0; i < 10; i++) {
  sum += a[i];
}
```

The TLB can cache every page it encounters (spatial locality).

Thus, our cache rate looks like this:

a[0] a[1] a[2]
miss, hit, hit
a[3] a[4] a[5] a[6]
miss, hit, hit, hit
a[7] a[8] a[9] 
miss, hit, hit

The TLB always misses on the start of a new page, but caches the rest of
the page, so we get about 70% caching here.

Since we used a 16-byte page here, we got 70% caching, but with a 4KB
page, we'd have 90% caching (just one cache miss to load the rest of the
addresses into memory).

Spatial (loading nearby addresses into cache) and temporal (addresses
accessed once are likely to be accessed again) make caches performant.

The OS might handle TLB lookup like this:

```c 
VPN = (VirtualAddress & VPN_MASK) >> SHIFT
(Success, TlbEntry) = TLB_Lookup(VPN)
if (Success == True) // TLB Hit
  if (CanAccess(TlbEntry.ProtectBits) == True)
    Offset = VirtualAddress & OFFSET_MASK
    PhysAddr = (TlbEntry.PFN << SHIFT) | Offset
    Register = AccessMemory(PhysAddr)
  else
    RaiseException(PROTECTION_FAULT)
else // TLB Miss
  RaiseException(TLB_MISS)
```

## Who Handles the TLB Miss?

Either the hardware or the software can handle the TLB miss. The
hardware can handle it by knowing where the page tables are located in
memory (with a page-table base register) and then handling it itself.
The other way is through software, where on a cache miss, the hardware
raises an exception and the OS interrupts the current process, and
escalates to kernel mode.

### RISC vs. CISC

RISC (Reduced Instruction sets) vs. CISC (Complex Instruction sets) was
a debate in the 80s -- CISC is meant for directly programming in
assembly (making higher level primitives) whereas RISC is meant for
being a compiler target for higher level languages, so RISC ripped out
the bloat and made smaller primitives that run faster.

In the end though, x86 and other CISC architectures took notes and added
early pipeline stages that transformed complex instructions into
micro-instructions like RISC and the debate died down.

## TLB Contents: What's In There?

The TLB contains entries which might look like this:

`VPN | PFN | other bits`

The other bits include:

A valid bit shows whether the entry is valid, protection bits determine
how a page can be accessed, there could be an address-space identifier,
and a dirty bit.

## TLB Issue: Context Switches

What happens when one process has filled up the TLB with page accesses
for its own process and is about to be context switched out?

The TLB caches are no longer valid, so they have to be changed somehow.
One way is to flush the TLB, emptying the cache -- this works, but has
severe runtime impact.

Another way to reduce overhead is to provide an address space identifier
(ASID) in the TLB. We can add one byte to the TLB entry for this to
identify the process that the TLB entry corresponds to.

## Issue: Replacement Policy

If we choose the ASID approach, we need to find a way to replace TLB
entries. Two strategies include LRU and random replacement. These work
better in different ways -- LRU has large overhead and performs well in
the average case, but random has little overhead and has no edge cases
where it performs poorly, in exchange of having fewer edge cases.

## A Real TLB Entry

The MIPS TLB supports 32-bit address space with a 4KB page size. Thus,
this should have a 20-bit VPN and a 12-bit offset. However, user
addresses can only have half the memory, so there are only 19 bits for
the VPN. The VPN translates to up to a 24-bit frame number, and can
support systems with up to 64GB of main memory.

The MIPS system supports a global bit (G) that is used for pages which
are globally-shared among processes. If this bit is set, the ASID is
ignored. There's an 8-bit ASID, 3 coherence bits, a dirty bit, a valid
bit, and a page mask field which supports different page sizes. 

Prev:
[paging-introduction](paging-introduction.md)
Next:
[paging-smaller-tables](paging-smaller-tables.md)
