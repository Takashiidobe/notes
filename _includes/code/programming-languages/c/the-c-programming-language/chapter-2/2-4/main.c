#include <stdio.h>
#include <string.h>

char lower(char c) {
  if (c >= 'A' && c <= 'Z')
    return c + 'a' - 'A';
  else
    return c;
}

void squeeze(char s1[], char s2[]) {
  int s1_len = strlen(s1);
  int s2_len = strlen(s2);
  char result[s1_len];
  int idx = 0;

  for (int i = 0; i < s1_len; i++) {
    char has_char = 0;
    for (int j = 0; j < s2_len; j++) {
      if (lower(s1[i]) == lower(s2[j]))
        has_char = 1;
    }

    if (!has_char)
      result[idx++] = s1[i];
  }

  result[idx] = '\0';
  printf("%s\n", result);
}

int main() {
  char hello[] = "Hello";
  char hello2[] = "Hello";
  char hi[] = "hi";
  char he[] = "he";
  squeeze(hello, hi);
  squeeze(hello2, he);
}
