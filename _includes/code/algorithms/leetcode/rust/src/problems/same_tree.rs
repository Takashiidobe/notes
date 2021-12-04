/*
 * @lc app=leetcode id=100 lang=rust
 *
 * [100] Same Tree
 *
 * https://leetcode.com/problems/same-tree/description/
 *
 * algorithms
 * Easy (53.69%)
 * Total Accepted:    637.8K
 * Total Submissions: 1.2M
 * Testcase Example:  '[1,2,3]\n[1,2,3]'
 *
 * Given two binary trees, write a function to check if they are the same or
 * not.
 *
 * Two binary trees are considered the same if they are structurally identical
 * and the nodes have the same value.
 *
 * Example 1:
 *
 *
 * Input:    1         1
 * ⁠         / \       / \
 * ⁠        2   3     2   3
 *
 * ⁠       [1,2,3],   [1,2,3]
 *
 * Output: true
 *
 *
 * Example 2:
 *
 *
 * Input:    1         1
 * ⁠         /           \
 * ⁠        2             2
 *
 * ⁠       [1,2],     [1,null,2]
 *
 * Output: false
 *
 *
 * Example 3:
 *
 *
 * Input:    1         1
 * ⁠         / \       / \
 * ⁠        2   1     1   2
 *
 * ⁠       [1,2,1],   [1,1,2]
 *
 * Output: false
 *
 *
 */

use leetcode_prelude::*;
use std::cell::RefCell;
use std::rc::Rc;

#[allow(dead_code)]
struct Solution {}

#[allow(dead_code)]
impl Solution {
    pub fn is_same_tree(
        p: Option<Rc<RefCell<TreeNode>>>,
        q: Option<Rc<RefCell<TreeNode>>>,
    ) -> bool {
        match (p, q) {
            (Some(l), Some(r)) => {
                let l = l.borrow();
                let r = r.borrow();
                return l.val == r.val
                    && Solution::is_same_tree(l.left.clone(), r.left.clone())
                    && Solution::is_same_tree(l.right.clone(), r.right.clone());
            }
            (None, None) => true,
            (_, _) => false,
        }
    }
}

#[test]
fn test_1() {
    let left = btree![1, 2, 3];
    let right = btree![1, 2, 3];
    assert_eq!(Solution::is_same_tree(left, right), true);
}

#[test]
fn test_2() {
    let left = btree![1, 2];
    let right = btree![1, null, 2];
    assert_eq!(Solution::is_same_tree(left, right), false);
}

#[test]
fn test_3() {
    let left = btree![1, 2, 1];
    let right = btree![1, 1, 2];
    assert_eq!(Solution::is_same_tree(left, right), false);
}
