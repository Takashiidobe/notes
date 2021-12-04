/*
 * @lc app=leetcode id=844 lang=rust
 *
 * [844] Backspace String Compare
 */

// @lc code=start
#[allow(dead_code)]
struct Solution {}

#[allow(dead_code)]
impl Solution {
    pub fn backspace_compare(s: String, t: String) -> bool {
        let mut left = String::from("");
        let mut right = String::from("");
        for c in s.chars() {
            match c {
                '#' => {
                    if left.len() > 0 {
                        left.pop();
                    }
                }
                c => left.push(c),
            }
        }
        for c in t.chars() {
            match c {
                '#' => {
                    if right.len() > 0 {
                        right.pop();
                    }
                }
                c => right.push(c),
            }
        }
        left == right
    }
}
// @lc code=end
#[test]
fn example_1() {
    assert_eq!(
        Solution::backspace_compare("ab#c".to_string(), "ad#c".to_string()),
        true
    );
}
#[test]
fn example_2() {
    assert_eq!(
        Solution::backspace_compare("ab##".to_string(), "c#d#".to_string()),
        true
    );
}
#[test]
fn example_3() {
    assert_eq!(
        Solution::backspace_compare("a##c".to_string(), "#a#c".to_string()),
        true
    );
}
#[test]
fn example_4() {
    assert_eq!(
        Solution::backspace_compare("a#c".to_string(), "b".to_string()),
        false
    );
}
