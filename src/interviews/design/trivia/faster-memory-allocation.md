# Faster Memory Allocation

To make memory allocation faster, one could allocate all the memory they want up front, and then never free it (a bump allocator). This works fine if you have enough free memory to never have to reuse memory. If you need to reuse memory, this scheme no longer works.

To make memory allocation faster, the problem is that malloc/free have to lock memory accesses in one application (as there could be multiple threads asking for memory at the same time). Thus, mallocing requires a mutex lock/unlock at the very least.

To make it faster, one could swap out a memory allocator that is better suited for the workflow (jemalloc) or use a more scalable memory allocator (hoard).

Hoard has a global heap, where it delegates to malloc/free, but it gives each thread its own heap. Memory is reclaimed to and from that local heap, and when the local heap requires more memory, it requests it from the hoard allocator. When the hoard allocator runs out of memory, it can ask malloc/free for more. This can be done smartly in the background when the hoard allocator is running low on memory, so there's no runtime cost for threads (unless they ask for a large amount of memory at once).

There's also buddy allocators and slab allocation for faster memory allocation.
