#include <stdio.h>

// crashes when ran because of dereferencing
// Thread 4 received signal SIGTRAP, Trace/breakpoint trap.
// Thread 4 received signal SIGSEGV, Segmentation fault.
// 0x0000000100003f74 in main () at src/null.c:6
int main() {
  int* p = NULL;

  printf("%d\n", *p);
}
