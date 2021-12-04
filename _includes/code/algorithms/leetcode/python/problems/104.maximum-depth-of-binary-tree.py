#
# @lc app=leetcode id=104 lang=python3
#
# [104] Maximum Depth of Binary Tree
#
# https://leetcode.com/problems/maximum-depth-of-binary-tree/description/
#
# algorithms
# Easy (66.68%)
# Total Accepted:    928.8K
# Total Submissions: 1.4M
# Testcase Example:  '[3,9,20,null,null,15,7]'
#
# <p>Given a binary tree, find its maximum depth.</p>
# 
# <p>The maximum depth is the number of nodes along the longest path from the
# root node down to the farthest leaf node.</p>
# 
# <p><strong>Note:</strong>&nbsp;A leaf is a node with no children.</p>
# 
# <p><strong>Example:</strong></p>
# 
# <p>Given binary tree <code>[3,9,20,null,null,15,7]</code>,</p>
# 
# <pre>
# ⁠   3
# ⁠  / \
# ⁠ 9  20
# ⁠   /  \
# ⁠  15   7</pre>
# 
# <p>return its depth = 3.</p>
# 
#
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def maxDepth(self, root: TreeNode) -> int:
        
