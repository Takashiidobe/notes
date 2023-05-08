# TLB

The TLB is a hardware cache that maps a virtual address to a physical address (This is called content-addressable memory). The TLB can have ~1024 pages in its cache, where it can speed up the OS' requests for memory pages. It is part of the chip's Memory Management Unit (MMU).

It is ~1024 pages. If a lot more pages are required, using huge pages can help with memory fragmentation and cache misses.
