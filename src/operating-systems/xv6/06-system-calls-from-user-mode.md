# System Calls from user Mode

System calls give up control from user mode code to kernel code in order
to run privileged instructions.

In xv6, there are 21 syscalls, as well as some library functions for
user code, in `ulib.c`.

## System Calls

| System Call | Purpose                                                        |
|-------------|----------------------------------------------------------------|
| `fork`      | Creates a new process (child process).                         |
| `exit`      | Terminates the current process.                                |
| `wait`      | Waits for a child process to finish.                           |
| `pipe`      | Creates a unidirectional pipe for interprocess communication.  |
| `read`      | Reads data from a file descriptor.                             |
| `write`     | Writes data to a file descriptor.                              |
| `close`     | Closes an open file descriptor.                                |
| `kill`      | Sends a signal to terminate a process.                         |
| `exec`      | Replaces the current process with a new program.               |
| `open`      | Opens a file and returns a file descriptor.                    |
| `mknod`     | Creates a special file (device file).                          |
| `unlink`    | Deletes a file.                                                |
| `fstat`     | Retrieves file metadata from a file descriptor.                |
| `link`      | Creates a new directory entry (hard link) to an existing file. |
| `mkdir`     | Creates a new directory.                                       |
| `chdir`     | Changes the current working directory.                         |
| `dup`       | Duplicates an existing file descriptor.                        |
| `getpid`    | Returns the process ID of the calling process.                 |
| `sbrk`      | Increases or decreases the size of the process's heap.         |
| `sleep`     | Puts the calling process to sleep for a specified time.        |
| `uptime`    | Returns the system uptime (ticks since boot).                  |

## ulib.c functions

 | Function  | Purpose                                                             |
 |-----------|---------------------------------------------------------------------|
 | `start`   | Calls `main()` and ensures `exit(0)` is called if `main()` returns. |
 | `strcpy`  | Copies a string from source to destination.                         |
 | `strcmp`  | Compares two strings.                                               |
 | `strlen`  | Returns the length of a string.                                     |
 | `memset`  | Fills a memory area with a constant value.                          |
 | `strchr`  | Finds the first occurrence of a character in a string.              |
 | `gets`    | Reads a line of input from standard input.                          |
 | `stat`    | Retrieves file metadata by opening and calling `fstat`.             |
 | `atoi`    | Converts a string to an integer.                                    |
 | `memmove` | Copies memory, handling overlapping regions safely.                 |
 | `memcmp`  | Compares two memory areas.                                          |
 | `memcpy`  | Copies memory from source to destination (calls `memmove`).         |


## Initcode

There's code that starts up a user process, by setting up init, and
argv, in `initcode.S`.

```asm
#include "syscall.h"

# exec(init, argv)
.globl start
start:
        la a0, init
        la a1, argv
        li a7, SYS_exec
        ecall

# for(;;) exit();
exit:
        li a7, SYS_exit
        ecall
        jal exit

# char init[] = "/init\0";
init:
  .string "/init\0"

# char *argv[] = { init, 0 };
.p2align 2
argv:
  .quad init
  .quad 0
```
