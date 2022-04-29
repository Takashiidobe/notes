/*
   2. Write a program that opens a file (with the open() system call) and then
   calls fork() to create a new process. Can both the child and parent ac-
   cess the file descriptor returned by open()? What happens when they are
   writing to the file concurrently, i.e., at the same time?
   */
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>

// fprintf is thread safe, so output can't corrupt the file.
// they can be arbitrarily ordered, though

// open, write, read aren't thread safe so they can cause segfaults.

int main(int argc, char *argv[]) {
  int result = open("p2.output", O_CREAT | O_RDWR | O_TRUNC, 0666);
  if (result < 0) {
    fprintf(stderr, "opening p2.output failed\n");
    exit(1);
  }
  int rc = fork();
  if (rc < 0) { // fork failed; exit
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) { // child (new process)
    // try to write to the file
    write(result, "hello", 5);
  } else { // parent goes down this path (main)
    write(result, "world", 5);
  }

  char buf[12];
  read(result, buf, 12);
  write(STDOUT_FILENO, buf, 12);

  return 0;
}
