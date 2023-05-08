# Named Pipes

Named pipes can be created with `mkfifo` or `mknod p`. They are used for IPC - One side can write to it, and the other one can read from it sequentially.

This can be used for interprocess communication without having to `fork`, `execve`, and `wait()`.
