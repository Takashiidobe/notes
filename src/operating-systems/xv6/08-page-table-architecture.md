# Page Table Architecture

Page tables are used to translate physical memory addresses to virtual ones.

In Risc-V, the `satp` register (Supervisor Address Translation and
Protection) points to the active page table.

Virtual memory translation is always on in S and U mode, but not in M
mode.

At startup, in M mode, `satp` is set to 0, but during initialization,
it's a valid page table.

## Kernel & User Page Tables

### Kernel Page Tables

The kernel page table is shared across all cores, and maps physical to
virtual memory one-to-one, except for a few mmappings.

It also maps memory-mapped I/O (MMIO) devices.

### User Page Tables

Each user process has its own page table, for isolation

## Levels

Risc-V supports 3 page table schemas:

1. SV32 = 2 level
2. SV39 = 3 level
3. SV48 = 4 level

Xv6 uses SV39, so it has 3-level paging.
x86_64 uses 48-bit virtual addresses, and also has 4-level paging, for
comparison.

## Page Table Walk & TLB

With 3-level paging, every memory access (load/store/fetch) requires a
3-level page table lookup.

Thus, the TLB (Translation Lookaside Buffer) caches recently used page
table entries.
However, the kernel must flush the TLB when switching page tables, with
`sfence.vma`, so context switches can be expensive for memory accesses
too.

## Virtual Address Breakdown in SV39

Since virtual addresses are 39 bits:

- 12 bits for the byte offsets within a page, since 2^12 = 4KB.
- 9 bits for the level 0 index. So there are up to 512 root nodes.
- 9 bits for the level 1 index. For up to 512 second level nodes.
- 9 bits for the level 2 index. For up to 512 third level nodes.

This only uses 33 bits -- the last 6 bits are ignored, but you could
imagine an optimization for transparent huge pages and use those last 6
bits, to support 256KB pages, or move around the page sizes to have
larger pages.

## Page Table Entries (PTEs)

Page Table Entries include some flags for the page:

- V (Valid), if the entry is valid
- R/W/X - Read/Write/Execute Permissions
- U (User-Accessible) if user mode can use the page
- Physical Page Number (PPN) the physical address of the mapped page.

## Final Address Translation

The physical address is constructed using with:

- The 44-bit Physical Page Number (PPN) from PTE.
- The 12-bit Page Offset from the virtual address.
- Total physical address size: 56 bits (supports 2^56 bytes of memory).
