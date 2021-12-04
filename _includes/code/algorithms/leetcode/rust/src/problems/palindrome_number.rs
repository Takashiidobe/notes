/*
 * @lc app=leetcode id=9 lang=rust
 *
 * [9] Palindrome Number
 */

#[allow(dead_code)]
struct Solution {}

// @lc code=start
#[allow(dead_code)]
impl Solution {
  pub fn is_palindrome(x: i32) -> bool {
    if x < 0 {
      return false;
    }
    if x >= 0 && x < 10 {
      return true;
    }

    let str_x = x.to_string();

    let mut i = 0;
    let mut j = str_x.len() - 1;

    while i <= j {
      if str_x.as_bytes()[i] != str_x.as_bytes()[j] {
        return false;
      }
      i += 1;
      j -= 1;
    }

    true
  }
}
// @lc code=end

#[test]
fn test_1() {
  assert_eq!(Solution::is_palindrome(0), true);
}

#[test]
fn test_2() {
  assert_eq!(Solution::is_palindrome(121), true);
}

#[test]
fn test_3() {
  assert_eq!(Solution::is_palindrome(-121), false);
}

#[test]
fn test_4() {
  assert_eq!(Solution::is_palindrome(-121), false);
}
