#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int htoi(char s[]) {
  int len = strlen(s);
  int i = 0;
  int total = 0;
  if (len > 2)
    if (s[0] == '0' && (s[1] == 'X' || s[1] == 'x'))
      i += 2;

  for (; i < len; i++) {
    if (isdigit(s[i])) {
      total = 16 * total + (s[i] - '0');
    }
    if (s[i] >= 'a' && s[i] <= 'f') {
      total = 16 * total + (10 + s[i] - 'a');
    }
    if (s[i] >= 'A' && s[i] <= 'F') {
      total = 16 * total + (10 + s[i] - 'A');
    }
  }

  return total;
}

int main() {
  assert(htoi("FF") == 255);
  assert(htoi("0xFF") == 255);
  assert(htoi("0XFF") == 255);

  assert(htoi("00") == 0);
  assert(htoi("F") == 15);
  assert(htoi("10") == 16);
  puts("All tests completed successfully.");
}
