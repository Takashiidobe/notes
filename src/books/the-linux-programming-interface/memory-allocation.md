---
title: memory-allocation
---

# Memory Allocation

Prev: [processes](processes.md) Next: [users-and-groups](users-and-groups.md)

## Allocating Memory on the Heap

A process can allocate memory by increasing the size of the heap. This is normally done with the C library functions like `malloc`, but at a lower level, the `brk` and `sbrk` system calls can be used.

### Adjusting the Program Break: `brk` and `sbrk`

Resizing the heap is done by telling the kernel to adjust its idea of where the program break is.

`brk` and `sbrk` look like the following:

```c
#include <unistd.h>

int brk(void *end_data_segment); // Returns 0 on success, or –1 on error
void *sbrk(intptr_t increment); // returns the previous program break on success, or (void *) -1 on error
void *sbrk(0); // this returns the current data segment
```

Attempting to set the program break below its initial value will probably lead to a segfault when trying to access data outside the new program break.

To get the current segment, you can use `sbrk(0)`. `sbrk(-num)` will decrease heap memory, and `sbrk(+num)` will increase heap memory.

`brk(void* num)` will set the data segment to that location.

Memory requested by these calls are not initialized yet, on first access, the kernel will allocate the pages.

### Allocating Memory on the Heap: `malloc` and `free`

Malloc and free have certain advantages over `brk` and `sbrk`.

- in the C standard library
- thread-safe
- simpler, less error prone interface

Malloc allocates `size` bytes from the heap and returns a pointer to the newly allocated block of memory:

```c
#include <stdlib.h>

void *malloc(size_t size); // Returns pointer to allocated memory on success, or NULL on error
```

`malloc(0)` returns a small piece of memory. If malloc could not allocate memory, then `malloc` returns `NULL` and sets `errno` to the error that occurred.

`free` is used to return memory to the kernel.

```c
#include <stdlib.h>
void free(void *ptr); // frees the memory pointed to at ptr
```

It should only be used for memory allocated by `malloc` and friends.

`free` in glibc doesn't lower the program break, but instead it readds the block of memory to a list of free blocks that are reused by malloc and friends.

This is used to lower the amount of calls to `sbrk`.

### To `free` or not to `free`

Since all terminating processes return their memory to the OS, some programs may not free memory (compilers do this, only allocating memory and then erroring out if they can't allocate enough memory). Most programs shouldn't omit calls to free.

### Implementation of `malloc` and `free`

Malloc needs to find a way to free the right amount of memory when a block is passed to it. To do so, the length of the block is placed before the pointer returned to the caller. Thus, free can read the length of the block and add the block to the free list.

Accessing a pointer out of bounds and then changing it could overwrite the length of another memory block, causing a segfault. To avoid this, some rules:

- Only touch bytes inside the block allocated.
- free allocated memory only once.
- only free memory from malloc and friends.
- free memory as soon as possible after use.

### Tools and libraries for malloc debugging

- `mtrace` and `muntrace` allow tracing of memory allocation calls on and off. When `mtrace` is called, it checks the value of the `MALLOC_TRACE` environment variable, and writes calls to malloc to the file indicated by `MALLOC_TRACE`.
- `mcheck` and `mprobe` allow a program to perform consistency checks on blocks of allocated memory.
- `MALLOC_CHECK_` is an environment variable which can be set to various values to respond to memory allocation errors.
    - 0: ignore errors
    - 1: print diagnostic errors to stderr
    - 2: call `abort` to terminate the program.

### Controlling and monitoring the malloc package

glibc has some nonstandard functions that can be used to monitor and control allocation of memory by functions in malloc.

- `mallopt` can be used to set various parameters that control the algorithm used by `malloc`, like the amount of free space required before calling `sbrk`, or the upper limit of block sizes allocated from the heap.
- `mallinfo` returns various statistics about memory allocated by `malloc`.

### Other Methods of Allocating Memory on the Heap

Some other ways of allocating memory include `calloc` and `realloc`:

```c
#include <stdlib.h>
void *calloc(size_t numitems, size_t size); // Returns pointer to allocated memory on success, or NULL on error
```

`calloc` also initializes the allocated memory to 0.

`realloc` is used to resize a block of memory previously allocated by `malloc` and friends.

```c
#include <stdlib.h>
void *realloc(void *ptr, size_t size); // Returns pointer to allocated memory on success, or NULL on error
```

On success, `realloc` returns a pointer to the location of the resized block. Since `realloc` may move memory locations pointed to by `ptr`, `ptr` shouldn't be used after being passed to `realloc`.

### Allocating aligned memory: `memalign` and `posix_memalign`

`memalign` and `posix_memalign` are used to allocate memory starting at an address aligned at a specified power of two boundary.

`memalign` allocates `size` bytes aligned to a multiple of boundary, which must be a power of two.

```c
#include <malloc.h>
void *memalign(size_t boundary, size_t size); // Returns pointer to allocated memory on success, or NULL on error
```

Some implementations of unix have `posix_memalign`, which is aligned to a multiple of `alignment`, a power of two multiple. Memory is returned in `memptr`.

```c
#include <stdlib.h>
int posix_memalign(void **memptr, size_t alignment, size_t size); //
```

## Allocating Memory on the Stack: `alloca`

```c
#include <alloca.h>
void *alloca(size_t size); // Returns pointer to allocated block of memory
```

`alloca` can be used to increase the stack space. It's not used often, but it can be used in conjuction with `longjmp` and `siglongjmp` to perform a nonlocal goto from a signal handler, with the intent of trying to surface errors.

Prev: [processes](processes.md) Next: [users-and-groups](users-and-groups.md)
