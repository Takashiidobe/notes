/*
 *
 * URLify: Write a method to replace all spaces in a string with '%20'. You may
 * assume that the string has sufficient space at the end to hold the additional
 * characters, and that you are given the "true" length of the string. (Note: If
 * implementing in Java, please use a character array so that you can perform
 * this operation in place.)
 *
 */

#include <string>

#include "../test/test.h"

namespace arrays {
namespace urlify {

void rtrim(std::string &str, const std::string &chars = "\t\n\v\f\r ") {
  str.erase(str.find_last_not_of(chars) + 1);
}

const std::string urlify(std::string s) {
  std::string answer = "";
  rtrim(s);
  for (const auto c : s) {
    if (c == ' ') {
      answer += "%20";
    } else {
      answer += c;
    }
  }

  return answer;
}

void test() { test_eq(urlify("Mr John Smith    "), "Mr%20John%20Smith"); }
} // namespace urlify
} // namespace arrays
