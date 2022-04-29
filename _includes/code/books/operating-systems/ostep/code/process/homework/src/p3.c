/*
3. Write another program using fork(). The child process should print “hello”;
the parent process should print “goodbye”. You should try to ensure that
the child process always prints first; can you do this without calling wait() in
the parent?
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>

// You can force the child to print first with spin, otherwise, no.
// otherwise, use wait()

int main(int argc, char *argv[]) {
  int rc = fork();
  if (rc < 0) { // fork failed; exit
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) { // child (new process)
    // try to print hello
    write(STDOUT_FILENO, "hello\n", 7);
  } else {
    // try to print goodbye
    write(STDOUT_FILENO, "goodbye\n", 9);
  }

  return 0;
}
