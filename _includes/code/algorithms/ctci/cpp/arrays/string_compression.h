/*
 *
 * String Compression: Implement a method to perform basic string compression
 * using the counts of repeated characters. For example, the string aabcccccaaa
 * would become a2blc5a3. If the "compressed" string would not become smaller
 * than the original string, your method should return the original string. You
 * can assume the string has only uppercase and lowercase letters (a - z).
 *
 */

#include "../test/test.h"
#include <string>

namespace arrays {
namespace string_compression {
const std::string string_compression(const std::string &s) {
  std::string ans = "";

  std::size_t i = 0;
  std::size_t j = 1;

  while (i < s.size() && j < s.size()) {
    while (s[i] == s[j]) {
      j++;
    }

    ans += s[i] + to_string(j - i);

    i = j;
    j++;
  }

  return ans;
}

void test() { test_eq(string_compression("aabcccccaaa"), "a2b1c5a3"); }
} // namespace string_compression
} // namespace arrays
