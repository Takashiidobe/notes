#include <stdio.h>
#include <string.h>

void reverse(char *str) {
  if (str != 0 && *str != '\0') {
    char *end = str + strlen(str) - 1;

    while (str < end) {
      char tmp = *str;
      *str++ = *end;
      *end-- = tmp;
    }
  }
}

int main() {
  int c;
  int i = 0;
  char curr[80];
  while ((c = getchar()) != EOF) {
    curr[i] = c;
    i++;
    if (c == '\n') {
      reverse(curr);
      printf("%s", curr);
    }
  }
}
