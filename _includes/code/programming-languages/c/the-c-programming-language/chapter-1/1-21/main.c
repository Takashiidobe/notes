#include <stdio.h>
#define TAB 7

int main(void) {
  int p = 0;
  int blanks = 0;
  char chunk[TAB + 2];
  int c;

  while ((c = getchar()) != EOF) {
    chunk[p++] = c;
    if (c == ' ')
      ++blanks;
    else
      blanks = 0;
    if (p == TAB || c == '\n') {
      chunk[p] = '\0';
      if (blanks > 1) {
        p -= blanks;
        chunk[p] = '\t';
        chunk[p + 1] = '\0';
      }
      printf("%s", chunk);
      p = blanks = 0;
    }
  }
  if (p > 0) {
    chunk[p] = '\0';
    printf("%s", chunk);
  }
  return 0;
}
