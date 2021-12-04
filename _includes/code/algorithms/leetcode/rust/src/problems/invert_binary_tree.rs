/*
 * @lc app=leetcode id=226 lang=rust
 *
 * [226] Invert Binary Tree
 */

use leetcode_prelude::TreeNode;
use std::cell::RefCell;
use std::rc::Rc;

#[allow(dead_code)]
struct Solution {}

// @lc code=start
#[allow(dead_code)]
impl Solution {
  pub fn invert_tree(mut root: Option<Rc<RefCell<TreeNode>>>) -> Option<Rc<RefCell<TreeNode>>> {
    fn invert(node: &mut Option<Rc<RefCell<TreeNode>>>) {
      if let Some(n) = node {
        let mut n = n.borrow_mut();
        invert(&mut n.left);
        invert(&mut n.right);

        let lt = std::mem::replace(&mut n.left, None);
        let rt = std::mem::replace(&mut n.right, lt);
        let _ = std::mem::replace(&mut n.left, rt);
      }
    }
    invert(&mut root);
    root
  }
}

// @lc code=end
#[cfg(test)]
mod test {
  use super::*;

  #[test]
  fn test_1() {
    assert_eq!(Solution::invert_tree(None), None);
  }

  #[test]
  fn test_2() {
    assert_eq!(Solution::invert_tree(None), None);
  }
}
