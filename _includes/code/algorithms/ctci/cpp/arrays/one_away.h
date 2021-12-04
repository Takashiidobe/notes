/*
 *
 * One Away: There are three types of edits that can be performed on strings:
 * insert a character, remove a character, or replace a character. Given two
 * strings, write a function to check if they are one edit (or zero edits) away.
 *
 */

#include "../test/test.h"
#include <string>
#include <valarray>

namespace arrays {
namespace one_away {
bool one_away(std::string a, std::string b) {
  int m = a.size(), n = b.size();

  if (std::abs(m - n) > 1)
    return false;

  int count = 0;

  int i = 0, j = 0;
  while (i < m && j < n) {
    if (a[i] != b[j]) {
      if (count == 1)
        return false;

      if (m > n)
        i++;
      else if (m < n)
        j++;
      else {
        i++;
        j++;
      }
      count++;
    }

    else {
      i++;
      j++;
    }
  }

  if (i < m || j < n)
    count++;

  return count == 1;
}

void test() {
  test_eq(one_away("pale", "pales"), true);
  test_eq(one_away("pale", "ple"), true);
  test_eq(one_away("pale", "bake"), false);
}
} // namespace one_away
} // namespace arrays
