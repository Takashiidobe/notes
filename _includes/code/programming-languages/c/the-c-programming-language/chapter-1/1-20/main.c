#include <stdio.h>
#define TAB_SIZE 7

int main() {
  int c;
  while ((c = getchar()) != EOF) {
    if (c != '\t')
      putchar(c);
    else {
      for (int i = 0; i < TAB_SIZE; i++)
        putchar(' ');
    }
  }
}
