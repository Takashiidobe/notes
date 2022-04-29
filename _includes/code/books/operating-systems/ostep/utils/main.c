#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
  errno = 2;
}

int main(void) {
  int a = 10;
  int b = 20;

  swap(&a, &b);

  printf("%d, %d\n", a, b);
}
