#include <stdio.h>

#define MAXLINE 100000

int main() {
  char line[MAXLINE], ch;
  int i = 0;
  while ((ch = getchar()) != EOF) {
    line[i] = ch;
    i++;
  }

  for (int j = 0; j < i; j++) {
    if (line[j] == '/' && line[j + 1] == '/') {
      ++j;
      ++j;
      while (line[j + 1] != '\n') {
        ++j;
      }
    } else if (line[j] == '/' && line[j + 1] == '*' && line[j + 2] != '"') {
      ++j;
      ++j;
      while ((line[j] == '/' && line[j + 1] == '/') || line[j] != '/' ||
             (line[j + 1] != '\n' && line[j + 1] == '\n')) {
        ++j;
      }
    } else {
      printf("%c", line[j]);
    }
  }
}
