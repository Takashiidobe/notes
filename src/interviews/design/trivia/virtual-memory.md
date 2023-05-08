# Virtual Memory

- Virtual Memory allows multiple processes to coexist on a single computer without trampling over each other's memory. This can be done for security reasons (processes shouldn't be able to read/write other processes memory, as that is insecure) and also for convenience (it's much easier to program to having the entire computer to yourself, and having the OS reject assumptions when that's not the case).
- The BSS, code, and data segments are allocated to the process on startup, whereas the heap addresses are translated, making heap allocations cost a page fault, whereas stack allocations do not. Each thread gets its own stack. When the thread exits, the stack is reclaimed, and when the application exits, heap memory is reclaimed.
