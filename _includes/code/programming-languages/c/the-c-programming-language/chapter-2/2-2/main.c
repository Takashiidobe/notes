#include <stdio.h>

int main() {
  int lim = 0;
  char c;
  char s[1024];
  for (int i = 0; c != EOF; ++i)
    if (i < lim - 1)
      if ((c = getchar()) != '\n')
        s[i] = c;
}
