/*
 * @lc app=leetcode id=94 lang=rust
 *
 * [94] Binary Tree Inorder Traversal
 */

use leetcode_prelude::*;

#[allow(dead_code)]
struct Solution {}

// @lc code=start
use std::cell::RefCell;
use std::rc::Rc;

#[allow(dead_code)]
impl Solution {
    pub fn inorder_traversal(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {
        fn helper(node: &Option<Rc<RefCell<TreeNode>>>, ret: &mut Vec<i32>) {
            if let Some(v) = node {
                let v = v.borrow();

                helper(&v.left, ret);
                ret.push(v.val);
                helper(&v.right, ret);
            }
        }

        let mut ret = vec![];

        if let Some(v) = root {
            helper(&Some(v), &mut ret);
        }

        ret
    }
}
// @lc code=end

#[test]
fn test_1() {
    assert_eq!(Solution::inorder_traversal(None), vec![]);
}

#[test]
fn test_2() {
    let root = btree![1, 2, 3];
    assert_eq!(Solution::inorder_traversal(root), vec![2, 1, 3]);
}

#[test]
fn test_3() {
    let root = btree![1, null, 2, 3];

    assert_eq!(Solution::inorder_traversal(root), vec![1, 3, 2]);
}
