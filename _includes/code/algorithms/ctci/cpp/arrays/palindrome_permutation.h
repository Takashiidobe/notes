/*
 *
 * Palindrome Permutation: Given a string, write a function to check if it is a
 * permutation of a palin­drome. A palindrome is a word or phrase that is the
 * same forwards and backwards. A permutation is a rearrangement of letters. The
 * palindrome does not need to be limited to just dictionary words.
 *
 */

#include "../test/test.h"
#include <locale>
#include <map>
#include <string>

namespace arrays {
namespace palindrome_permutation {

bool palindrome_permutation(std::string &s) {

  auto m = std::map<const char, std::size_t>();

  for (auto c : s) {
    if (c != ' ') {
      c = std::tolower(c);
      m[c] += 1;
    }
  }

  std::size_t count = 0;

  for (const auto &[key, val] : m) {
    if (val % 2 != 0)
      count++;
  }

  return count < 2;
}

void test() {
  std::string s = "Tact Coa";
  test_eq(palindrome_permutation(s), true);

  std::string haha = "haha";
  test_eq(palindrome_permutation(haha), true);
}

} // namespace palindrome_permutation
} // namespace arrays
