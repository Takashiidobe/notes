#include <stdio.h>

unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y) {
  unsigned mask;
  if (n == 0) {
    mask = 0;
  } else {
    mask = ~(~0 << (n - 1) << 1) << (p + 1 - n);
  }
  return (x & ~mask) | (y & mask);
}

int main() {
  printf("hi");
  return 0;
}
