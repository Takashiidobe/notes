#
# @lc app=leetcode id=226 lang=python3
#
# [226] Invert Binary Tree
#
# https://leetcode.com/problems/invert-binary-tree/description/
#
# algorithms
# Easy (65.80%)
# Total Accepted:    594K
# Total Submissions: 901.5K
# Testcase Example:  '[4,2,7,1,3,6,9]'
#
# <p>Invert a binary tree.</p>
# 
# <p><strong>Example:</strong></p>
# 
# <p>Input:</p>
# 
# <pre>
# ⁠    4
# ⁠  /   \
# ⁠ 2     7
# ⁠/ \   / \
# 1   3 6   9</pre>
# 
# <p>Output:</p>
# 
# <pre>
# ⁠    4
# ⁠  /   \
# ⁠ 7     2
# ⁠/ \   / \
# 9   6 3   1</pre>
# 
# <p><strong>Trivia:</strong><br />
# This problem was inspired by <a
# href="https://twitter.com/mxcl/status/608682016205344768"
# target="_blank">this original tweet</a> by <a href="https://twitter.com/mxcl"
# target="_blank">Max Howell</a>:</p>
# 
# <blockquote>Google: 90% of our engineers use the software you wrote
# (Homebrew), but you can&rsquo;t invert a binary tree on a whiteboard so f***
# off.</blockquote>
# 
#
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def invertTree(self, root: TreeNode) -> TreeNode:
        
