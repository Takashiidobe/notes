/*
 * @lc app=leetcode id=94 lang=rust
 *
 * [94] Binary Tree Inorder Traversal
 *
 * https://leetcode.com/problems/binary-tree-inorder-traversal/description/
 *
 * algorithms
 * Medium (64.40%)
 * Total Accepted:    824.7K
 * Total Submissions: 1.3M
 * Testcase Example:  '[1,null,2,3]'
 *
 * <p>Given the <code>root</code> of a binary tree, return <em>the inorder
 * traversal of its nodes&#39; values</em>.</p>
 * 
 * <p>&nbsp;</p>
 * <p><strong>Example 1:</strong></p>
 * <img alt=""
 * src="https://assets.leetcode.com/uploads/2020/09/15/inorder_1.jpg"
 * style="width: 202px; height: 324px;" />
 * <pre>
 * <strong>Input:</strong> root = [1,null,2,3]
 * <strong>Output:</strong> [1,3,2]
 * </pre>
 * 
 * <p><strong>Example 2:</strong></p>
 * 
 * <pre>
 * <strong>Input:</strong> root = []
 * <strong>Output:</strong> []
 * </pre>
 * 
 * <p><strong>Example 3:</strong></p>
 * 
 * <pre>
 * <strong>Input:</strong> root = [1]
 * <strong>Output:</strong> [1]
 * </pre>
 * 
 * <p><strong>Example 4:</strong></p>
 * <img alt=""
 * src="https://assets.leetcode.com/uploads/2020/09/15/inorder_5.jpg"
 * style="width: 202px; height: 202px;" />
 * <pre>
 * <strong>Input:</strong> root = [1,2]
 * <strong>Output:</strong> [2,1]
 * </pre>
 * 
 * <p><strong>Example 5:</strong></p>
 * <img alt=""
 * src="https://assets.leetcode.com/uploads/2020/09/15/inorder_4.jpg"
 * style="width: 202px; height: 202px;" />
 * <pre>
 * <strong>Input:</strong> root = [1,null,2]
 * <strong>Output:</strong> [1,2]
 * </pre>
 * 
 * <p>&nbsp;</p>
 * <p><strong>Constraints:</strong></p>
 * 
 * <ul>
 * <li>The number of nodes in the tree is in the range <code>[0,
 * 100]</code>.</li>
 * <li><code>-100 &lt;= Node.val &lt;= 100</code></li>
 * </ul>
 * 
 * <p>&nbsp;</p>
 * 
 * <p><strong>Follow up:</strong></p>
 * 
 * <p>Recursive solution is trivial, could you do it iteratively?</p>
 * 
 * <p>&nbsp;</p>
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
    pub fn inorder_traversal(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {
        
    }
}
