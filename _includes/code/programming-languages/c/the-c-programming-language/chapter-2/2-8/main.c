#include <stdio.h>

unsigned rightrot(unsigned x, unsigned n) {
  while (n > 0) {
    if ((x & 1) == 1)
      x = (x >> 1) | ~(~0U >> 1);
    else
      x = (x >> 1);
    n--;
  }
  return x;
}

int main() {
  printf("%d\n", rightrot(10, 3));
  printf("%d\n", rightrot(2, 5));
}
