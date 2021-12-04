#include <algorithm>
#include <ranges>
#include <string>
#include <vector>

#include "../test/test.h"

namespace algorithms {
namespace reverse_string {

const std::string reverse_string(std::string str) {
  std::ranges::reverse(str);
  return str;
}

auto test() { test_eq(reverse_string("hello"), "olleh"); }
}  // namespace reverse_string
}  // namespace algorithms
