---
title: interlude-process-api
---

# Interlude: Process API

Prev:
[the-abstraction-the-process](the-abstraction-the-process.md)
Next:
[mechanism-limited-direct-execution](mechanism-limited-direct-execution.md)

## The fork() System Call

The Fork system call is for creating a new process. It creates a copy of
its parent and then gets its own address space.

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  printf("hello world (pid:%d)\n", (int) getpid());
  int rc = fork();
  if (rc < 0) { // fork failed; exit
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) { // child (new process)
    printf("hello, I am child (pid:%d)\n", (int) getpid());
  } else { // parent goes down this path (main)
    printf("hello, I am parent of %d (pid:%d)\n",
        rc, (int) getpid());
  }
  return 0;
}
```

This prints out:

```sh
prompt> ./p1
hello world (pid:29146)
hello, I am parent of 29147 (pid:29146)
hello, I am child (pid:29147)
prompt>
```

When calling fork, the parent gets the pid of the newly-created child,
whereas the child receives a return code of 0, which allows you to
handle the parent and child's path.

## The wait() System Call

What happens if we want either the parent or child to execute first? Add
a wait() system call.

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  printf("hello world (pid:%d)\n", (int) getpid());
  int rc = fork();
  if (rc < 0) { // fork failed; exit
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) { // child (new process)
    printf("hello, I am child (pid:%d)\n", (int) getpid());
  } else { // parent goes down this path (main)
  int rc_wait = wait(NULL);
  printf("hello, I am parent of %d (rc_wait:%d) (pid:%d)\n",
  rc, rc_wait, (int) getpid());
  }
  return 0;
}
```

## The exec() System Call

You can use `exec()` to run a different program than the parent
process.

```c
include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  printf("hello world (pid:%d)\n", (int) getpid());
  int rc = fork();
  if (rc < 0) { // fork failed; exit
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) { // child (new process)
    printf("hello, I am child (pid:%d)\n", (int) getpid());
    char *myargs[3];
    myargs[0] = strdup("wc"); // program: "wc" (word count)
    myargs[1] = strdup("p3.c"); // argument: file to count
    myargs[2] = NULL; // marks end of array
    execvp(myargs[0], myargs); // runs word count
    printf("this shouldn’t print out");
  } else { // parent goes down this path (main)
    int rc_wait = wait(NULL);
    printf("hello, I am parent of %d (rc_wait:%d) (pid:%d)\n",
  rc, rc_wait, (int) getpid());
  }
  return 0;
}
```

This runs `wc` in an odd way. Exec loads code and static data from that
executable and overwrites its current code segment with that data. Then
it runs that process, transforming itself into that program.

## Why? Motivating the API

With these design decisions, we can easily design a shell.

By separating fork and exec, you can easily create a shell that handles
this command:

`wc p3.c > newfile.txt`

This is done by redirecting the output of the command `wc p3.c` to
newfile.txt by closing stdout and opening newfile.txt.

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  int rc = fork();
  if (rc < 0) { // fork failed; exit
   fprintf(stderr, "fork failed\n");
   exit(1);
  } else if (rc == 0) { // child: redirect standard output to a file
   close(STDOUT_FILENO);
   open("./p4.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);

   // now exec "wc"...
   char *myargs[3];
   myargs[0] = strdup("wc"); // program: "wc" (word count)
   myargs[1] = strdup("p4.c"); // argument: file to count
   myargs[2] = NULL; // marks end of array
   execvp(myargs[0], myargs); // runs word count
  } else { // parent goes down this path (main)
   int rc_wait = wait(NULL);
  }
  return 0;
}
```

## Process Control and Users

Besides fork, exec, and wait, there are other useful commands, like
`kill`, which sends signals to a process. Ctrl-C sends a SIGINT
(interrupt) and Ctrl-Z sends a SIGTSTP (stop) command, pausing the
process to be rerun later with `fg`.

A process can use the `signal()` system call to catch various signals,
and react to those (e.g. cleanup on Ctrl-C).

Because having a process receive signals from multiple users would run
into concurrency issues, we limit the users who can send signals (e.g.
only root and the current user).

## Useful Tools

For example `ps` shows which processes are running. `top` says which
processes are using the most CPU and memory. `kill` and `killall` can
send signals to processes.

Prev:
[the-abstraction-the-process](the-abstraction-the-process.md)
Next:
[mechanism-limited-direct-execution](mechanism-limited-direct-execution.md)
