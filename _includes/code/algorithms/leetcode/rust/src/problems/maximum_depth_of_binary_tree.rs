/*
 * @lc app=leetcode id=104 lang=rust
 *
 * [104] Maximum Depth of Binary Tree
 */

use leetcode_prelude::TreeNode;

#[allow(dead_code)]
struct Solution {}

// @lc code=start
use std::cell::RefCell;
use std::rc::Rc;
#[allow(dead_code)]
impl Solution {
  pub fn max_depth(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
    fn depth(node: &Option<Rc<RefCell<TreeNode>>>, mut current_depth: i32) -> i32 {
      if let Some(n) = node {
        let n = n.borrow();
        current_depth += 1;
        return std::cmp::max(
          depth(&n.left, current_depth),
          depth(&n.right, current_depth),
        );
      }
      current_depth
    }

    depth(&root, 0)
  }
}
// @lc code=end
#[cfg(test)]
mod test {
  use super::*;

  fn make_node(node: TreeNode) -> Option<Rc<RefCell<TreeNode>>> {
    Some(Rc::new(RefCell::new(node)))
  }

  #[test]
  fn test_1() {
    assert_eq!(Solution::max_depth(None), 0);
  }

  #[test]
  fn test_2() {
    let root = TreeNode::new(1);

    assert_eq!(Solution::max_depth(make_node(root)), 1);
  }

  #[test]
  fn test_3() {
    let mut root = TreeNode::new(1);
    let left_node = TreeNode::new(2);
    let right_node = TreeNode::new(3);

    root.left = make_node(left_node);
    root.right = make_node(right_node);

    assert_eq!(Solution::max_depth(make_node(root)), 2);
  }

  #[test]
  fn test_4() {
    let mut root = TreeNode::new(1);
    let left_node = TreeNode::new(2);
    let right_node = TreeNode::new(3);

    root.left = make_node(left_node);
    root.right = make_node(right_node);

    assert_eq!(Solution::max_depth(make_node(root)), 2);
  }
}
