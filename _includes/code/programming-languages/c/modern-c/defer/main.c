#include <stdio.h>
#include <stdlib.h>

#define macro_var(name) concat(name, __LINE__)
#define defer(start, end)                                \
  for (int macro_var(_i_) = (start, 0); !macro_var(_i_); \
       (macro_var(_i_) += 1), end)

typedef struct v2 {
  float x;
  float y;
} v2;

void printv2(v2 v) { printf("[%f, %f]", v.x, v.y); }

v2 *alloc() {
  v2 *v = malloc(sizeof(v2));
  return v;
}

void delete (v2 *v) { free(v); }

int main() {
  v2 *v = NULL;
  defer(alloc(), delete ()) { printv2(*v); }
}
