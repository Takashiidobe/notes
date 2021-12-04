#include <assert.h>

int main() {
  static_assert(2 + 2 == 4, "Math is broken!");
  _Static_assert(sizeof(int) < sizeof(char),
                 "This program requires char > int");
}
