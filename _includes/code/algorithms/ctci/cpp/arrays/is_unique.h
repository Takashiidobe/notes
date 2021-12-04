/*
 *
 *Is Unique: Implement an algorithm to determine if a string has all unique
 *characters. What if you cannot use additional data structures?
 *
 */

#include "../test/test.h"
#include <iostream>
#include <set>
#include <string>

namespace arrays {
namespace is_unique {
bool is_unique(const std::string &s) {

  auto character_count = std::set<char>();

  for (const auto c : s) {
    if (character_count.contains(c)) {
      return false;
    } else {
      character_count.insert(c);
    }
  }

  return true;
}

void test() {
  test_eq(is_unique("hello"), false);
  test_eq(is_unique("orange"), true);
  test_eq(is_unique(""), true);
}
} // namespace is_unique
} // namespace arrays
