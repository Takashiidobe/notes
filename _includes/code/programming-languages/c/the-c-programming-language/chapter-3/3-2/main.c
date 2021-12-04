#include <stdio.h>

enum bool { NO, YES };

char esc_char(char c) {
  switch (c) {
  case '\\':
    return '\\';
  case '\n':
    return 'n';
  case '\r':
    return 'r';
  case '\t':
    return 't';
  case '"':
    return '"';
  default:
    return '\0';
  }
}

void escape(char s[], char t[]) {
  int i = 0, j = 0;
  char c, e;

  while ((c = s[i++])) {
    if ((e = esc_char(c))) {
      t[j++] = '\\';
      t[j++] = e;
    } else {
      t[j++] = c;
    }
  }
  t[j] = '\0';
}
char unesc_char(char c) {
  switch (c) {
  case 'n':
    return '\n';
  case 'r':
    return '\r';
  case 't':
    return '\t';
  case '\\':
  case '"':
  default:
    return c;
  }
}

void unescape(char s[], char t[]) {
  int i = 0, j = 0, esc_mode = NO;
  char c;

  while ((c = s[i++])) {
    if (esc_mode) {
      t[j++] = unesc_char(c);
      esc_mode = NO;
    } else if (c == '\\') {
      esc_mode = YES;
    } else {
      t[j++] = c;
    }
  }
  t[j] = '\0';
}

int main() {
  char s[8] = "Hello\t\t\n";
  char t[9];
  escape(s, t);
  printf("%s\n", t);
}
