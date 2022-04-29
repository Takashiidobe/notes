#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

// What does wait return? It returns an integer. We need to check if its greater than 0 to make sure the child has finished).
// waiting in the child doesn't work.

int main(int argc, char *argv[]) {
  int rc = fork();
  if (rc < 0) { // fork failed; exit
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    printf("In child\n");
    while ((wait(NULL)) > 0) {
      printf("After waiting in child\n");
    }
  } else { // parent goes down this path (main)
    int rc = wait(NULL);
    if (rc > 0) {
      printf("All children succeeded\n");
    }
  }
  return 0;
}
