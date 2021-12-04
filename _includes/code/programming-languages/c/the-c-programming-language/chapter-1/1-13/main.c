#include <stdio.h>

#define LEN 10

int main() {
  int lengths[LEN];

  for (int i = 0; i < LEN; i++)
    lengths[i] = 0;

  int c;

  int len = 0;
  while ((c = getchar()) != EOF) {
    if (c != '\t' && c != '\n' && c != ' ') {
      len++;
    } else {
      if (len > 8)
        len = 9;
      lengths[len]++;
      len = 0;
    }
    if (c == '\'')
      break;
  }

  for (int i = 0; i < LEN; i++) {
    printf("Count of words with length %d: ", i);
    for (int j = 0; j < lengths[i]; j++) {
      if (lengths[i] != 0)
        putchar('|');
      else
        printf("No count here");
    }
    putchar('\n');
  }
}
