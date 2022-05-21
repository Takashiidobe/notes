---
title: interlude-memory-api
---

# Interlude: Memory API


Prev:
[the-abstraction-address-spaces](the-abstraction-address-spaces.md)
Next:
[mechanism-address-translation](mechanism-address-translation.md)

## Types of Memory

In C, there are two types of memory: stack memory (automatic memory) where
allocations and deallocations are managed by the compiler, and heap
memory, where all allocations and deallocations are handled by you.

```c 
#include <stdlib.h>

int x = 5; // automatic memory
int* y = malloc(sizeof(int)); // heap memory
*y = 5; 
```

## The malloc() Call

Malloc requires an argument, the size of the block of memory you want.
This returns a `void *` pointer, which is returned for you to cast.


## The free() Call

Once you malloc memory, you must free it, otherwise this will cause a
memory leak. 

## Common Errors 

### Forgetting to Allocate Memory

```c 
char *src = "hello";
char *dst; // oops! unallocated
strcpy(dst, src); // segfault and die
```

### Not Allocating enough memory

```c 
char *src = "hello";
char *dst = (char *) malloc(strlen(src)); // too small!
strcpy(dst, src); // work properly
```

### Forgetting to Free Memory 

### Freeing Memory Before you are Done with It 

### Freeing Memory Repeatedly 

### Calling Free() Incorrectly
