# What is mmap?

`mmap` is a system call that creates a new mapping in the virtual address space of the calling process at `fd`.

```c
#include <sys/mman.h>

void *mmap(void *addr, size_t length, int prot, int flags,
           int fd, off_t offset);
```

The protection flags include:

PROT_EXEC
- Pages may be executed.

PROT_READ
- Pages may be read.

PROT_WRITE
- Pages may be written.

PROT_NONE
- Pages may not be accessed.

some interesting flags:

`MAP_ANONYMOUS`: The mapping is not backed by a file.
`MAP_FIXED_NOREPLACE`: Put the mapping at the location provided by `addr`, but dont overwrite any existing mappings.
`MAP_HUGE_2MB MAP_HUGE_1GB`: Map 2MB or 1GB huge pages. You may map different page sizes by bitshifting `MAP_HUGE_SHIFT`.
