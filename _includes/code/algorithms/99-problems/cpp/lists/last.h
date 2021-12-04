#include <vector>

#include "../test/test.h"

namespace lists {
namespace last {

template <typename T>
const T last(const std::vector<T> &list) {
  if (list.size() > 0) {
    return list[list.size() - 1];
  } else {
    throw "Runtime error";
  }
}

auto test() {
  test_eq(last<int>({1, 2, 3}), 3);
  test_eq(last<int>({5, 2, 3}), 3);
  test_eq(last<int>({10, 2, 3}), 3);
}
}  // namespace last
}  // namespace lists
