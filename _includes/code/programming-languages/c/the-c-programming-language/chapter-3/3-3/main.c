#include <ctype.h>
#include <stdio.h>
#include <string.h>

int isdash(char c) { return c == '-'; }

void expand(char s[], char t[]) {
  int len = strlen(s);
  int j = 0;
  for (int i = 0; i < len; i++) {
    char c = s[i];
    if (i + 2 < len) {
      if (isdigit(c) && isdash(s[i + 1]) && isdigit(s[i + 2])) {
        for (int k = 0; k <= s[i + 2] - c; k++) {
          t[j] = c + k;
          j++;
        }
        i += 2;
      } else if (islower(c) && isdash(s[i + 1]) && islower(s[i + 2])) {
        for (int k = 0; k <= s[i + 2] - c; k++) {
          t[j] = c + k;
          j++;
        }
        i += 2;
      } else if (isupper(c) && isdash(s[i + 1]) && isupper(s[i + 2])) {
        for (int k = 0; k <= s[i + 2] - c; k++) {
          t[j] = c + k;
          j++;
        }
        i += 2;
      } else {
        t[j] = s[i];
        j++;
      }
    } else {
      t[j] = s[i];
      j++;
    }
  }
  t[j] = '\0';
}

int main() {
  char s[] = "0-35-8a-z";
  char t[1000];
  expand(s, t);
  printf("%s\n", t);
}
