#include <numeric>
#include <vector>

namespace lists {
namespace sum {
int sum(const std::vector<int>& vec) {
  auto sum = 0;
  for (const auto item : vec) sum += item;
  return sum;
}

auto test() {
  test_eq(sum({1, 2, 3}), 6);
  test_eq(sum({5, 2, 3}), 10);
  test_eq(sum({10, 2, 3}), 15);
}

}  // namespace sum
}  // namespace lists
