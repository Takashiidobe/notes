#include <stdio.h>

typedef struct v2 {
  float x;
  float y;
} v2;

v2 v2_add(v2 a, v2 b) {
  v2 result = {a.x + b.x, a.y + b.y};
  return result;
}

typedef union hmm_vec2 {
  struct {
    float X;
    float Y;
  };
  struct {
    float U;
    float V;
  };
  struct {
    float Left;
    float Right;
  };
  struct {
    float Width;
    float Height;
  };
  float Elements[2];
} hmm_vec2;

void print_vec2(hmm_vec2 v) {
  printf("[%f, %f]\n", v.Elements[0], v.Elements[1]);
}

void printv2(v2 v) { printf("[%f, %f]\n", v.x, v.y); }

int main() {
  v2 v2_1 = {.x = 1.0f, .y = 1.0f};
  printv2(v2_1);
  v2 v2_2 = {.x = 1.0f};
  printv2(v2_2);

  v2 v_added = v2_add(v2_1, v2_2);
  printv2(v_added);

  hmm_vec2 vec2 = {.U = 10, .V = 20};
  print_vec2(vec2);
}
