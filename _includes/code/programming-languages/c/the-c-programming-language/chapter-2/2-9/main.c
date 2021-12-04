#include <stdio.h>

int bitcount(unsigned x) {
  int b;

  for (b = 0; x != 0; x &= (x - 1))
    b++;
  return b;
}

int main() {
  printf("The number of set bits in 5 are: %d\n", bitcount(5));
  printf("The number of set bits in 8 are: %d\n", bitcount(8));
  printf("The number of set bits in 16 are: %d\n", bitcount(16));
}
