#
# @lc app=leetcode id=82 lang=python3
#
# [82] Remove Duplicates from Sorted List II
#
# https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/description/
#
# algorithms
# Medium (37.42%)
# Total Accepted:    275.8K
# Total Submissions: 733.5K
# Testcase Example:  '[1,2,3,3,4,4,5]'
#
# Given a sorted linked list, delete all nodes that have duplicate numbers,
# leaving only distinct numbers from the original list.
# 
# Return the linked list sorted as well.
# 
# Example 1:
# 
# 
# Input: 1->2->3->3->4->4->5
# Output: 1->2->5
# 
# 
# Example 2:
# 
# 
# Input: 1->1->1->2->3
# Output: 2->3
# 
# 
#
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def deleteDuplicates(self, head: ListNode) -> ListNode:
        
