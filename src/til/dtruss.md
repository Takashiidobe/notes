---
title: dtruss
---

# Dtruss

Dtruss allows you to trace the system calls made by an executable. On
mac os, you\'ll need to install it with `brew install dtruss`.

You will need root permissions:

```sh
sudo dtruss $(executable_to_analyze)
```

A program like this:

```c
#include <stdio.h>

int main(void) { printf("This is 10: %d\n", 10); }
```

Would print this to the console.

```sh
SYSCALL(args)       = return
This is 10: 10
open("/dev/dtracehelper\0", 0x2, 0xFFFFFFFFE4EC4CE0)         = 3 0
ioctl(0x3, 0x80086804, 0x7FFEE4EC4BF0)       = 0 0
close(0x3)       = 0 0
mprotect(0x10AD3E000, 0x4000, 0x1)       = 0 0
access("/AppleInternal/XBS/.isChrooted\0", 0x0, 0x0)         = -1 Err#2
bsdthread_register(0x7FFF6CD5CB7C, 0x7FFF6CD5CB68, 0x2000)       = 1073742047 0
sysctlbyname(kern.bootargs, 0xD, 0x7FFEE4EC3DC0, 0x7FFEE4EC3DB0, 0x0)        = 0 0
issetugid(0x0, 0x0, 0x0)         = 0 0
ioctl(0x2, 0x4004667A, 0x7FFEE4EC4104)       = 0 0
mprotect(0x10AD4E000, 0x1000, 0x0)       = 0 0
mprotect(0x10AD53000, 0x1000, 0x0)       = 0 0
mprotect(0x10AD54000, 0x1000, 0x0)       = 0 0
mprotect(0x10AD59000, 0x1000, 0x0)       = 0 0
mprotect(0x10AD4C000, 0x90, 0x1)         = 0 0
mprotect(0x10AD5A000, 0x1000, 0x1)       = 0 0
mprotect(0x10AD4C000, 0x90, 0x3)         = 0 0
mprotect(0x10AD4C000, 0x90, 0x1)         = 0 0
getentropy(0x7FFEE4EC3630, 0x20, 0x0)        = 0 0
getentropy(0x7FFEE4EC3680, 0x40, 0x0)        = 0 0
getpid(0x0, 0x0, 0x0)        = 22320 0
stat64("/AppleInternal\0", 0x7FFEE4EC4230, 0x0)      = -1 Err#2
csops_audittoken(0x5730, 0x7, 0x7FFEE4EC3D80)        = -1 Err#22
proc_info(0x2, 0x5730, 0xD)      = 64 0
csops_audittoken(0x5730, 0x7, 0x7FFEE4EC3600)        = -1 Err#22
getrlimit(0x1008, 0x7FFEE4EC5560, 0x0)       = 0 0
fstat64(0x1, 0x7FFEE4EC5548, 0x0)        = 0 0
ioctl(0x1, 0x4004667A, 0x7FFEE4EC5594)       = 0 0
write_nocancel(0x1, "This is 10: 10\n\0", 0xF)       = 15 0
```
