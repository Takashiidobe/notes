---
pdf_url: "[[A Malloc Tutorial.pdf]]"
author:
  - Marwan Burelle
title: A Malloc Tutorial
date created: Sunday, July 20th 2025, 10:54:07 am
date modified: Sunday, July 20th 2025, 12:23:02 pm
---

# A Malloc Tutorial

Malloc allocates memory in C:

1. It takes a parameter, `size`, and this must be at least the number of bytes requested.
2. The pointer returned points to the space.
3. No other call to malloc can allocate memory within this space while it is in use and has not been freed.
4. the pointer should be able to be resized and freed.

```c
void* malloc(size_t size);
```

## The Heap, `brk` and `sbrk`

The heap (free memory) of a process has a start, and a `break`, which is where the mapped region of memory ends. Afterwards, there is the unmapped region, which ends with `rlimit`, which is not in use.

We can use two system calls to help out with this:

```c
int brk(const void *addr);
void* sbrk (intptr_t incr);
```

`brk` sets the break value to `addr`, and changes allocated space. `sbrk` takes in `incr` as a parameter, and either increments or decrements the process break by that amount.

`sbrk(0)` returns the current program break.

`mmap` and `munmap` can be used to free memory as well.

## Dummy Malloc

The first malloc is a bump allocator. When we get a call for some amount of memory, we bump the space by that many bytes. We cannot realloc or free, so this is a big downside, but it is as fast as possible.

```c
void *malloc(size_t size) {
	void *p = sbrk(0); // get program break
	if (sbrk(size) == -1) { return NULL; } // alloc failed
	return p; // return the start of the allocation
}
```

## Organizing the Heap

To be able to reallocate and free, we need bookkeeping information. Let's keep metadata before the data, such as the pointer, length, and then the next free block (a free list).

```c
struct s_block {
	size_t size; // size of allocation
	struct s_block* next; // next free block
	bool free; // bool for free/not
}
```

## A First Fit Malloc

This implementation is of a malloc that traverses the chunk list and when a suitable free block is found, we use that.

We just make sure to align to the pointer size, and then find a chunk:

If we find no suitable blocks, we use sbrk to increment the heap.

If there's a suitable block that's too big, we can also split the block into two.


