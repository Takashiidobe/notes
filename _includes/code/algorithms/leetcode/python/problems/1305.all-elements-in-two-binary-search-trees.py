#
# @lc app=leetcode id=1305 lang=python3
#
# [1305] All Elements in Two Binary Search Trees
#
# https://leetcode.com/problems/all-elements-in-two-binary-search-trees/description/
#
# algorithms
# Medium (77.69%)
# Total Accepted:    69.8K
# Total Submissions: 89.8K
# Testcase Example:  '[2,1,4]\r\n[1,0,3]\r'
#
# Given two binary search trees root1 and root2.
# 
# Return a list containing all the integers from both trees sorted in ascending
# order.
# 
# 
# Example 1:
# 
# 
# Input: root1 = [2,1,4], root2 = [1,0,3]
# Output: [0,1,1,2,3,4]
# 
# 
# Example 2:
# 
# 
# Input: root1 = [0,-10,10], root2 = [5,1,7,0,2]
# Output: [-10,0,0,1,2,5,7,10]
# 
# 
# Example 3:
# 
# 
# Input: root1 = [], root2 = [5,1,7,0,2]
# Output: [0,1,2,5,7]
# 
# 
# Example 4:
# 
# 
# Input: root1 = [0,-10,10], root2 = []
# Output: [-10,0,10]
# 
# 
# Example 5:
# 
# 
# Input: root1 = [1,null,8], root2 = [8,1]
# Output: [1,1,8,8]
# 
# 
# 
# Constraints:
# 
# 
# Each tree has at most 5000 nodes.
# Each node's value is between [-10^5, 10^5].
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
    def getAllElements(self, root1: TreeNode, root2: TreeNode) -> List[int]:
        
