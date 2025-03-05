# Memory Management

Xv6 handles memory in 4KB pages, and uses a free list to track available
memory.

Memory allocation is done in the `kalloc.c` file. Memory is held in a
free list, which has 4KB pages to dole out for memory allocation.

```c
struct run {
  struct run *next;
};

struct {
  struct spinlock lock;
  struct run *freelist;
} kmem;
```

There's a variable, called `end`, which denotes the first address after
the kernel starts:

```c
extern char end[];
```

There's a function to initialize the allocator by grabbing a lock for
the entire freelist and freeing all of the pages it can access in
memory.

```c
void kinit() {
  initlock(&kmem.lock, "kmem");
  freerange(end, (void*)PHYSTOP);
}
```

`freerange` frees all the pages in a provided range.

```c
void freerange(void *pa_start, void *pa_end) {
  char *p;
  p = (char*)PGROUNDUP((uint64)pa_start);
  for(; p + PGSIZE <= (char*)pa_end; p += PGSIZE)
    kfree(p);
}
```

`kalloc` allocates a page.

1. It locks the free list
2. It then traverses the list, finding the first available page
3. It unlocks the free list
4. It fills the page with 0x05 (junk)
5. and returns the page


```c
void * kalloc(void) {
  struct run *r;

  acquire(&kmem.lock);
  r = kmem.freelist;
  if(r)
    kmem.freelist = r->next;
  release(&kmem.lock);

  if(r)
    memset((char*)r, 5, PGSIZE); // fill with junk
  return (void*)r;
}
```

`kfree` frees a page of memory.

1. It makes sure the address is page aligned
2. It makes sure the address is in the range of start - end
3. Fills the page with 0x01 to detect use-after-free bugs.
4. Locks the memory allocator
5. Adds the page back to the free list by adding it to the front of the
   list
6. releases the free list's lock.

```c
void kfree(void *pa) {
  struct run *r;

  if(((uint64)pa % PGSIZE) != 0 || (char*)pa < end || (uint64)pa >= PHYSTOP)
    panic("kfree");

  // Fill with 1s to catch use-after-free
  memset(pa, 1, PGSIZE);

  r = (struct run*)pa;

  acquire(&kmem.lock);
  r->next = kmem.freelist;
  kmem.freelist = r;
  release(&kmem.lock);
}
```
