# What is Madvise?

Madvise is a system call used to give directions to the kernel about an address range.

```c
#include <sys/mman.h>

int madvise(void *addr, size_t length, int advice);
```

Some advice can include:

- `MADV_HUGEPAGE` (enable huge pages for the range)
- `MADV_SEQUENTIAL` (expect sequential accesses in the future)
- `MADV_WILLNEED` (expect access in the future)
- `MADV_DONTNEED` (don't expect access in the future)
- `MADV_FREE` (the application no longer requires the page(s), free them).
