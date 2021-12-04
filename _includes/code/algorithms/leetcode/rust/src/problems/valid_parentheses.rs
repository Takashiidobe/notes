/*
 * @lc app=leetcode id=20 lang=rust
 *
 * [20] Valid Parentheses
 */

#[allow(dead_code)]
struct Solution {}

// @lc code=start
#[allow(dead_code)]
impl Solution {
    pub fn is_valid(s: String) -> bool {
        let mut stack = Vec::new();
        for c in s.chars() {
            match c {
                '(' => stack.push('('),
                '{' => stack.push('{'),
                '[' => stack.push('['),
                ')' => {
                    if stack.pop() != Some('(') {
                        return false;
                    }
                }
                '}' => {
                    if stack.pop() != Some('{') {
                        return false;
                    }
                }
                ']' => {
                    if stack.pop() != Some('[') {
                        return false;
                    }
                }
                _ => (),
            }
        }

        stack.len() == 0
    }
}
// @lc code=end

#[test]
fn test_1() {
    assert_eq!(Solution::is_valid(String::from("()")), true);
}

#[test]
fn test_2() {
    assert_eq!(Solution::is_valid(String::from("())")), false);
}

#[test]
fn test_3() {
    assert_eq!(Solution::is_valid(String::from("()[]{}")), true);
}
