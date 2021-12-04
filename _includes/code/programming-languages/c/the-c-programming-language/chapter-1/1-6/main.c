#include <stdio.h>

int main() {
  int c;

  printf("%d\n", EOF);

  // EOF is -1, so every int has to be either equal to it or not. ASCII
  // characters are never EOF, so this works for this set.

  while ((c = getchar()) != EOF)
    putchar(c);
}
