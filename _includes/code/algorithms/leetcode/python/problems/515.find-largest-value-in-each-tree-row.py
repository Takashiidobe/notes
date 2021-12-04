#
# @lc app=leetcode id=515 lang=python3
#
# [515] Find Largest Value in Each Tree Row
#
# https://leetcode.com/problems/find-largest-value-in-each-tree-row/description/
#
# algorithms
# Medium (61.52%)
# Total Accepted:    117.8K
# Total Submissions: 191K
# Testcase Example:  '[1,3,2,5,3,null,9]'
#
# Given the root of a binary tree, return an array of the largest value in each
# row of the tree (0-indexed).
# 
# 
# 
# 
# Example 1:
# 
# 
# Input: root = [1,3,2,5,3,null,9]
# Output: [1,3,9]
# 
# 
# Example 2:
# 
# 
# Input: root = [1,2,3]
# Output: [1,3]
# 
# 
# Example 3:
# 
# 
# Input: root = [1]
# Output: [1]
# 
# 
# Example 4:
# 
# 
# Input: root = [1,null,2]
# Output: [1,2]
# 
# 
# Example 5:
# 
# 
# Input: root = []
# Output: []
# 
# 
# 
# Constraints:
# 
# 
# The number of nodes in the tree will be in the range [0, 10^4].
# -2^31 <= Node.val <= 2^31 - 1
# 
# 
#
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def largestValues(self, root: TreeNode) -> List[int]:
        
