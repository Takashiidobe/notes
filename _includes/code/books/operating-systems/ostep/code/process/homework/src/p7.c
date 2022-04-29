#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

// if you close stdout in the parent process, then the child can't open stdout.
// if you close stdout in the child process, the parent can still print.

int main(int argc, char *argv[]) {
  int rc = fork();
  if (rc < 0) { // fork failed; exit
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) { // child
    // closes STDOUT in child
    close(STDOUT_FILENO);
    // of course you can't print to stdout in the child.
    printf("Hello, stdout has been closed!\n");
  } else { // parent goes down this path (main)
    printf("Parent finished\n");
  }
  return 0;
}
