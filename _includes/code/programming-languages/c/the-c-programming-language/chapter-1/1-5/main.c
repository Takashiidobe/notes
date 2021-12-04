#include <stdio.h>

int main() {
  printf("F\tC\n");
  for (int i = 300; i >= 0; i -= 20) {
    int celcius = (i - 32) * 5 / 9;
    printf("%d\t%d\n", i, celcius);
  }
}
