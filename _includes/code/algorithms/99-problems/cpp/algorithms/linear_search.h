#include <vector>

#include "../test/test.h"

namespace algorithms {
namespace linear_search {

template <typename T>
bool linear_search(const vector<T>& arr, T target) {
  for (const auto& item : arr) {
    if (item == target) return true;
  }
  return false;
}

auto test() {
  test_eq(linear_search({1, 2, 3}, 2), true);
  test_eq(linear_search({1, 2, 3}, 4), false);
}
}  // namespace linear_search
}  // namespace algorithms
