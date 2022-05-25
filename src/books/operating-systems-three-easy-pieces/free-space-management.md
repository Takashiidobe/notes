---
title: free-space-management
---

# Free-Space Management

Prev: [segmentation](segmentation.md) Next:
[paging-introduction](paging-introduction.md)

This chapter focuses on free-space management, using segmentation to
implement virtual memory. 

Segmentation with virtual memory management can lead to external
fragmentation -- free space gets chopped into little pieces of different
sizes.

## Assumptions 

1. We assume we have a malloc like function: `void* malloc(size_t
   size)`.
2. we use a free list to track memory. 
3. We are concerned with external fragmentation. 
4. No compaction of free space is possible (since userspace owns the
   memory, not us).
5. The allocator manages a contiguous region of bytes.

## Low-level Mechanisms

Assume the following heap:

| free | used | free |
|------|------|------|
| 0    | 10   | 20   |

The list would like this:

Head -> { addr: 0, len: 10 } -> { addr: 20, len: 10 } -> NULL

Assume we have a request for 1 byte of memory. Then we'll take a free
chunk of memory, and split it into two, one that fills the request and
keeps the remainder:

Head -> { addr: 0, len: 10 } -> { addr: 21, len: 9 } -> NULL

Let's say our user frees 10 bytes of memory, which can be merged with
another segment:

Head -> { addr: 10, len: 10 } -> { addr: 0, len: 10 } -> { addr: 20, len
10} -> NULL

We can merge this:

Head -> { addr: 0, len: 30 } -> NULL

### Tracking The Size of Allocated Regions

To track the size of the region being freed, generally memory allocated
has a header tucked away before the given memory.

This might look like this:

```c 
typedef struct {
  int size;
  int magic;
} header_t;
```

The size contains the size of the pointer, and magic is some random
number that makes sure that we're freeing the correct segment in memory.

When we want to figure out where the header begins, we use some pointer
arithmetic:

```c 
void free(header_t * ptr) {
  header_t *hptr = ptr--;
  assert(hptr->magic == 1234567); // make sure we have the right pointer
}
```

### Embedding a Free List

We need to embed a free list into our heap as well:

```c 
// free list
typedef struct __node_t {
  int size;
  struct __node_t *next;
} node_t;

// mmap the heap 
node_t *head = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
head->size = 4096 - sizeof(node_t);
head->next = NULL;
```

Then, when allocating memory, we split the remaining memory in two and
allocate a header for each node before the allocation, and return memory
to the user.

Finally, on free requests, we can coalesce the heap if they have
contiguous addresses.

### Growing the Heap 

You can also grow the heap using `sbrk` when the heap runs out of space.

## Basic Strategies

Some strategies to counter fragmentation follow:

### Best Fit 

Search through the free list and find chunks of free memory that are as
big or bigger than the requested size. Then find the smallest one that
suffices.

This is efficient (always finds the smallest block) but time intensive
(always takes one pass through the free list).

### Worst Fit

Find the largest chunk that suffices and split it into two. 

This is questionable because it has large fragmentation and takes one
pass.

### First Fit 

First fit always returns the first block that works:

This is fast, but causes fragmentation at the beginning of the list.
This is however good for coalescing, reducing fragmentation. 

### Next Fit

Next fit keeps an extra pointer to the location where the list was
looking last. This can help with reducing fragmentation as well. 

## Other Approaches

There are some other approaches that improve memory allocation: 

### Segregated Lists

If you know that an application might allocate a lot of one type of
memory, you can keep a separate list just for objects of that size, and
forward other requests to a more general memory allocator.

### The Slab Allocator

The slab allocator is one way of doing this -- when the kernel boots up,
it allocates object caches that are split into free lists. 

When a cache runs low on free space, it requests slabs of memory from
a general memory allocator. Likewise, when the reference counts of the
objects within a given slab all go to zero, the general allocator can
reclaim them from the specialized allocator.

### Buddy Allocation 

The buddy allocator system uses a large space of 2^N memory. Then, when
a request is made, the search for free space recursively divides free
space by two until a block that is just big enough is found. Then, that
block is returned to the user. 

When the block is freed, the allocator checks to see if its buddy is
also free. If so, it coalesces the blocks into one.

Prev: [segmentation](segmentation.md) Next:
[paging-introduction](paging-introduction.md)
