/*
 * @lc app=leetcode id=104 lang=rust
 *
 * [104] Maximum Depth of Binary Tree
 *
 * https://leetcode.com/problems/maximum-depth-of-binary-tree/description/
 *
 * algorithms
 * Easy (66.68%)
 * Total Accepted:    928.8K
 * Total Submissions: 1.4M
 * Testcase Example:  '[3,9,20,null,null,15,7]'
 *
 * <p>Given a binary tree, find its maximum depth.</p>
 * 
 * <p>The maximum depth is the number of nodes along the longest path from the
 * root node down to the farthest leaf node.</p>
 * 
 * <p><strong>Note:</strong>&nbsp;A leaf is a node with no children.</p>
 * 
 * <p><strong>Example:</strong></p>
 * 
 * <p>Given binary tree <code>[3,9,20,null,null,15,7]</code>,</p>
 * 
 * <pre>
 * ⁠   3
 * ⁠  / \
 * ⁠ 9  20
 * ⁠   /  \
 * ⁠  15   7</pre>
 * 
 * <p>return its depth = 3.</p>
 * 
 */
// Definition for a binary tree node.
// #[derive(Debug, PartialEq, Eq)]
// pub struct TreeNode {
//   pub val: i32,
//   pub left: Option<Rc<RefCell<TreeNode>>>,
//   pub right: Option<Rc<RefCell<TreeNode>>>,
// }
// 
// impl TreeNode {
//   #[inline]
//   pub fn new(val: i32) -> Self {
//     TreeNode {
//       val,
//       left: None,
//       right: None
//     }
//   }
// }
use std::rc::Rc;
use std::cell::RefCell;
impl Solution {
    pub fn max_depth(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
        
    }
}
