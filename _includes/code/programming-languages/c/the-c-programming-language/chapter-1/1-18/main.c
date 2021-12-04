#include <stdio.h>

#define MAXLINE 1024

int main() {
  int c;
  char buf[MAXLINE];
  int count = 0;

  while ((c = getchar()) != EOF) {
    // read chars till newline
    if (c != '\n' && count - 1 < MAXLINE) {
      buf[count++] = c;
    } else {
      // skip trailing whitespace
      while (buf[count - 1] == ' ' || buf[count - 1] == '\t') {
        count--;
      }
      // add nl and \0
      buf[count] = c;
      buf[count + 1] = 0;
      if (count != 0) { // after skipping all other whitespace is there
                        // something left besides the nl?
        printf("%s", buf);
        count = 0;
      }
    }
  }
}
