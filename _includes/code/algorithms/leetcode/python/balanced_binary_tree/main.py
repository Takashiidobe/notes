#
# @lc app=leetcode id=110 lang=python3
#
# [110] Balanced Binary Tree
#
# https://leetcode.com/problems/balanced-binary-tree/description/
#
# algorithms
# Easy (43.85%)
# Total Accepted:    495.5K
# Total Submissions: 1.1M
# Testcase Example:  '[3,9,20,null,null,15,7]'
#
# Given a binary tree, determine if it is height-balanced.
#
# For this problem, a height-balanced binary tree is defined as:
#
#
# a binary tree in which the left and right subtrees of every node differ in
# height by no more than 1.
#
#
#
# Example 1:
#
#
# Input: root = [3,9,20,null,null,15,7]
# Output: true
#
#
# Example 2:
#
#
# Input: root = [1,2,2,3,3,null,null,4,4]
# Output: false
#
#
# Example 3:
#
#
# Input: root = []
# Output: true
#
#
#
# Constraints:
#
#
# The number of nodes in the tree is in the range [0, 5000].
# -10^4 <= Node.val <= 10^4
#
#
#
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

"""
A balanced binary tree is determined by having a tree where every subtree 
(left and right) has a difference in max depth of no more than 1.
We can validate using backtracking:
If there is no node, we know that both the left and right side have a max depth of 0.
Otherwise, the max depth of the node is 1 + max(left_side, right_side)
"""


class Solution:
    def __init__(self):
        self.balanced = True

    def validate(self, root: TreeNode) -> int:
        if not root:
            return 0
        l = self.validate(root.left)
        r = self.validate(root.right)
        if abs(l - r) > 1:
            self.balanced = False
        return 1 + max(l, r)

    def isBalanced(self, root: TreeNode) -> bool:
        self.validate(root)
        return self.balanced
