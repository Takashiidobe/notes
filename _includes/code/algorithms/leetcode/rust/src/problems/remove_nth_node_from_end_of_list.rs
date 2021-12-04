/*
 * @lc app=leetcode id=19 lang=rust
 *
 * [19] Remove Nth Node From End of List
 */

use crate::linked_list::ListNode;

#[allow(dead_code)]
struct Solution {}

// @lc code=start
impl Solution {
  pub fn remove_nth_from_end(head: Option<Box<ListNode>>, n: i32) -> Option<Box<ListNode>> {

    // increment the node n times
    // this is the fast pointer
    // when the fast pointer hits the end,
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
