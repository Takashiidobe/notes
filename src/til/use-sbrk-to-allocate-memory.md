---
title: use-sbrk-to-allocate-memory
---

sbrk to allocate memory

## Use sbrk to adjust the program break

Note: sbrk and brk are used to allocate memory.

These are deprecated (Nowadays mmap is preferred):

These were deprecated in POSIX 1997, and removed in POSIX.1-2001. That
being said, most UNIXes still have them (Linux and Mac, for legacy
compatibility reasons).

Here\'s a possible implementation of sbrk.

```c
static uintptr_t current_break; // Some global variable for your application.
                                // This would probably be properly tracked by the OS for the process
void *sbrk(intptr_t incr)
{
    uintptr_t old_break = current_break;
    current_break += incr;
    return old_break;
}
```

And let\'s use it (note we\'re using the OS\' `sbrk`, defined in
`<unistd.h>`):

```c
#include <stdio.h>
#include <unistd.h>

int main(void) {
  void *curr_address = sbrk(0);
  printf("current heap location: %p\n", curr_address); // our program break

  sbrk(16); // sbrk returns the old break, so this is still where curr_address was.
  void *next_address = sbrk(0);
  printf("current heap location: %p\n", next_address); // curr_address + 16

  sbrk(-16); // sbrk returns the old break, so this is still where curr_address was.
  void *new_address = sbrk(0);
  printf("current heap location: %p\n", new_address); // back to curr_address
}
```

## Use brk to set the program break

Here\'s a possible implementation of brk.

```c
static uintptr_t current_break;

int brk(void* end_data_segment) {
  current_break = end_data_segment;
  return 0;
}
```

To set a pointer:

```c
#include <unistd.h>

int main(void) {
  brk(0); // set current data segment to 0.
}
```

## Caveats

Since a lot of libc functions end up using `sbrk` and `brk` under the
hood, be careful with adjusting the heap with `sbrk` and `brk`. It
might\'ve readjusted or you might\'ve readjusted the pointer for other
calls.
