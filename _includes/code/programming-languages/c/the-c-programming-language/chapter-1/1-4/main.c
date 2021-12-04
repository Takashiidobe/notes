#include <stdio.h>

int main() {
  int lowest = 0;
  int highest = 300;
  int step = 20;
  int curr = lowest;
  printf("C\tF\n");
  while (curr <= highest) {
    int fahrenheit = (curr * 1.8) + 32;
    printf("%d\t%d\n", curr, fahrenheit);
    curr += step;
  }
}
