---
title: "Storage Allocation"
---

# Storage Allocation

Prev: [measurement-and-timing](measurement-and-timing.md)
Next: [parallel-storage-allocation](parallel-storage-allocation.md)

## Stack Allocation

You can allocate memory using a stack. However, you can only free the last allocated memory.

Thus, allocating and freeing take $O(1)$ time, and there's no fragmentation, but unusued memory can take up a lot of the stack, if there's one allocation that can't be freed, any memory allocated before then cannot be freed.

## Heap Allocation

To allocate on the heap, use malloc/free, or new/delete. Failure to free memory allocated by the programmer can result in a memory leak, dangling pointers, and double freeing.

One way to allocate memory on the heap is to use a free list (a linked list of fixed size blocks that point to each other one by one.

```
used -> free -> used -> free.
```

- Allocating and freeing takes $O(1)$ time.
- Good temporal locality
- Poor spatial locality due to pointer chasing. Also makes caching worse.

To mitigate external fragmentation, keep a free list per disk page. Allocate from the free list for the fullest page. If a page becoems empty, page it out in the background.

## Variable Size Heap Allocation

Binned Free Lists:

Have a set of $O(log{}N)$ free lists that each hold blocks of a power of 2.
When you allocate memory, allocate the next largest chunk that can serve the request.

If you run out of memory on a free list, then split a block in the next larger non empty bin into blocks and distribute the pieces.

At worst case, given the size of memory used is $M$, the Binned Free List will consume $O(M log{}M)$ storage.

As well, it has $O(log log{}M)$ reads and writes, because it needs to find the size of the binned free list to use with binary search.

Coalescing (Buddy Trees, like in Linux) where similarly freed allocations can be coalesced into a larger block are no better in theory, but can be better in practice, since heap storage is deallocated in a stack like fashion.

## Garbage Collection with Reference Counting

Use reference counting, which contains a count of how many times it's being used. When that count hits 0, the item can be freed.

You can't allow pointer arithmetic, since this casts pointers to ints and vice-versa, making it difficult on C/C++ programs.

Reference counting can't be used on cyclical data structures (they'll never be freed) unless you explicitly free one node, which most languages won't let you do.

## Mark and Sweep Garbage Collection

Start off with some root node of the program, BFS through all the nodes. These are all the "live" nodes. Any node in memory that isn't in this graph is freeable. The sweep phase will take care of that.

## Copying Garbage Collection

Start out with an allocation to the heap, and when it fills up the entire allocation, double its size and copy the items over, freeing the old buffer. This is like how a vector allocates memory.

Prev: [measurement-and-timing](measurement-and-timing.md)
Next: [parallel-storage-allocation](parallel-storage-allocation.md)
