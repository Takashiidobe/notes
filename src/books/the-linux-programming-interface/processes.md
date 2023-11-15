---
title: processes
---

# Processes

Prev:
[file-io-further-details](file-io-further-details.md) Next: [memory-allocation](memory-allocation.md)

## Processes and Programs

A process is an instance of an executing program. A program is a file containing information that describes how to construct a process at run time. Programs have information that describes how to construct a process at run time like:

- Binary format identification: Each program file includes a metadata header that describes the format of the executable file. The current format is ELF on linux.
- Machine language instructions: The instructions the process will run.
- Program entry-point address: The location of the instruction at which execution of the program should commence.
- Data: The constants (like variables and literals) that the program uses.
- Symbol and relocation tables: The location and name of functions used by the program, used for debugging and run-time symbol resolution.
- Shared library and dynamic-linking information: the shared libraries the program needs to use at run time and the linker used to load those libraries.

A program can be used to construct many processes.

## Process ID and Parent Process ID

Each process has a process ID, a PID, which uniquely identifies the process on the system. `getpid` returns the process ID of the calling process.

```c
#include <unistd.h>

pid_t getpid(void); // Always successfully returns process ID of called
```

The Linux kernel limits process IDs to being less than or equal to 32,767.

To get the parent process id, `getppid` can be used.

```c
#include <unistd.h>
pid_t getppid(void); // Always successfully returns process ID of parent of caller
```

## Memory Layout of a Process

The memory layout of a process has many segments, or parts.

- The **text segment** contains the machine-language instruction of the program run by the process. This is read-only.
- The **initialized data segment** contains global and static variables that are initialized.
- The **uninitialized data segment** contains global and static variables that are not explicitly initialized.
- The **stack** is a dynamically growing and shrinking segment containing stack frames, which contain functions, variables, arguments, and the return value.
- The **heap** where programs can be dynamically allocated at run time.

## Virtual Memory Management

Linux uses virtual memory to layout processes, which looks like this:

![Process Memory Layout](../../img/process-memory-layout.png)

A virtual memory scheme splits the memory used by each program into smaller, fixed-size units called pages. RAM is divided into series of page frames of the same size.

The kernel maintains a page table for each process, which contains the location of each page in the processes' virtual address space.

![Virtual Memory Page Table](../../img/virtual-memory-page-table.png)

If a process tries to access memory without a corresponding page-table entry, it receives a `SIGSEGV` signal.

## The Stack and Stack Frames

The stack grows and shrinks as functions are called and return. Each process has its own stack with the following:

- **Function arguments and local variables**: Automatic variables and function arguments are allocated and deallocated.
- **Call Linkage information**: Each function has certain CPU registers, like the program counter which points to the next instruction to be executed.

## Command-Line Arguments (argc, argv)

Every C program must have a function called main. The first argument is `int argc`, which indicates how many arguments there are. `char* argv[]` is an array of pointers to the command line arguments provided. The first, `argv[0]` is normally the name of the program itself. This allows for a nice trick, used by some utilities, like `busybox`, to run different programs based on the name the program is called.

## Environment List

Each process maintains an array of strings called the environment list, which holds strings of form `name=value`. Each name is referred to as an environment variable. When a new process is created, it inherits a copy of its parent's environment.

To add a value to the environment, the `export` command can be used:

`export SHELL=/bin/bash`

Or, to affect a single program:

`NAME=value ./program`

As well, `setenv` in the shell can be used.

To print the current environment list, `printenv` can be used.

To access the current environment in a program, you can iterate through `environ`.

```c
extern char **environ;
int main(int argc, char *argv[]) {
    char **ep;
    for (ep = environ; *ep != NULL; ep++)
    puts(*ep);
    exit(EXIT_SUCCESS);
}
```

To get a specific environment variable, use `getenv`.

```c
#include <stdlib.h>
char *getenv(const char *name); // Returns pointer to (value) string, or NULL if no such variable
```

To set a specific environment variable, use `setenv`.

```c
#include <stdlib.h>
int setenv(const char *name, const char *value, int overwrite); // Returns 0 on success, or –1 on err
```

To unset a variable, use `unsetenv`.

```c
#include <stdlib.h>
int unsetenv(const char *name); // Returns 0 on success, or –1 on error
```

To clear the entire environment, use `clearenv`.

```c
#define _BSD_SOURCE /* Or: #define _SVID_SOURCE */
#include <stdlib.h>
int clearenv(void)
Returns 0 on success, or a nonzero on error
```


## Performing a Nonlocal Goto: `setjmp` and `longjmp`

`setjmp` and `longjmp` are libc functions that perform a nonlocal goto. C's `goto` does not allow jumping from the current function to another function. Imagine there is a function that errors out, and the code to handle the error is in another function that is up the stack. Without non-local goto, you'd have to jump through all those functions and go to the error handling function, and hope that the call stack doesn't terminate before then.

```c
#include <setjmp.h>
int setjmp(jmp_buf env); // Returns 0 on initial call, nonzero on return via longjmp()
void longjmp(jmp_buf env, int val);
```

`setjmp` establishes a target for a later jump performed by `longjmp`.

`longjmp` and `setjmp` make code worse to read but also are optimized away by compilers, which can lead to bugs. Avoid their use.


Prev:
[file-io-further-details](file-io-further-details.md) Next: [memory-allocation](memory-allocation.md)
