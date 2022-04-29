/* 1. Write a program that calls fork(). Before calling fork(), have the main
   process access a variable (e.g., x) and set its value to something (e.g., 100).
   What value is the variable in the child process? What happens to the variable
   when both the child and parent change the value of x?
   */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  volatile int x = 0;
  int rc = fork();
  if (rc < 0) { // fork failed; exit
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) { // child (new process)
    printf("value of x in child: %d\n", x);
    x = 200;
    printf("value of x in child: %d\n", x);
  } else { // parent goes down this path (main)
    printf("value of x in parent: %d\n", x);
    x = 300;
    printf("value of x in parent: %d\n", x);
  }
  return 0;
}
