#include <algorithm>
#include <ranges>
#include <vector>

#include "../test/test.h"

namespace algorithms {
namespace binary_search {

template <typename T>
bool binary_search(const vector<T> &arr, T target) {
  return std::ranges::binary_search(arr, target);
}

auto test() {
  test_eq(binary_search({1, 2, 3}, 2), true);
  test_eq(binary_search({1, 2, 3}, 4), false);
}
}  // namespace binary_search
}  // namespace algorithms
