#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define auto __auto_type

#define LEN(x) (sizeof(x) / sizeof(x *))

#define TYPE_SIZE(x) (sizeof(x *))

#define map(s, d, f)                                                           \
  ({                                                                           \
    for (unsigned i = 0; i < len; i++)                                         \
      d[i] = f(s[i]);                                                          \
    d;                                                                         \
  })

int f(int a) { return a + 10; }

int main() {
  int collection[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int col[10];
  auto len = 10;
  int *answer = map(collection, col, f);

  for (int i = 0; i < len; i++) {
    printf("%d\n", answer[i]);
  }
  // for (int i = 0; i < len; i++) {
  //   printf("%d\n", answer[i]);
  // }
  // for (int i = 0; i < len; i++) {
  //   printf("%d\n", collection[i]);
  // }
}
