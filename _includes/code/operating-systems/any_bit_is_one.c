#include <stdio.h>
#include <stdbool.h>

int x = 12;

bool any_bit_is_one(int x) {
  while(x > 1) {
    x = x >> 1;
    if (x == 1) return true;
  }
  return false;
}

int main() {
  bool answer = any_bit_is_one(x);
  printf("%i\n", answer);
}
