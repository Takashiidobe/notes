#include <stdio.h>
#include <string.h>

int strrindex(char s[], char t[]) {
  int slen = strlen(s);
  int tlen = strlen(t);

  int rightmost = -1;

  for (int i = 0; i < slen; i++) {
    if (s[i] == t[0]) {
      for (int j = 1; j <= tlen; j++) {
        if (j == tlen)
          rightmost = i;
        if (s[i + j] != t[j])
          break;
      }
    }
  }

  return rightmost;
}

int main() {
  printf("%d\n", strrindex("HelloHello", "llo"));
  printf("%d\n", strrindex("Hello", "ello"));
  printf("%d\n", strrindex("Hello", "no"));
  return 0;
}
