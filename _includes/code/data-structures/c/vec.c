#include "vec.h"

typedef char *string;

typedef struct {
  int x;
  int y;
} Tuple;

int main() {
  auto *v = vec_new(Tuple, {4, 2}, {5, 10}, {10, 5});
  vec_push(v, {10, 10});

  Tuple x = vec_pop(v);
  printf("Popped: (%d, %d)\n", x.x, x.y);

  for (int i = 0; i < v->len; i++) {
    printf("(%d, %d)\n", v->data[i].x, v->data[i].y);
  }
}
