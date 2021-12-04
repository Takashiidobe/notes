/*
 * @lc app=leetcode id=1 lang=rust
 *
 * [1] Two Sum
 */

#[allow(dead_code)]
struct Solution {}

// @lc code=start
use std::collections::HashMap;

#[allow(dead_code)]
impl Solution {
    pub fn two_sum(nums: Vec<i32>, target: i32) -> Vec<i32> {
        let mut hm: HashMap<i32, i32> = HashMap::new();

        for (index, num) in nums.iter().enumerate() {
            let index = index as i32;
            if hm.contains_key(&num) {
                let mut ans = vec![*hm.get(&num).unwrap(), index];
                ans.sort();
                return ans;
            } else {
                hm.insert(target - num, index);
            }
        }

        vec![-1, -1]
    }
}
// @lc code=end

#[test]
fn test_1() {
    assert_eq!(Solution::two_sum(vec![], 10), vec![-1, -1]);
}

#[test]
fn test_2() {
    assert_eq!(Solution::two_sum(vec![2, 4, 7, 11], 6), vec![0, 1]);
}

#[test]
fn test_3() {
    assert_eq!(Solution::two_sum(vec![2, 7, 11, 15], 9), vec![0, 1]);
}
