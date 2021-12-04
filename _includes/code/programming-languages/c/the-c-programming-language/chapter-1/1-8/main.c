#include <stdio.h>

int main() {
  char c;
  int spaces = 0;
  int tabs = 0;
  int newlines = 0;

  while ((c = getchar()) != EOF) {
    if (c == ' ')
      spaces++;
    if (c == '\t')
      tabs++;
    if (c == '\n')
      newlines++;
    if (c == '`')
      break;
  }

  printf("------------\n");
  printf("Spaces: %d\n", spaces);
  printf("tabs: %d\n", tabs);
  printf("newlines: %d\n", newlines);
}
