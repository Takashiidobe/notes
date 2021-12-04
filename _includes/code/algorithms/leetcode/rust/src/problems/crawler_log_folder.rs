/*
 * @lc app=leetcode id=1598 lang=rust
 *
 * [1598] Crawler Log Folder
 */

#[allow(dead_code)]
struct Solution {}

// @lc code=start
#[allow(dead_code)]
impl Solution {
    pub fn min_operations(logs: Vec<&str>) -> i32 {
        // Keep a counter of the level we're in.
        let mut level = 0;
        // iterate through the logs
        for log in logs {
            // for every item, there are three "types":
            // "./" -> do nothing
            // "../" -> level -= 1. If level = 0, do nothing.
            // "__/" -> level += 1.
            match log {
                "./" => {}
                "../" => {
                    if level > 0 {
                        level -= 1;
                    }
                }
                _ => level += 1,
            }
        }
        // return the level here.
        level
    }
}
// @lc code=end
#[test]
fn example_1() {
    assert_eq!(
        Solution::min_operations(vec!["d1/", "d2/", "../", "d21/", "./"]),
        2
    );
}

#[test]
fn example_2() {
    assert_eq!(
        Solution::min_operations(vec!["d1/", "d2/", "./", "d3/", "../", "d31/"]),
        3
    );
}

#[test]
fn example_3() {
    assert_eq!(
        Solution::min_operations(vec!["d1/", "../", "../", "../"]),
        0
    );
}
