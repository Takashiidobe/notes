/*
 *
 * Check Permutation: Given two strings, write a method to decide if one is a
 * permutation of the other.
 *
 */

#include "../test/test.h"
#include <map>
#include <string>

namespace arrays {
namespace check_permutation {
bool check_permutation(std::string first, std::string second) {
  if (first.size() != second.size())
    return false;

  auto first_map = std::map<const char, std::size_t>();

  auto second_map = std::map<const char, std::size_t>();

  for (const auto c : first)
    first_map[c]++;
  for (const auto c : second)
    second_map[c]++;

  if (first_map == second_map)
    return true;

  return false;
}

// this makes sure two maps can be properly compared.
bool sanity_check() {
  auto first = std::map<const char, std::size_t>();
  first['h'] = 1;
  auto second = std::map<const char, std::size_t>();
  second['n'] = 2;

  auto third = std::map<const char, std::size_t>();
  third['h'] = 1;
  auto fourth = std::map<const char, std::size_t>();
  fourth['h'] = 1;

  return first == second && third == fourth;
}

void test() {
  test_eq(check_permutation("hello", "olelh"), true);
  test_eq(check_permutation("hello", "oolelh"), false);
  test_eq(check_permutation("hello", "ooleh"), false);
  test_eq(sanity_check(), false);
}
} // namespace check_permutation
} // namespace arrays
