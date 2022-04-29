#include <stdio.h>
#include <stdlib.h>

int main() {
  int* data = malloc(sizeof(int) * 100);

  free(data + 50); // linter tells me i've freed a pointer that is offset 50 places

  // funny-free(22660,0x109bfedc0) malloc: *** error for object 0x7fc13dc05b38: pointer being freed was not allocated
  // funny-free(22660,0x109bfedc0) malloc: *** set a breakpoint in malloc_error_break to debug
  // fish: Job 1, './build/funny-free' terminated by signal SIGABRT (Abort)
  // This happens because there isn't a length with the pointer, i bet.
}
