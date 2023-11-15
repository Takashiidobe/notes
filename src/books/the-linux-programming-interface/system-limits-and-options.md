---
title: system-limits-and-options
---

# System Limits and Options

Prev: [times-and-dates](times-and-dates.md) Next: [retrieving-system-and-process-information](retrieving-system-and-process-information.md)

Unix implementations must provide limits on system features and resources, like:

- How many files can a process keep open at one time?
- Does the system have realtime signals?
- What is the largest value for a variable?
- How big of an argument list can a program have?
- How long can a pathname be?

Some values should be determined at compile time and some at runtime. For the runtime cases, `sysconf`, `pathconf`, and `fpathconf` can be used to check for implementation limits and options.

## System Limits



## Retrieving System Limits (and Options) at Run Time

To retrieve limits, use `sysconf`.

```c
#include <unistd.h>
long sysconf(int name); // Returns value of limit specified by name, or –1 if limit is indeterminate or an error occurred
```



## Retrieving File-Related Limits (and Options) at Run Time

For file related limits, `pathconf` and `fpathconf` can be used:

```c
#include <unistd.h>
long pathconf(const char *pathname, int name);
long fpathconf(int fd, int name); // Both return value of limit specified by name, or –1 if limit is indeterminate or an error occurred
```



## Indeterminate Limits

## System Options

Prev: [times-and-dates](times-and-dates.md) Next: [retrieving-system-and-process-information](retrieving-system-and-process-information.md)
