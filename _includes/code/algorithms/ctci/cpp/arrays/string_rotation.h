/*
 *
 * String Rotation:Assumeyou have a method isSubstringwhich checks ifoneword isa
 * substring of another. Given two strings, sl and s2, write code to check if s2
 * is a rotation of sl using only one call to isSubstring (e.g., "waterbottle"
 * is a rotation of"erbottlewat").
 *
 */

#include <string>

namespace arrays {
namespace string_rotation {
bool string_rotation(const std::string &a, const std::string &b) {
  if (a.size() != b.size())
    return false;
  if (a == b)
    return true;

  std::size_t j = 0;
  while (a[0] != b[j]) {
    j++;
  }

  for (const auto c : a) {
    auto b_index = j % b.size();
    if (c != b[b_index])
      return false;
    j++;
  }

  return true;
}

void test() { test_eq(string_rotation("waterbottle", "erbottlewat"), true); }
} // namespace string_rotation
} // namespace arrays
