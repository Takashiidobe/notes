#include <stdio.h>

#define MAXLEN 1000

int get_len(char _current_line[], int _maxline) {
  int i, c;

  for (i = 0; i < _maxline && (c = getchar()) != EOF && c != '\n'; ++i)
    _current_line[i] = c;
  if (c == '\n') {
    _current_line[i] = '\n';
    ++i;
  }
  _current_line[i] = '\0';
  return i;
}

int main() {
  int len;
  char ln[MAXLEN];

  while ((len = get_len(ln, MAXLEN)) > 0) {
    if (len > 80)
      printf("%s\n", ln);
    else
      printf("line < 80 \n");
  }
}
