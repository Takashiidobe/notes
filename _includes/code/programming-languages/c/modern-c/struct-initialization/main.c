#include <stdio.h>

typedef struct v2 {
  float x;
  float y;
} v2;

void printv2(v2 v) { printf("[%f, %f]", v.x, v.y); }

int main() {
  v2 v2_1 = {.x = 1.0f, .y = 1.0f};
  printv2(v2_1);
  v2 v2_2 = {.x = 1.0f};
  printv2(v2_2);
}
