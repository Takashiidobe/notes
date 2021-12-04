/*
 * @lc app=leetcode id=509 lang=rust
 *
 * [509] Fibonacci Number
 */

#[allow(dead_code)]
struct Solution {}

// @lc code=start
#[allow(dead_code)]
impl Solution {
  pub fn fib(n: i32) -> i32 {
    if n == 0 {
      return 0;
    }
    if n == 1 {
      return 1;
    }
    let mut first_num = 0;
    let mut second_num = 1;

    for _ in 2..n {
      let third_num = first_num + second_num;
      first_num = second_num;
      second_num = third_num;
    }

    first_num + second_num
  }
}
// @lc code=end

#[test]
fn test_1() {
  assert_eq!(Solution::fib(0), 0);
}

#[test]
fn test_2() {
  assert_eq!(Solution::fib(1), 1);
}

#[test]
fn test_3() {
  assert_eq!(Solution::fib(2), 1);
}

#[test]
fn test_4() {
  assert_eq!(Solution::fib(3), 2);
}

#[test]
fn test_5() {
  assert_eq!(Solution::fib(4), 3);
}
