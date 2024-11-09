---
title: "The Slab Allocator"
---
## Introduction

The Slab Allocator is an allocator for SunOS 5.4. The allocator notes
that initialization and destruction of objects are generally expensive,
and so caching should be a high priority of the system.

## Object Caching

Object Caching is a technique for dealing with objects that are
frequently allocated and freed. Take a mutex -- `mutex_init()` needs to
be applied once, and then the object can be freed and reallocated
without incurring the cost of `mutex_destroy()` and `mutex_init()`.

The Design of the cache is straightforward:

- Allocating the object:

```c 
if (there's an object in the cache)
  take it (no construction required);
else {
  allocate memory;
  construct the object;
}
```

- Freeing an object:

```c 
Return it to the cache (no destruction required);
```

- To reclaim memory from the cache:

```c 
take objects from the cache;
destroy the objects;
free the underlying memory;
```

An object's constructed state must be initialized only once.

## The Case for Object Caching in the Central Allocator

1. Privately-managed caches cannot handle the tension of an object
   cache, which wants to keep memory, and the allocator, which wants
   that memory back. The cache and the allocator only have local
   knowledge, which prevents optimizations.
2. Since private caches bypass the central allocator, they can't benefit
   from the debugging tools of the allocator, which makes them harder to
   use.
3. Having many instances of the same solution to a common problem
   increases complexity and kernel code size.

## The Object Cache Interface

The interface follows from two observations:

1. Descriptions of objects belong in clients, not in the central
   allocator. The allocator shouldn't know that certain objects are
   useful to cache at compile time, since this is brittle and cannot
   anticipate the needs of clients at runtime, such as device drivers,
   streams modules, and file systems.
2. Memory management policies belong in the central allocator, not the
   clients. The clients want to allocate and free objects quickly,
   nothing else.

Thus, the interface to construct an object cache looks like this:

```c 
struct kmem_cache *kmem_cache_create(
  char *name,
  size_t size,
  int align,
  void (*constructor)(void*, size_t),
  void (*destructor)(void*, size_t)
);
```

This creates a cache of objects, each with a size `size`, aligned on an
`align` boundary. The `name` is for debugging, and `constructor` is a
function that constructs objects in the cache, and `destructor` undoes
that.

Next, clients should need just two simple functions to allocate and free
objects:

To get an object from the cache:

```c 
void *kmem_cache_alloc(
  struct kmem_cache *cp,
  int flags);
```

The first parameter is the cache to retrieve items from, and flags can
be either `KM_SLEEP` or `KM_NOSLEEP`, which indicates whether its
acceptable to wait for memory if none is currently available.

To return an item to the cache:

```c 
void kmem_cache_free(
  struct kmem_cache *cp,
  void* buf);
```

If a cache is no longer needed, the client can destroy it:

```c 
void kmem_cache_destroy(struct kmem_cache *cp);
```

This interface allows us to build a flexible allocator that is ideally
suited to the needs of its clients. It also doesn't require compile time
knowledge of custom allocators, nor does it have to guess what the ideal
cache size is as in adaptive-fit methods.

## An Example

Taking this struct:

```c 
struct foo {
  kmutex_t foo_lock;
  kcondvar_t foo_cv;
  struct bar *foo_barlist;
  int foo_refcnt;
};
```

We would create a constructor like this:

```c 
void foo_constructor(void *buf, int size) {
  struct foo *foo = buf;
  mutex_init(&foo->foo_lock, ...);
  cv_init(&foo->foo_cv, ...);
  foo->foo_refcnt = 0;
  foo->foo_barlist = NULL;
}
```

And a destructor like this:

```c 
void foo_destructor(void *buf, int size) {
  struct foo *foo = buf;
  ASSERT(foo->foo_barlist == NULL);
  ASSERT(foo->foo_refcnt == 0);
  cv_destroy(&foo->foo_cv);
  mutex_destroy(&foo->foo_lock);
}
```

And then to create the cache:

```c 
foo_cache = kmem_cache_create("foo_cache",
sizeof (struct foo), 0,
foo_constructor, foo_destructor);
```

And then to free:

```c 
foo = kmem_cache_alloc(foo_cache, KM_SLEEP);
use foo;
kmem_cache_free(foo_cache, foo);
```

Thus, allocation becomes fast, because the allocator will usually do
nothing more than fetch an already-constructed foo from the cache.

## Caches

We've discussed the frontend of the cache, but there's also a backend:

| Backend         | Frontend         |
|-----------------|------------------|
| kmem_cache_grow | kmem_cache_alloc |
| kmem_cache_reap | kmem_cache_free  |

The grow call gets memory from the VM system, makes objects, and feeds
those items to the cache.

The reap call frees memory from the cache and returns it to the VM.

The slab allocator isn't a monolithic entity, but is rather a loose
confederation of independent caches with no shared state. This allows
them to have per-cache locking instead of the entire heap.

## Slabs 

The slab is the unit of currency in the slab allocator. When the
allocator needs to grow, it acquires an entire slab of objects at once.
When the allocator needs more memory, a slab is freed.

This leads to the following benefits:

1. Reclaiming unused memory is trivial: When the slab's ref count goes
   to zero, the associated pages can be returned to the VM.
2. Allocating and freeing memory are fast, constant-time operations. All
   we need to do is move an object to or from a freelist and updated a
   ref count.
3. Severe fragmentation is unlikely. Because these are very granular
   slabs, there is little external fragmentation. 
4. Internal fragmentation is minimal. Each buffer is exactly the right
   size, so the only wasted space is at the end of the slab. If a slab
   contains n buffers, the internal fragmentation is at most 1/n.

### Slab Layout - Logical

The contents of each slab are managed by a `kmem_slab` data structure,
that maintains the slab's linkage in the cache. 
