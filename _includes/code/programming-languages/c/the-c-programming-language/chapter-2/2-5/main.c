#include <stdio.h>
#include <string.h>

int any(char s1[], char s2[]) {
  int s1_len = strlen(s1);
  int s2_len = strlen(s2);

  for (int i = 0; i < s1_len; i++)
    for (int j = 0; j < s2_len; j++)
      if (s1[i] == s2[j])
        return i;

  return -1;
}

int main() { printf("%d\n", any("hello", "0")); }
