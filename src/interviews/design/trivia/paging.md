# Paging

Paging divides the linear address space into fixed-sized pages. The most common size is 4KB, but 2MB and 1GB are also common on x86_64 on linux.

The MMU does translation of a page location to the linear address space.

The Linux kernel uses 4-level page tables:

- Page Global Directory
- Page Upper Directory
- Page Middle Directory
- Page Table Entry

The kernel is allowed to use the top 16-bits, and userspace gets 48-bits.

## Huge Pages

Normally, pages are 4KB in size, as the OS has a lot of applications with smaller memory requirements. The OS can also avoid large scale fragmentation by moving pages around in the background.

Huge Pages allow you to allocate pages for a process with a larger size (2MiB, 1GB). While this may have performance benefits, it might not as well, so be sure to test on your workload if this improves performance before turning it on.

It can also cause memory leaks too, as freed huge pages might be returned to the OS, and then coalesced into another huge page, which can't be given back to the OS, causing increased memory usage and defeating MADV_DONTNEED.

malloc can be set up to use hugetlbs.
