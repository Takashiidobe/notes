#
# @lc app=leetcode id=61 lang=python3
#
# [61] Rotate List
#
# https://leetcode.com/problems/rotate-list/description/
#
# algorithms
# Medium (31.14%)
# Total Accepted:    331.5K
# Total Submissions: 1.1M
# Testcase Example:  '[1,2,3,4,5]\n2'
#
# Given the head of a linked list, rotate the list to the right by k places.
# 
# 
# Example 1:
# 
# 
# Input: head = [1,2,3,4,5], k = 2
# Output: [4,5,1,2,3]
# 
# 
# Example 2:
# 
# 
# Input: head = [0,1,2], k = 4
# Output: [2,0,1]
# 
# 
# 
# Constraints:
# 
# 
# The number of nodes in the list is in the range [0, 500].
# -100 <= Node.val <= 100
# 0 <= k <= 2 * 10^9
# 
# 
#
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def rotateRight(self, head: ListNode, k: int) -> ListNode:
        
