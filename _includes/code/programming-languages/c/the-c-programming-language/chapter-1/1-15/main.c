#include <stdio.h>

int celcius_to_fahrenheit(int deg) { return (deg * 1.8) + 32; }

int main() {
  printf("C\tF\n");
  for (int i = 0; i <= 300; i += 20)
    printf("%d\t%d\n", i, celcius_to_fahrenheit(i));
}
