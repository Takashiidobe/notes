#include <stdio.h>

#define LEN 26

int main() {
  int lengths[LEN];

  for (int i = 0; i < LEN; i++)
    lengths[i] = 0;

  int c;

  while ((c = getchar()) != EOF) {
    if (c >= 97 && c <= 122)
      lengths[c - 97]++;
    if (c >= 65 && c <= 90)
      lengths[c - 65]++;
    if (c == '\'')
      break;
  }

  for (int i = 0; i < LEN; i++) {
    printf("Count of letter %c: ", i + 65);
    for (int j = 0; j < lengths[i]; j++) {
      if (lengths[i] != 0)
        putchar('|');
      else
        printf("No count here");
    }
    putchar('\n');
  }
}
