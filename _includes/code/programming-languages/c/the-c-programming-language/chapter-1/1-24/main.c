#include <stdio.h>

#define MAX_SIZE 1024

int main() {
  char c;
  char stack[MAX_SIZE];
  int i = 0;
  while ((c = getchar()) != EOF) {
    if (i < 0) {
      printf("misplaced closing brace\n");
      return 1;
    }
    if (c == '{') {
      stack[i] = '{';
      i++;
    }
    if (c == '(') {
      stack[i] = '(';
      i++;
    }
    if (c == '[') {
      stack[i] = '[';
      i++;
    }
    if (c == '}') {
      if (stack[i - 1] != '{') {
        printf("Syntax Error, misplaced }\n");
        return 1;
      } else {
        i--;
      }
    }
    if (c == ')') {
      if (stack[i - 1] != '(') {
        printf("Syntax Error, misplaced )\n");
        return 1;
      } else {
        i--;
      }
    }
    if (c == ']') {
      if (stack[i - 1] != '[') {
        printf("Syntax Error, misplaced ]\n");
        return 1;
      } else {
        i--;
      }
    }
  }
}
