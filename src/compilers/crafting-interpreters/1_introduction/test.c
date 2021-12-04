#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main() {
  char* c = malloc(5);
  c = "hello";
  char* d = malloc(5);
  d = "world";

  bool a = c == d;
  if (a) printf("true\n");
}
